#include "NewPhoto.h"

NewPhoto::NewPhoto(std::vector<int> cameraIDs, std::string passHash, QString name, QString surname,int loggedID, int faceID, ImgProc *imgProc, QWidget *parent)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	this->imgProc = imgProc;
	/*imgProc = new ImgProc();*/
	/*imgProc->LoadFaceCascade();*/
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
	if (capThread != nullptr)
	{
		capThread->StopThread();
		capThread->wait();
		delete capThread;
	}
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
	disconnect(capThread, SIGNAL(updatePixmap(const QPixmap&)), this, SLOT(UpdatePixmap(const QPixmap&)));
	bool result = true;

	//Keep the last frame
	QImage   swapped = pixmap.toImage();
	if (pixmap.toImage().format() == QImage::Format_RGB32)
	{
		swapped = swapped.convertToFormat(QImage::Format_RGB888);
	}
	swapped = swapped.rgbSwapped();
	cv::Mat tmpMatImg = cv::Mat(
		swapped.height(), swapped.width(),
		CV_8UC3,
		const_cast<uchar*>(swapped.bits()),
		static_cast<size_t>(swapped.bytesPerLine())).clone();
	//

	//Detect face
	//cv::Mat tmpMatImg = matImg;
	std::vector<cv::Rect> faces = imgProc->DetectFace(tmpMatImg);
	int peopleInFrameCounter = faces.size();
	if (peopleInFrameCounter > 1)
	{
		ui.PBSnapshot->setEnabled(false);
		ui.LWarning->setStyleSheet("QLabel{color: rgb(255, 255, 255);background-color: rgb(255, 77, 61);}");
		ui.LWarning->setText("In frame must be only one face");
		ui.LWarning->setAlignment(Qt::AlignCenter);
	}
	else if (peopleInFrameCounter == 1)
	{
		ui.PBSnapshot->setEnabled(true);
		ui.LWarning->setStyleSheet("QLabel{color: rgb(255, 255, 255);background-color:rgb(36, 118, 59);}");
		ui.LWarning->setText("You can take photo");
		ui.LWarning->setAlignment(Qt::AlignCenter);
		//crop photo
		cv::Rect myROI(faces[0].x*2+1, faces[0].y*2+1, faces[0].width*2-1, faces[0].height*2-1);
		// Crop the full image to that image contained by the rectangle myROI
		cv::Mat imgCropped = tmpMatImg(myROI);
		cvtColor(imgCropped, imgCropped, CV_BGR2GRAY);
		cv::resize(imgCropped, imgCropped, cv::Size(200, 200), 1.0, 1.0, cv::INTER_CUBIC);
		matImg = imgCropped;
	}
	else
	{
		ui.PBSnapshot->setEnabled(false);
		ui.LWarning->setStyleSheet("QLabel{color: rgb(255, 255, 255);background-color: rgb(255, 77, 61);}");
		ui.LWarning->setText("No faces has been detected");
		ui.LWarning->setAlignment(Qt::AlignCenter);
	}

	cvtColor(tmpMatImg, tmpMatImg, CV_BGR2RGB);
	//cv::Mat -> to QPixmap
	QPixmap::fromImage(QImage(tmpMatImg.data, 760, 427, tmpMatImg.step, QImage::Format_RGB888));
	QImage imgIn = QImage((uchar*)tmpMatImg.data, tmpMatImg.cols, tmpMatImg.rows, tmpMatImg.step, QImage::Format_RGB888);
	ui.LPreviewScreen->setPixmap(QPixmap::fromImage(imgIn));
	//ui.LPreviewScreen->setPixmap(tmp);
	connect(capThread, SIGNAL(updatePixmap(const QPixmap&)), this, SLOT(UpdatePixmap(const QPixmap&)));
}
void NewPhoto::BackButtonClicked()
{
	//Close window
	this->close();
}
void NewPhoto::PBSnapshotClicked(int faceID)
{
	QString folderPath = ".\\FaceBase\\" + QVariant(faceID).toString();
	Utilities::CreateFolderIfNotExists(folderPath);
	QString dateTime=Utilities::GetCurrentDateTime();
	cv::Mat tmp = matImg;
	//cvtColor(tmp, tmp, CV_BGR2RGB);
	QString picturePath = folderPath + "\\" + dateTime + ".jpg";
	std::string pathToFile = picturePath.toStdString();
	replace(pathToFile.begin(), pathToFile.end(),':', '-');
	cv::imwrite(pathToFile, tmp);
	//Add to images
	imgProc->PushBackImage(tmp);
	//Add to labels
	imgProc->PushBackLabel(faceID);
	Utilities::MBAlarm("Picture has been taken", true);
}
//Delete this method
bool NewPhoto::CameraPreviewUpdate(std::string streamURI)
{
	//QThread::currentThread()->setPriority(QThread::Priority::HighestPriority);
	cv::VideoCapture vcap;
	ImgProc *imgproc = new ImgProc();
	bool result = true;
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
	delete imgproc;
	return result;
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