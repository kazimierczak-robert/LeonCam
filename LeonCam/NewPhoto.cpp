#include "NewPhoto.h"

NewPhoto::NewPhoto(std::vector<int> cameraIDs, std::string passHash, QString name, QString surname,int loggedID, int faceID, ImgProc *imgProc, map<int, MainAppCamera *> *cameraThread, QWidget *parent)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	this->loggedID = loggedID;
	this->imgProc = imgProc;
	this->cameraThread = cameraThread;
	/*imgProc = new ImgProc();*/
	/*imgProc->LoadFaceCascade();*/
	ui.setupUi(this);
	this->setWindowTitle(name + " " + surname +" (ID: " + (QVariant(faceID)).toString() + ") - LeonCam");
//	capThread = new CapturingFrame(this);

	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));

	connect(ui.PBFolder, &QPushButton::clicked, this, [this, faceID] {Utilities::OpenFileExplorer(".\\FaceBase\\" + QVariant(faceID).toString()); });
	GetCamerasInfo(loggedID, cameraIDs);
	currentCameraID = ui.CBPresets->currentData().toInt();
	//connect(ui.PBFolder, SIGNAL(clicked()), this, SLOT(OpenFileExplorer(ID)));
	//future = QtConcurrent::run([=]() {CameraPreviewUpdate(cameraURIs); }); //run preview from camera
	connect(ui.CBPresets, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
		[=](int index) {CurrentIndexChanged(passHash); });
	connect(ui.PBSnapshot, &QPushButton::clicked, this, [this, faceID] {PBSnapshotClicked(faceID); });
	connect(cameraThread->at(currentCameraID), SIGNAL(updatePixmap(const QPixmap&)), this, SLOT(UpdatePixmap(const QPixmap&)));
	cameraThread->at(currentCameraID)->SetSendBigPicture(true);
	FillPtzAndProfileToken(passHash);
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
	//if (capThread != nullptr)
	//{
	//	capThread->StopThread();
	//	capThread->wait();
	//	delete capThread;
	//}
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
	disconnect(cameraThread->at(currentCameraID), SIGNAL(updatePixmap(const QPixmap&)), this, SLOT(UpdatePixmap(const QPixmap&)));
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
	connect(cameraThread->at(currentCameraID), SIGNAL(updatePixmap(const QPixmap&)), this, SLOT(UpdatePixmap(const QPixmap&)));
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
	ImgProc *imgproc = new ImgProc(loggedID);
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
	query.prepare("SELECT CameraID, Name FROM Cameras WHERE UserID=?");
	query.bindValue(0, loggedID);
	bool result = query.exec();
	if (result == true)
	{
		while (query.next())
		{
			//https://stackoverflow.com/a/3450906
			//if cameraIDs contains
			if (std::find(cameraIDs.begin(), cameraIDs.end(), query.value(0).toInt()) != cameraIDs.end())
			{
				//fill camerasToCB: CameraID and Name
				ui.CBPresets->addItem(query.value(1).toString(), query.value(0).toInt());
			}
		}
	}
}
void NewPhoto::FillPtzAndProfileToken(std::string passHash)
{
	//Get cameras IPAddress, Login, Password
	QSqlQuery query;
	query.prepare("Select IPAddress, Login, Password FROM Cameras WHERE CameraID = ?");
	query.bindValue(0, currentCameraID);
	bool result = query.exec();
	if (result == true)
	{
		query.next();
		QString iPAddress = query.value(0).toString();
		QString login = query.value(1).toString();
		QString password = query.value(2).toString();

		//Decrypt password
		std::string DecPass = Utilities::GetDecrypted(passHash, password.toStdString());
		//Get stream URI
		std::string url = "http://" + iPAddress.toStdString() + "/onvif/device_service";
		OnvifClientDevice *onvifDevice = new OnvifClientDevice(url, login.toStdString(), DecPass);
		if (onvifDevice->GetCapabilities() == 0) 
		{
			OnvifClientMedia media(*onvifDevice);
			_trt__GetProfilesResponse profiles;
			media.GetProfiles(profiles);
			if (profiles.Profiles.size() > 0)
			{
				this->profileToken = profiles.Profiles[0]->token;
				this->ptz = new OnvifClientPTZ(*onvifDevice);
			}
		}
	}
}
void NewPhoto::CurrentIndexChanged(std::string passHash)
{
	//Get previousCameraID
	int previousCameraID = currentCameraID;
	cameraThread->at(previousCameraID)->SetSendBigPicture(false);
	//Change currentCameraID
	currentCameraID = ui.CBPresets->currentData().toInt();
	FillPtzAndProfileToken(passHash);
	//Disconnect 'old' thread
	disconnect(cameraThread->at(previousCameraID), SIGNAL(updatePixmap(const QPixmap&)), this, SLOT(UpdatePixmap(const QPixmap&)));
	connect(cameraThread->at(currentCameraID), SIGNAL(updatePixmap(const QPixmap&)), this, SLOT(UpdatePixmap(const QPixmap&)));
	cameraThread->at(currentCameraID)->SetSendBigPicture(true);
}

void NewPhoto::closeEvent(QCloseEvent *event)
{
	cameraThread->at(currentCameraID)->SetSendBigPicture(false);
	event->accept();
}