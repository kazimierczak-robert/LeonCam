#include "NewPhoto.h"

NewPhoto::NewPhoto(std::vector<int> cameraIDs, std::string passHash, QString name, QString surname,int loggedID, int faceID, ImgProc *imgProc, map<int, MainAppCamera *> *cameraThread, QWidget *parent)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	this->loggedID = loggedID;
	this->imgProc = imgProc;
	this->cameraThread = cameraThread;
	ui.setupUi(this);
	this->setWindowTitle(name + " " + surname +" (ID: " + (QVariant(faceID)).toString() + ") - LeonCam");
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
	connect(ui.PBFolder, &QPushButton::clicked, this, [this, faceID] {Utilities::OpenFileExplorer(".\\FaceBase\\" + QVariant(faceID).toString()); });
	GetCamerasInfo(loggedID, cameraIDs);
	currentCameraID = ui.CBPresets->currentData().toInt();

	connect(ui.CBPresets, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
		[=](int index) {CurrentIndexChanged(passHash); });

	connect(ui.PBSnapshot, &QPushButton::clicked, this, [this, faceID] {PBSnapshotClicked(faceID); });
	
	imageWidget = new CVImageWidget();
	ui.verticalLayout->addWidget(imageWidget);
	qRegisterMetaType< cv::Mat >("const cv::Mat&");
	connect(cameraThread->at(currentCameraID), SIGNAL(updateImage(const cv::Mat&)), this, SLOT(UpdateImage(const cv::Mat&)));
	
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
	connect(ui.PWarning, &QPushButton::clicked, this, [this, faceID] {PBSnapshotClicked(faceID); });
}
NewPhoto::~NewPhoto()
{
	if (onvifDevice != nullptr)
	{
		delete onvifDevice;
	}
	if (ptz != nullptr)
	{
		delete ptz;
	}
	if (cameraControl != nullptr)
	{
		delete cameraControl;
	}
	if (imageWidget != nullptr)
	{
		delete imageWidget;
	}
}
//https://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap/
void NewPhoto::UpdateImage(const cv::Mat& image)
{
	disconnect(cameraThread->at(currentCameraID), SIGNAL(updateImage(const cv::Mat&)), this, SLOT(UpdateImage(const cv::Mat&)));
	//Detect face
	cv::Mat tmpImage = image;
	std::vector<cv::Rect> faces = imgProc->DetectFace(tmpImage);
	int peopleInFrameCounter = faces.size();
	if (peopleInFrameCounter > 1)
	{
		ui.PBSnapshot->setEnabled(false);
		ui.PWarning->setEnabled(false);

		ui.PWarning->setStyleSheet("QPushButton{color: rgb(255, 255, 255);background-color: rgb(255, 77, 61);}");
		ui.PWarning->setText("In frame must be only one face");
	}
	else if (peopleInFrameCounter == 1)
	{
		ui.PBSnapshot->setEnabled(true);
		ui.PWarning->setEnabled(true);

		ui.PWarning->setStyleSheet("QPushButton{color: rgb(255, 255, 255);background-color:rgb(36, 118, 59);}");
		ui.PWarning->setText("You can take photo");

		//crop photo
		cv::Rect myROI(faces[0].x+1, faces[0].y+1, faces[0].width-1, faces[0].height-1);
		// Crop the full image to that image contained by the rectangle myROI
		cv::Mat imgCropped = tmpImage(myROI);
		//cvtColor(imgCropped, imgCropped, CV_BGR2GRAY);
		cv::resize(imgCropped, imgCropped, cv::Size(100, 100), 1.0, 1.0, cv::INTER_CUBIC);
		matImg = imgCropped;
	}
	else
	{
		ui.PBSnapshot->setEnabled(false);
		ui.PWarning->setEnabled(false);

		ui.PWarning->setStyleSheet("QPushButton{color: rgb(255, 255, 255);background-color: rgb(255, 77, 61);}");
		ui.PWarning->setText("No faces has been detected");
	}

	imageWidget->ShowImage(tmpImage);
	//ui.LPreviewScreen->setPixmap(tmp);
	connect(cameraThread->at(currentCameraID), SIGNAL(updateImage(const cv::Mat&)), this, SLOT(UpdateImage(const cv::Mat&)));
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
		std::string decPass = Utilities::GetDecrypted(passHash, password.toStdString());
		//Get stream URI
		std::string url = "http://" + iPAddress.toStdString() + "/onvif/device_service";
		onvifDevice = new OnvifClientDevice(url, login.toStdString(), decPass);
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
	disconnect(cameraThread->at(previousCameraID), SIGNAL(updateImage(const cv::Mat&)), this, SLOT(UpdateImage(const cv::Mat&)));
	connect(cameraThread->at(currentCameraID), SIGNAL(updateImage(const cv::Mat&)), this, SLOT(UpdateImage(const cv::Mat&)));
	cameraThread->at(currentCameraID)->SetSendBigPicture(true);
}
void NewPhoto::closeEvent(QCloseEvent *event)
{
	cameraThread->at(currentCameraID)->SetSendBigPicture(false);
	event->accept();
}