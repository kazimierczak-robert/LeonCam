#include "CameraPreview.h"

CameraPreview::CameraPreview(QWidget *parent, QString cameraDetails, QPushButton *buttonIsEnabledFromParent, QPushButton *buttonRecognationFromParent, OnvifClientDevice *onvifDevice, int camID, std::string passHash)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	this->buttonIsEnabledFromParent = buttonIsEnabledFromParent;
	this->buttonRecognationFromParent = buttonRecognationFromParent;
	this->onvifDevice = onvifDevice;
	this->camID = camID;
	this->passHash = passHash;

	designB = new DesignBase(this);
	ui.Lloading->setVisible(false);
	designB->SetGifInLabel(ui.Lloading);

	ui.LCameraDetails->setText(cameraDetails);

	this->capThread = new CapturingFrame(this);
	ptz = nullptr;
	ctrl = nullptr;

	connect(ui.PBCameraOnOff, SIGNAL(clicked()), this, SLOT(TurnOnOffCamera()));
	connect(ui.PBRecognize, SIGNAL(clicked()), this, SLOT(TurnOnOffRecognizeMode()));

	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));

	connect(ui.PBEdit, &QPushButton::clicked, this, [this, camID] {emit openCameraEdit(camID); });

	connect(ui.PBLeft, &QPushButton::pressed, this, [this] {ctrl->MoveCamera(-0.2, 0.0); });
	connect(ui.PBRight, &QPushButton::pressed, this, [this] {ctrl->MoveCamera(0.2, 0.0); });
	connect(ui.PBUp, &QPushButton::pressed, this, [this] {ctrl->MoveCamera(0.0, 0.2); });
	connect(ui.PBDown, &QPushButton::pressed, this, [this] {ctrl->MoveCamera(0.0, -0.2); });

	connect(ui.PBLeft, &QPushButton::released, this, [this] {ctrl->StopCamera(); });
	connect(ui.PBRight, &QPushButton::released, this, [this] {ctrl->StopCamera(); });
	connect(ui.PBUp, &QPushButton::released, this, [this] {ctrl->StopCamera(); });
	connect(ui.PBDown, &QPushButton::released, this, [this] {ctrl->StopCamera(); });

	connect(ui.PBHome, &QPushButton::clicked, this, [this] {ctrl->GoHomeCamera(); });

	connect(capThread, SIGNAL(turnOnLabels()), this, SLOT(TurnOnLabels()));
	connect(capThread, SIGNAL(updatePixmap(const QPixmap&)), this, SLOT(UpdatePixmap(const QPixmap&)));
	connect(parent, SIGNAL(closeCameraEdit(const QString&)), this, SLOT(CloseCameraEdit(const QString&)));

	/*_tptz__SetPresetResponse *res2 = new _tptz__SetPresetResponse();
	ptz->SetPreset(*res2, profileToken);

	_tptz__GetPresetsResponse *res = new _tptz__GetPresetsResponse();
	ptz->GetPresets(*res, profileToken);*/

	ui.PBCameraOnOff->setText(buttonIsEnabledFromParent->text());
	ui.PBCameraOnOff->setStyleSheet(buttonIsEnabledFromParent->styleSheet());

	ui.PBRecognize->setText(buttonRecognationFromParent->text());
	ui.PBRecognize->setStyleSheet(buttonRecognationFromParent->styleSheet());

	if (buttonIsEnabledFromParent->text() == "On")
	{
		designB->gif->start();
		ui.Lloading->setVisible(true);
		QFuture<void> future = QtConcurrent::run([=]()
		{
			int counter = 0;
			while (!StartShowingPreview() && counter < MAXCONNECTIONTRIES)
			{
				counter += 1;
			}
			if (counter == MAXCONNECTIONTRIES)
			{
				buttonIsEnabledFromParent->click();
			}
			designB->gif->stop();
		});
	}
	else
	{
		StopShowingPreview();
	}
}

CameraPreview::~CameraPreview()
{
	delete capThread;
	if (ptz != nullptr)
	{
		delete ptz;
	}
	if (ctrl != nullptr)
	{
		delete ctrl;
	}
}

void CameraPreview::TurnOnLabels()
{
	ui.PBCameraOnOff->setText("On");
	ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
	ui.PBUp->setEnabled(true);
	ui.PBDown->setEnabled(true);
	ui.PBLeft->setEnabled(true);
	ui.PBRight->setEnabled(true);
	ui.PBHome->setEnabled(true);
	ui.Lloading->setVisible(false);
}

bool CameraPreview::StartShowingPreview()
{
	if (onvifDevice->GetCapabilities() == 0)
	{
		OnvifClientMedia *media = new OnvifClientMedia(*onvifDevice);
		_trt__GetProfilesResponse *profiles = new _trt__GetProfilesResponse();
		media->GetProfiles(*profiles);
		if (profiles->Profiles.size() > 0)
		{
			this->profileToken = profiles->Profiles[0]->token;
			_trt__GetStreamUriResponse *link = new _trt__GetStreamUriResponse();
			media->GetStreamUrl(this->profileToken, *link);

			if (link->MediaUri != NULL)
			{
				this->ptz = new OnvifClientPTZ(*onvifDevice);
				ctrl = new CameraControl(ptz, profileToken);
				std::string login = "";
				std::string pass = "";
				onvifDevice->GetUserPasswd(login, pass);
				std::string streamURI = link->MediaUri->Uri.insert(link->MediaUri->Uri.find("//") + 2, login + ":" + pass + "@");
				capThread->SetStreamURI(streamURI);
				capThread->start();

				delete media;
				delete profiles;
				delete link;
				return true;
			}
			delete link;
		}
		delete media;
		delete profiles;
	}
	return false;
}
void CameraPreview::StopShowingPreview()
{
	ui.PBCameraOnOff->setText("Off");
	ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
	ui.PBUp->setEnabled(false);
	ui.PBDown->setEnabled(false);
	ui.PBLeft->setEnabled(false);
	ui.PBRight->setEnabled(false);
	ui.PBHome->setEnabled(false);
}

void CameraPreview::UpdatePixmap(const QPixmap& pixmap) 
{
	ui.LPreviewScreen->setPixmap(pixmap);
}

void CameraPreview::CloseCameraEdit(const QString& cameraDetails)
{
	ui.LCameraDetails->setText(cameraDetails);
	if (ui.PBCameraOnOff->text()=="On")
	{
		capThread->StopThread();
		capThread->wait();
		StopShowingPreview();
	}

	QSqlQuery *query = new QSqlQuery();
	query->prepare("SELECT IPAddress, Login, Password FROM Cameras WHERE CameraID=?");
	query->bindValue(0, camID);
	bool result = query->exec() == true ? true : false;
	if (result == true)
	{
		query->next();
		string url = "http://" + query->value(0).toString().toStdString() + "/onvif/device_service";
		string user = query->value(1).toString().toStdString();
		string pass = Utilities::GetDecrypted(passHash, query->value(2).toString().toStdString());

		onvifDevice = new OnvifClientDevice(url, user, pass);
	}

	if (ui.PBCameraOnOff->text() == "On")
	{
		designB->gif->start();
		ui.Lloading->setVisible(true);
		QFuture<void> future = QtConcurrent::run([=]()
		{
			int counter = 0;
			while (!StartShowingPreview() && counter < MAXCONNECTIONTRIES)
			{
				counter += 1;
			}
			if (counter == MAXCONNECTIONTRIES)
			{
				TurnOnOffCamera();
			}
			designB->gif->stop();
		});
	}
	delete query;
}

void CameraPreview::BackButtonClicked()
{
	this->close();
}

void CameraPreview::closeEvent(QCloseEvent *event)
{
	if (capThread->isRunning() == true)
	{
		capThread->StopThread();
		capThread->wait();
	}
	event->accept();
}

void CameraPreview::TurnOnOffCamera()
{
	if (ui.PBCameraOnOff->text() == "Off")
	{
		designB->gif->start();
		ui.Lloading->setVisible(true);
		QFuture<void> future = QtConcurrent::run([=]() 
		{
			int counter = 0;
			while (!StartShowingPreview() && counter < MAXCONNECTIONTRIES)
			{
				counter += 1;
			}
			if (counter < MAXCONNECTIONTRIES)
			{
				buttonIsEnabledFromParent->click();
			}
			designB->gif->stop();
		});
	}
	else
	{
		capThread->StopThread();
		capThread->wait();

		StopShowingPreview();
		buttonIsEnabledFromParent->click();
		ui.LPreviewScreen->clear();
	}
}

void CameraPreview::TurnOnOffRecognizeMode()
{
	buttonRecognationFromParent->click();
	ui.PBRecognize->setText(buttonRecognationFromParent->text());
	ui.PBRecognize->setStyleSheet(buttonRecognationFromParent->styleSheet());
}