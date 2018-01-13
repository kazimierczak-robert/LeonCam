#include "CameraPreview.h"

CameraPreview::CameraPreview(QWidget *parent, QString cameraDetails, QPushButton *buttonIsEnabledFromParent, QPushButton *buttonRecognationFromParent, QPushButton *buttonTakePhotoFromParent, int cameraID, /*MainAppCamera *thread*/std::map<int, MainAppCamera *> *cameraThread, std::string passHash)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	this->buttonIsEnabledFromParent = buttonIsEnabledFromParent;
	this->buttonRecognationFromParent = buttonRecognationFromParent;
	this->buttonTakePhotoFromParent = buttonTakePhotoFromParent;
	this->cameraID = cameraID;
	this->passHash = passHash;

	ui.LCameraDetails->setText(cameraDetails);

	ui.CBPresets->setVisible(false);
	ui.PBGoToPreset->setVisible(false);
	ui.PBSavePreset->setVisible(false);

	this->cameraThread = cameraThread;
	device = nullptr;
	ptz = nullptr;
	ctrl = nullptr;

	connect(ui.PBCameraOnOff, SIGNAL(clicked()), this, SLOT(TurnOnOffCamera()));
	connect(ui.PBRecognize, SIGNAL(clicked()), this, SLOT(TurnOnOffRecognizeMode()));
	connect(ui.PBBack, &QPushButton::clicked, this, [this] {this->close();	});
	connect(ui.PBEdit, &QPushButton::clicked, this, [this, cameraID] {emit openCameraEdit(cameraID); });
	connect(ui.PBLeft, &QPushButton::pressed, this, [this] {ctrl->MoveCamera(-0.2, 0.0); });
	connect(ui.PBRight, &QPushButton::pressed, this, [this] {ctrl->MoveCamera(0.2, 0.0); });
	connect(ui.PBUp, &QPushButton::pressed, this, [this] {ctrl->MoveCamera(0.0, 0.2); });
	connect(ui.PBDown, &QPushButton::pressed, this, [this] {ctrl->MoveCamera(0.0, -0.2); });

	connect(ui.PBLeft, &QPushButton::released, this, [this] {ctrl->StopCamera(); });
	connect(ui.PBRight, &QPushButton::released, this, [this] {ctrl->StopCamera(); });
	connect(ui.PBUp, &QPushButton::released, this, [this] {ctrl->StopCamera(); });
	connect(ui.PBDown, &QPushButton::released, this, [this] {ctrl->StopCamera(); });

	connect(ui.PBHome, &QPushButton::clicked, this, [this] {ctrl->GoHomeCamera(); });
	connect(ui.PBSnapshot, &QPushButton::clicked, this, [this, buttonTakePhotoFromParent] {buttonTakePhotoFromParent->click(); });

	imageWidget = new CVImageWidget();
	ui.verticalLayout->addWidget(imageWidget);
	qRegisterMetaType< cv::Mat >("const cv::Mat&");

	connect(parent, SIGNAL(closeCameraEdit(const QString&)), this, SLOT(CloseCameraEdit(const QString&)));
	/*_tptz__SetPresetResponse *res2 = new _tptz__SetPresetResponse();
	ptz->SetPreset(*res2, profileToken);

	_tptz__GetPresetsResponse *res = new _tptz__GetPresetsResponse();
	ptz->GetPresets(*res, profileToken);*/

	ui.PBCameraOnOff->setText(buttonIsEnabledFromParent->text());
	ui.PBCameraOnOff->setStyleSheet(buttonIsEnabledFromParent->styleSheet());

	ui.PBRecognize->setText(buttonRecognationFromParent->text());
	ui.PBRecognize->setStyleSheet(buttonRecognationFromParent->styleSheet());
	
	ui.PBSnapshot->setText(buttonTakePhotoFromParent->text());

	imageWidget->ShowImage(cv::imread(".\\Resources\\Images\\previewNotAvailable.png"));

	if (buttonIsEnabledFromParent->text() == "On")
	{
		imageWidget->ShowImage(cv::imread(".\\Resources\\Images\\connecting.png"));
		TurnOnLabels();
		if (!SetProfileTokenAndPTZ())
		{
			imageWidget->ShowImage(cv::imread(".\\Resources\\Images\\previewNotAvailable.png"));
			buttonIsEnabledFromParent->click();
			TurnOffLabels();
		}
	}
	else
	{
		TurnOffLabels();
	}
}
CameraPreview::~CameraPreview()
{
	if (device != nullptr)
	{
		delete device;
	}
	if (ptz != nullptr)
	{
		delete ptz;
	}
	if (ctrl != nullptr)
	{
		delete ctrl;
	}
	if (imageWidget != nullptr)
	{
		delete imageWidget;
	}
}
void CameraPreview::TurnOnLabels()
{
	ui.PBCameraOnOff->setText("On");
	ui.PBCameraOnOff->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/greenSwitch.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/greenSwitchHover.png);}");
	ui.PBUp->setEnabled(true);
	ui.PBDown->setEnabled(true);
	ui.PBLeft->setEnabled(true);
	ui.PBRight->setEnabled(true);
	ui.PBHome->setEnabled(true);
	ui.PBSnapshot->setText(buttonTakePhotoFromParent->text());
	ui.PBSnapshot->setEnabled(true);

	connect(cameraThread->at(cameraID), SIGNAL(updateImage(const cv::Mat&)), imageWidget, SLOT(ShowImage(const cv::Mat&)));
	cameraThread->at(cameraID)->SetSendBigPicture(true);
}
bool CameraPreview::SetProfileTokenAndPTZ()
{
	this->profileToken = "";
	if (device != nullptr)
	{
		delete device;
		device = nullptr;
	}
	if (ptz != nullptr)
	{
		delete ptz;
		ptz = nullptr;
	}
	if (ctrl != nullptr)
	{
		delete ctrl;
		ctrl = nullptr;
	}

	QSqlQuery query;
	query.prepare("SELECT IPAddress, Login, Password FROM Cameras WHERE CameraID=?");
	query.bindValue(0, cameraID);
	if (query.exec())
	{
		query.next();
		string url = "http://" + query.value(0).toString().toStdString() + "/onvif/device_service";
		string user = query.value(1).toString().toStdString();
		string pass = Utilities::GetDecrypted(passHash, query.value(2).toString().toStdString());

		device = new OnvifClientDevice(url, user, pass);
		if (device->GetCapabilities() == 0)
		{
			OnvifClientMedia media(*device);
			_trt__GetProfilesResponse profiles;
			media.GetProfiles(profiles);
			if (profiles.Profiles.size() > 0)
			{
				this->profileToken = profiles.Profiles[0]->token;
				this->ptz = new OnvifClientPTZ(*device);
				ctrl = new CameraControl(ptz, profileToken);
				return true;
			}
		}
	}
	Utilities::MBAlarm("Cannot connect to this camera. Check camera details and your local network connection, then try again", false);
	return false;
}
void CameraPreview::TurnOffLabels()
{
	disconnect(cameraThread->at(cameraID), SIGNAL(updateImage(const cv::Mat&)), imageWidget, SLOT(ShowImage(const cv::Mat&)));
	cameraThread->at(cameraID)->SetSendBigPicture(false);
	ui.PBCameraOnOff->setText("Off");
	ui.PBCameraOnOff->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/redSwitch.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/redSwitchHover.png);}");
	ui.PBUp->setEnabled(false);
	ui.PBDown->setEnabled(false);
	ui.PBLeft->setEnabled(false);
	ui.PBRight->setEnabled(false);
	ui.PBHome->setEnabled(false);
	ui.PBSnapshot->setText(buttonTakePhotoFromParent->text());
	ui.PBSnapshot->setEnabled(false);

	ui.PBRecognize->setText(buttonRecognationFromParent->text());
	ui.PBRecognize->setStyleSheet(buttonRecognationFromParent->styleSheet());
}
void CameraPreview::CloseCameraEdit(const QString& cameraDetails)
{
	bool wasTurnedOn = false;
	if (ui.PBCameraOnOff->text()=="On")
	{
		TurnOnOffCamera();
		wasTurnedOn = true;
	}
	ui.LCameraDetails->setText(cameraDetails);

	if (wasTurnedOn == true)
	{
		imageWidget->ShowImage(cv::imread(".\\Resources\\Images\\connecting.png"));
		if (SetProfileTokenAndPTZ())
		{
			TurnOnOffCamera();
		}
		else
		{
			imageWidget->ShowImage(cv::imread(".\\Resources\\Images\\previewNotAvailable.png"));
		}
	}
}
void CameraPreview::TurnOnOffCamera()
{
	if (ui.PBCameraOnOff->text() == "Off")
	{
		imageWidget->ShowImage(cv::imread(".\\Resources\\Images\\connecting.png"));
		if (ptz == nullptr)
		{
			if (SetProfileTokenAndPTZ())
			{
				buttonIsEnabledFromParent->click();
				if (buttonIsEnabledFromParent->text() == "On")
				{
					TurnOnLabels();
				}
				else
				{
					QCoreApplication::processEvents();
					imageWidget->ShowImage(cv::imread(".\\Resources\\Images\\previewNotAvailable.png"));
				}
			}
			else
			{
				QCoreApplication::processEvents();
				imageWidget->ShowImage(cv::imread(".\\Resources\\Images\\previewNotAvailable.png"));
			}
		}
		else
		{
			buttonIsEnabledFromParent->click();
			if (buttonIsEnabledFromParent->text() == "On")
			{
				TurnOnLabels();
			}
			else
			{
				QCoreApplication::processEvents();
				imageWidget->ShowImage(cv::imread(".\\Resources\\Images\\previewNotAvailable.png"));
			}
		}
	}
	else
	{
		buttonIsEnabledFromParent->click();
		if (buttonIsEnabledFromParent->text() == "Off")
		{
			QCoreApplication::processEvents();
			imageWidget->ShowImage(cv::imread(".\\Resources\\Images\\previewNotAvailable.png"));
			TurnOffLabels();
		}
	}
}
void CameraPreview::TurnOnOffRecognizeMode()
{
	buttonRecognationFromParent->click();
	ui.PBRecognize->setText(buttonRecognationFromParent->text());
	ui.PBRecognize->setStyleSheet(buttonRecognationFromParent->styleSheet());
	ui.PBRecognize->setToolTip(buttonRecognationFromParent->toolTip());
}