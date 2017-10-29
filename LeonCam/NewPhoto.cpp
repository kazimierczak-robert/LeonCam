#include "NewPhoto.h"

NewPhoto::NewPhoto(std::vector<int> cameraIDs, std::string passHash, QString name, QString surname,int loggedID, int faceID, QWidget *parent)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	this->setWindowTitle(name + " " + surname +" (ID: " + (QVariant(faceID)).toString() + ") - LeonCam");
	capThread = new CapturingFrame(this);
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
	connect(ui.PBFolder, &QPushButton::clicked, this, [this, faceID] {Utilities::OpenFileExplorer(faceID); });
	GetCamerasInfo(loggedID, cameraIDs);
	FillCBWithCamerasToCB();
	//connect(ui.PBFolder, SIGNAL(clicked()), this, SLOT(OpenFileExplorer(ID)));
	//future = QtConcurrent::run([=]() {CameraPreviewUpdate(cameraURIs); }); //run preview from camera
	connect(ui.CBPresets, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
		[=](int index) {CurrentIndexChanged(passHash); });
	connect(ui.PBSnapshot, &QPushButton::clicked, this, [this, faceID] {PBSnapshotClicked(faceID); });
	connect(capThread, SIGNAL(updatePixmap(const QPixmap&)), this, SLOT(UpdatePixmap(const QPixmap&)));
	//fill profileToken & ptz
	CurrentIndexChanged(passHash);
	//Camera control
	cameraControl = new CameraControl(this->ptz, this->profileToken);
	//left, right, up, down control
	connect(ui.PBLeft, &QPushButton::pressed, this, [this] {cameraControl->MoveCamera(-0.2, 0.0); });
	connect(ui.PBRight, &QPushButton::pressed, this, [this] {cameraControl->MoveCamera(0.2, 0.0); });
	connect(ui.PBUp, &QPushButton::pressed, this, [this] {cameraControl->MoveCamera(0.0, 0.2); });
	connect(ui.PBDown, &QPushButton::pressed, this, [this] {cameraControl->MoveCamera(0.0, -0.2); });

	connect(ui.PBLeft, &QPushButton::released, this, [this] {cameraControl->StopCamera(); });
	connect(ui.PBRight, &QPushButton::released, this, [this] {cameraControl->StopCamera(); });
	connect(ui.PBUp, &QPushButton::released, this, [this] {cameraControl->StopCamera(); });
	connect(ui.PBDown, &QPushButton::released, this, [this] {cameraControl->StopCamera(); });
	//home position
	connect(ui.PBHome, &QPushButton::clicked, this, [this] {cameraControl->GoHomeCamera(); });
}

NewPhoto::~NewPhoto()
{
	//Close thread
	capThread->StopThread();
	capThread->wait();
	delete capThread;
	if (ptz != nullptr)
	{
		delete ptz;
	}
	if (cameraControl != nullptr)
	{
		delete cameraControl;
	}
}

//https://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap/
void NewPhoto::UpdatePixmap(const QPixmap& pixmap)
{
	ui.LPreviewScreen->setPixmap(pixmap);

	QImage   swapped = pixmap.toImage();
	if (pixmap.toImage().format() == QImage::Format_RGB32)
	{
		swapped = swapped.convertToFormat(QImage::Format_RGB888);
	}
	swapped = swapped.rgbSwapped();
	matImg = cv::Mat(
		swapped.height(), swapped.width(),
		CV_8UC3,
		const_cast<uchar*>(swapped.bits()),
		static_cast<size_t>(swapped.bytesPerLine())).clone();
}
void NewPhoto::BackButtonClicked()
{
	//Close window
	this->close();
}
void NewPhoto::PBSnapshotClicked(int faceID)
{
	//TODO: <date.jpg>
	//create folder if not exists
	cv::Mat tmp = matImg;
	cv::imwrite(".\\FaceBase\\"+ std::to_string(faceID) + "\\date.jpg", tmp);
}
void NewPhoto::CameraPreviewUpdate(std::string streamURI)
{
	//QThread::currentThread()->setPriority(QThread::Priority::HighestPriority);
	cv::VideoCapture vcap;
	if (vcap.open(streamURI))
	{
		while (true)
		{
			if (vcap.read(matImg))
			{
				cvtColor(matImg, matImg, CV_BGR2RGB);
				ui.LPreviewScreen->setPixmap(QPixmap::fromImage(QImage(matImg.data, 760, 427, matImg.step, QImage::Format_RGB888)));
			}
		}
	}
}
void NewPhoto::GetCamerasInfo(int loggedID, std::vector<int> cameraIDs)
{
	//Get Cameras where UserID equals loggedID
	QSqlQuery query;
	query.prepare("SELECT CameraID, Name, IPAddress, Login, Password FROM Cameras WHERE UserID=?");
	query.bindValue(0, loggedID);
	bool result = query.exec() == true ? true : false;
	if (result == true)
	{
		while (query.next())
		{
			//https://stackoverflow.com/a/3450906
			//if cameraIDs contains
			if (std::find(cameraIDs.begin(), cameraIDs.end(), query.value(0).toInt()) != cameraIDs.end())
			{
				//fill camerasToCB
				camerasToCB.insert(std::pair<int, std::string>(query.value(0).toInt(), query.value(1).toString().toStdString()));
				//fill cameras
				struct Camera *cam = new struct Camera;
				cam->CameraID = query.value(0).toInt();
				cam->Name = query.value(1).toString().toStdString();
				cam->IPAddress = query.value(2).toString().toStdString();
				cam->Login = query.value(3).toString().toStdString();
				cam->Password = query.value(4).toString().toStdString();

				cameras.insert(std::pair<int, struct Camera*>(query.value(0).toInt(), cam));
			}
		}
	}
}
void NewPhoto::FillCBWithCamerasToCB()
{
	for (std::pair<int, std::string> elem : camerasToCB)
	{
		ui.CBPresets->addItem(QString::fromStdString(elem.second), elem.first);
	}

}
void NewPhoto::CurrentIndexChanged(std::string passHash)
{
	//Get camera
	int cameraID = ui.CBPresets->currentData().toInt();
	struct Camera *cam = cameras[cameraID];
	
	//Decrypt passorrd
	std::string password = Utilities::GetDecrypted(passHash, cam->Password);
	//Get stream URI & start capturing frames thread 
	std::string url = "http://" + cam->IPAddress + "/onvif/device_service";
	OnvifClientDevice *onvifDevice = new OnvifClientDevice(url, cam->Login, password);
	if (onvifDevice->GetCapabilities() == 0)
	{
		OnvifClientMedia media(*onvifDevice);
		_trt__GetProfilesResponse profiles;
		media.GetProfiles(profiles);

		if (profiles.Profiles.size() > 0)
		{
			this->profileToken = profiles.Profiles[0]->token;
			_trt__GetStreamUriResponse link;
			media.GetStreamUrl(this->profileToken, link);

			if (&link.MediaUri != NULL)
			{
				this->ptz = new OnvifClientPTZ(*onvifDevice);
				std::string streamURI = link.MediaUri->Uri.insert(link.MediaUri->Uri.find("//") + 2, cam->Login + ":" + password + "@");

				capThread->SetStreamURI(streamURI);
				capThread->start();
			}
		}
	}
}