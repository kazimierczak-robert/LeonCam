#include "CameraPreview.h"

void CameraPreview::CameraPreviewUpdate()
{
	//QThread::currentThread()->setPriority(QThread::Priority::HighestPriority);
	cv::VideoCapture vcap;
	cv::Mat img;
	if (vcap.open(this->streamURI))
	{
		while (ui.PBCameraOnOff->text() == "On")
		{
			if (vcap.read(img))
			{
				cvtColor(img, img, CV_BGR2RGB);
				ui.LPreviewScreen->setPixmap(QPixmap::fromImage(QImage(img.data, 760, 427, img.step, QImage::Format_RGB888)));
			}
		}
	}
}


CameraPreview::CameraPreview(QWidget *parent, QString cameraDetails, QPushButton *buttonIsEnabledFromParent, QPushButton *buttonRecognationFromParent, QLabel *numberOfEnabledCameras, OnvifClientDevice *onvifDevice, string profileToken, string streamURI)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	this->buttonIsEnabledFromParent = buttonIsEnabledFromParent;
	this->buttonRecognationFromParent = buttonRecognationFromParent;
	this->numberOfEnabledCameras = numberOfEnabledCameras;

	this->profileToken = profileToken;
	this->ptz = new OnvifClientPTZ(*onvifDevice);
	this->streamURI = streamURI;
	this->streamURI.insert(this->streamURI.find("//") + 2, ":@");

	connect(ui.PBCameraOnOff, SIGNAL(clicked()), this, SLOT(TurnOnOffCamera()));
	connect(ui.PBRecognize, SIGNAL(clicked()), this, SLOT(TurnOnOffRecognizeMode()));
	ui.LCameraDetails->setText(cameraDetails);
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));

	connect(ui.PBLeft, &QPushButton::pressed, this, [this] {MoveCamera(-0.2, 0.0); });
	connect(ui.PBRight, &QPushButton::pressed, this, [this] {MoveCamera(0.2, 0.0); });
	connect(ui.PBUp, &QPushButton::pressed, this, [this] {MoveCamera(0.0, 0.2); });
	connect(ui.PBDown, &QPushButton::pressed, this, [this] {MoveCamera(0.0, -0.2); });

	connect(ui.PBLeft, SIGNAL(released()), this, SLOT(StopCamera()));
	connect(ui.PBRight, SIGNAL(released()), this, SLOT(StopCamera()));
	connect(ui.PBUp, SIGNAL(released()), this, SLOT(StopCamera()));
	connect(ui.PBDown, SIGNAL(released()), this, SLOT(StopCamera()));

	connect(ui.PBHome, SIGNAL(clicked()), this, SLOT(GoHomeCamera()));

	/*_tptz__SetPresetResponse *res2 = new _tptz__SetPresetResponse();
	ptz->SetPreset(*res2, profileToken);

	_tptz__GetPresetsResponse *res = new _tptz__GetPresetsResponse();
	ptz->GetPresets(*res, profileToken);*/


	if (buttonIsEnabledFromParent->text() == "On")
	{
		future = QtConcurrent::run([=]() {CameraPreviewUpdate();});
		ui.PBCameraOnOff->setText("On");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
	}
	else
	{
		ui.PBCameraOnOff->setText("Off");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
	}

	if (buttonRecognationFromParent->text() == "On")
	{
		ui.PBRecognize->setText("On");
		ui.PBRecognize->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}");
	}
	else
	{
		ui.PBRecognize->setText("Off");
		ui.PBRecognize->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOff.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOffHover.png);}");
	}

}

CameraPreview::~CameraPreview()
{
}

void CameraPreview::BackButtonClicked()
{
	if (future.isRunning()==true)
	{
		if (ui.PBCameraOnOff->text() == "On")
		{
			ui.PBCameraOnOff->setText("Off");
			future.waitForFinished();
			ui.PBCameraOnOff->setText("On");
		}
	}
	this->close();
}


void CameraPreview::TurnOnOffCamera()
{
	int number = numberOfEnabledCameras->text().split(" ").last().toInt();

	if (ui.PBCameraOnOff->text() == "Off")
	{
		future = QtConcurrent::run([=]() {CameraPreviewUpdate(); });
		ui.PBCameraOnOff->setText("On");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
		buttonIsEnabledFromParent->setText("On");
		buttonIsEnabledFromParent->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
		number += 1;
	}
	else
	{
		ui.PBCameraOnOff->setText("Off");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");

		buttonIsEnabledFromParent->setText("Off");
		buttonIsEnabledFromParent->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
		number -= 1;
	}

	numberOfEnabledCameras->setText("Number of enabled cameras: " + QVariant(number).toString());
}

void CameraPreview::TurnOnOffRecognizeMode()
{
	if (buttonRecognationFromParent->text() == "Off")
	{
		buttonRecognationFromParent->setText("On");
		buttonRecognationFromParent->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}");
		ui.PBRecognize->setText("On");
		ui.PBRecognize->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}");
	}
	else
	{
		buttonRecognationFromParent->setText("Off");
		buttonRecognationFromParent->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOff.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOffHover.png);}");
		ui.PBRecognize->setText("Off");
		ui.PBRecognize->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOff.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOffHover.png);}");
	}
}
void CameraPreview::MoveCamera(float panSpeed, float tiltSpeed)
{
	_tptz__ContinuousMoveResponse *res = new _tptz__ContinuousMoveResponse();
	LONG64 timeout = 1;

	tt__PTZSpeed *ptzSpeed = new tt__PTZSpeed();
	ptzSpeed->PanTilt = new tt__Vector2D();
	ptzSpeed->PanTilt->x = panSpeed;
	ptzSpeed->PanTilt->y = tiltSpeed;

	ptzSpeed->Zoom = new tt__Vector1D();
	ptzSpeed->Zoom->x = 0.0;

	for (int i = 0; i < MAXTRIES; i++)
	{
		ptz->ContinuousMove(*res, *ptzSpeed, timeout, profileToken);
		if (res->soap != nullptr)
		{
			if (res->soap->status == 200)
			{
				break;
			}
		}
	}
}
void CameraPreview::StopCamera()
{
	_tptz__StopResponse *res = new _tptz__StopResponse();
	for (int i = 0; i < MAXTRIES; i++)
	{
		ptz->Stop(*res, 1, 1, profileToken);
		if (res->soap != nullptr)
		{
			if (res->soap->status == 200)
			{
				break;
			}
		}
	}
}
void CameraPreview::GoHomeCamera()
{
	_tptz__GotoHomePositionResponse *res = new _tptz__GotoHomePositionResponse();
	for (int i = 0; i < MAXTRIES; i++)
	{
		ptz->GoToHomePosition(*res, profileToken);
		if (res->soap != nullptr)
		{
			if (res->soap->status == 200)
			{
				break;
			}
		}
	}
}
