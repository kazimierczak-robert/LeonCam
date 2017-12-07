#include "MainApp.h"

MainApp::MainApp(QWidget *parent, int loggedID, std::string passHash)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	activeCameraCounter = 0;

	this->loggedID = loggedID;
	this->passHash = passHash;
	//Get username by loggedID
	QSqlQuery query;
	query.prepare("SELECT Username FROM Users WHERE UserID = ?");
	query.bindValue(0, loggedID);
	bool result = query.exec();;
	if (result == true)
	{
		query.next();
		QString result = query.value(0).toString();
		if (result != "")
		{
			this->username = result;
		}
		else
		{
			this->username = loggedID;
		}
	}
	this->setWindowTitle(username + " - LeonCam");
	//
	vectorCameraLayoutsPages = new std::vector<std::vector<QGridLayout*>*>();
	vectorQGridLayouts = new std::vector<QGridLayout*>();
	cameraThread = new std::map<int, MainAppCamera *>();
	//Create ImgProc object and load face Cascade
	imgProc = new ImgProc(loggedID);
	imgProc->LoadFaceCascade();

	ui.LEnabledNumber->setText(ui.LEnabledNumber->text() + QVariant(QThread::idealThreadCount()).toString());

	FillFacesBaseTW();

	if (loggedID > 0)
	{
		//delete alerts
		query.clear();
		//Get RedAlertsDeleteSettings & GreenAlertsDeleteSettings
		query.prepare("SELECT RedAlertDeleteSettingID, GreenAlertDeleteSettingID FROM Users WHERE UserID = ?");
		query.bindValue(0, loggedID);
		result = query.exec();
		if (result == true && query.next())
		{
			redAlertDelSets = query.value(0).toInt();
			greenAlertDelSets = query.value(1).toInt();
			QSqlQuery selectedQuery;
			//1 - never				
			if (redAlertDelSets > 1)
			{
				query.clear();
				query.exec("BEGIN IMMEDIATE TRANSACTION");
				switch (redAlertDelSets)
				{
				case 2: //2 - 1 day
				{
					selectedQuery.prepare("SELECT RedAlertID, CameraID FROM RedAlerts WHERE (julianday('now')-julianday(StartDate)) >= 1 AND UserID = ?");
					query.prepare("DELETE FROM RedAlerts WHERE (julianday('now')-julianday(StartDate)) >= 1 AND UserID = ?");
					break;
				}
				case 3: //3 - 1 week
				{
					selectedQuery.prepare("SELECT RedAlertID, CameraID FROM RedAlerts WHERE (julianday('now')-julianday(StartDate)) >= 7 AND UserID = ?");
					query.prepare("DELETE FROM RedAlerts WHERE (julianday('now')-julianday(StartDate)) >= 7 AND UserID = ?");
					break;
				}
				case 4: //4 - 1 month
				{
					selectedQuery.prepare("SELECT RedAlertID, CameraID FROM RedAlerts WHERE (julianday('now')-julianday(StartDate)) >= 30 AND UserID = ?");
					query.prepare("DELETE FROM RedAlerts WHERE (julianday('now')-julianday(StartDate)) >= 30 AND UserID = ?");
					break;
				}
				case 5: //5 - half a year
				{
					selectedQuery.prepare("SELECT RedAlertID, CameraID FROM RedAlerts WHERE (julianday('now')-julianday(StartDate)) >= 183 AND UserID = ?");
					query.prepare("DELETE FROM RedAlerts WHERE (julianday('now')-julianday(StartDate)) >= 183 AND UserID = ?");
					break;
				}
				case 6: //6 - year
				{
					selectedQuery.prepare("SELECT RedAlertID, CameraID FROM RedAlerts WHERE (julianday('now')-julianday(StartDate)) >= 365 AND UserID = ?");
					query.prepare("DELETE FROM RedAlerts WHERE (julianday('now')-julianday(StartDate)) >= 365 AND UserID = ?");
				}
				}
				selectedQuery.bindValue(0, loggedID);
				result = selectedQuery.exec();
				if (result == true)
				{
					QFile file;
					QString fileName;
					while (selectedQuery.next())
					{
						
						fileName = ".\\RedAlerts\\" + QVariant(selectedQuery.value(1)).toString() + "\\" + QVariant(selectedQuery.value(0)).toString() + ".avi";
						file.remove(fileName);
					}
				}
				query.bindValue(0, loggedID);
				result = query.exec();
				query.exec("COMMIT");
			}
			if (greenAlertDelSets > 1)
			{
				query.clear();
				query.exec("BEGIN IMMEDIATE TRANSACTION");
				switch (greenAlertDelSets)
				{
				case 2: //2 - 1 day
				{
					query.prepare("DELETE FROM GreenAlerts WHERE (julianday('now')-julianday(StartDate)) >= 1 AND UserID = ?");
					break;
				}
				case 3: //3 - 1 week
				{
					query.prepare("DELETE FROM GreenAlerts WHERE (julianday('now')-julianday(StartDate)) >= 7 AND UserID = ?");
					break;
				}
				case 4: //4 - 1 month
				{
					query.prepare("DELETE FROM GreenAlerts WHERE (julianday('now')-julianday(StartDate)) >= 30 AND UserID = ?");
					break;
				}
				case 5: //5 - half a year
				{
					query.prepare("DELETE FROM GreenAlerts WHERE (julianday('now')-julianday(StartDate)) >= 183 AND UserID = ?");
					break;
				}
				case 6: //6 - year
				{
					query.prepare("DELETE FROM GreenAlerts WHERE (julianday('now')-julianday(StartDate)) >= 365 AND UserID = ?");
					break;
				}
				}
				query.bindValue(0, loggedID);
				result = query.exec();
				query.exec("COMMIT");
			}
		}
	}

	FillReportsTW();
	StatisticsChart();

	activeCameraPage = 0;

	AddTab();
	ui.TWCameraPages->setTabText(0, "");
	ui.TWCameraPages->setFocusPolicy(Qt::NoFocus);
	connect(ui.PBAddCamera, SIGNAL(clicked()), this, SLOT(AddCamera()));
	//logout: on close (logout and close), by clicking logout icon (only logout and switch to LogIn window)
	connect(this, SIGNAL(closed()), this, SLOT(LogOut()));
	connect(ui.PBLogout, SIGNAL(clicked()), this, SLOT(LogOut()), Qt::ConnectionType::QueuedConnection);
	connect(ui.LESearch, SIGNAL(textChanged(const QString&)), this, SLOT(LESearchChanged()));
	connect(ui.LESearch, SIGNAL(returnPressed()), this, SLOT(LESearchPressed()));
	connect(ui.TWCameraPages, SIGNAL(currentChanged(int)), this, SLOT(TWCameraPagesChanged(int)));
	//Faces base
	connect(ui.TWFacesBase, SIGNAL(CurentCellChanged(int, int)), this, SLOT(UpdateDBAfterCellChanged(int, int)));
	connect(ui.LESearchFB, SIGNAL(textChanged(const QString&)), this, SLOT(LESearchFBChanged()));
	connect(ui.PBAddPerson, SIGNAL(clicked()), this, SLOT(AddPerson()));
	connect(ui.LEUsername, SIGNAL(returnPressed()), this, SLOT(AddPerson()));
	connect(ui.LESurname, SIGNAL(returnPressed()), this, SLOT(AddPerson()));
	connect(ui.PBGreenAlert, &QPushButton::clicked, this, [this] {ChangeTWReport(0); });
	connect(ui.PBRedAlert, &QPushButton::clicked, this, [this] {ChangeTWReport(1); });
	//Reports
	connect(ui.CBSettings, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
		[=]() {CurrentIndexChanged(); });
	//Settings
	connect(ui.LEChangeLoginUsername, SIGNAL(returnPressed()), this, SLOT(ChangeLogin()));
	connect(ui.LEChangeLoginPassword, SIGNAL(returnPressed()), this, SLOT(ChangeLogin()));
	connect(ui.PBChangeLogin, SIGNAL(clicked()), this, SLOT(ChangeLogin()));

	connect(ui.LEChangePasswordOldPassword, SIGNAL(returnPressed()), this, SLOT(ChangePassword()));
	connect(ui.LEChangePasswordPassword, SIGNAL(returnPressed()), this, SLOT(ChangePassword()));
	connect(ui.LEChangePasswordConfPass, SIGNAL(returnPressed()), this, SLOT(ChangePassword()));
	connect(ui.PBChangePassword, SIGNAL(clicked()), this, SLOT(ChangePassword()));

	connect(ui.LEDeleteLoginUsername, SIGNAL(returnPressed()), this, SLOT(DeleteProfile()));
	connect(ui.LEDeleteProfilePassword, SIGNAL(returnPressed()), this, SLOT(DeleteProfile()));
	connect(ui.PBDeleteProfile, SIGNAL(clicked()), this, SLOT(DeleteProfile()));

	connect(ui.LEChangeSecQuestionPassword, SIGNAL(returnPressed()), this, SLOT(ChangeSecurityQuestion()));
	connect(ui.LEChangeSecQuestionSecQuest, SIGNAL(returnPressed()), this, SLOT(ChangeSecurityQuestion()));
	connect(ui.LEChangeSecQuestionNewAnswer, SIGNAL(returnPressed()), this, SLOT(ChangeSecurityQuestion()));
	connect(ui.PBChangeSecQuestion, SIGNAL(clicked()), this, SLOT(ChangeSecurityQuestion()));

	query.clear();
	query.prepare("SELECT CameraID FROM Cameras WHERE UserID = ?");
	query.bindValue(0, loggedID);
	result = query.exec();
	if (result == true)
	{
		while (query.next())
		{
			AddCameraFromDB(query.value(0).toInt());
		}
	}
}
MainApp::~MainApp()
{
	//Vector 1 level
	for (int j = vectorCameraLayoutsPages->size() - 1; j >= 0;j--)
	{
		//Vector 2 level
		for (int i= vectorCameraLayoutsPages->at(j)->size()-1; i >=0; i--)
		{
			DeleteCameraFromMemory(vectorCameraLayoutsPages->at(j)->at(i));
		}
		if (j == 0)
		{
			delete vectorCameraLayoutsPages->at(j);
		}
	}
	//Only this, above was deleting it content
	delete vectorQGridLayouts;
	if (vectorCameraLayoutsPages->size() == 0)
	{
		delete vectorCameraLayoutsPages;
	}

	if (imgProc != nullptr)
	{
		delete imgProc;
	}

	//delete map;
	delete cameraThread;

	//Remove row from table
	for (int i = ui.TWFacesBase->rowCount()-1; i >= 0; i--)
	{
		ui.TWFacesBase->removeCellWidget(i, 3);
		ui.TWFacesBase->removeCellWidget(i, 4);
		ui.TWFacesBase->removeCellWidget(i, 5);
		ui.TWFacesBase->removeCellWidget(i, 6);
		ui.TWFacesBase->removeRow(i);
	}
}
int MainApp::getCameraIDFromLayout(QGridLayout* layout)
{
	return ((QLabel *)layout->itemAtPosition(3, 0)->widget())->text().toInt();
}
void MainApp::AddCamera()
{
	if (vectorCameraLayoutsPages->size() == 20)
	{
		if (vectorCameraLayoutsPages->at(19)->size() == 6)
		{
			QMessageBox msgBox;
			msgBox.setText("Error: You can't assign more cameras to your profile");
			msgBox.exec();
			return;
		}
	}
	UserCamera *UserCam = new UserCamera(this, loggedID);
	bool result = UserCam->exec();
	if (result == QDialog::Accepted)
	{
		//vector includes values from QDialog
		std::vector<QString>* controlsValues = UserCam->GetValuesFromControls();

		QSqlQuery query;
		query.exec("BEGIN IMMEDIATE TRANSACTION");
		query.prepare("INSERT INTO Cameras (Name, IPAddress, Login, Password, UserID, LastEditDate) "
			"VALUES (:Name, :IPAddress, :Login, :Password, :UserID, :LastEditDate)");
		query.bindValue(":Name", controlsValues->at(0));
		query.bindValue(":IPAddress", controlsValues->at(1));
		query.bindValue(":Login", controlsValues->at(2));
		std::string encryptedMsg = Utilities::GetEncrypted(passHash, controlsValues->at(3).toStdString());
		query.bindValue(":Password", QString::fromStdString(encryptedMsg));
		query.bindValue(":UserID", loggedID);
		query.bindValue(":LastEditDate", Utilities::GetCurrentDateTime());
		result = query.exec();
		query.exec("COMMIT");
		if (result == true)
		{
			query.prepare("SELECT CameraID FROM Cameras WHERE Name = ? AND UserID = ?");
			query.bindValue(0, controlsValues->at(0));
			query.bindValue(1, loggedID);
			result = query.exec();
			if (result == true)
			{
				query.next();
				AddCameraFromDB(query.value(0).toInt());
			}
		}	
	}
}
void MainApp::AddCameraFromDB(int cameraID)
{
	QSqlQuery query;
	query.prepare("SELECT Name, IPAddress FROM Cameras WHERE CameraID=?");
	query.bindValue(0, cameraID);
	bool result = query.exec();
	if (result == true)
	{
		query.next();
		QGridLayout *layout = new QGridLayout();

		//Add thread do cameraThread map (combines layout camera with thread)
		cameraThread->insert(std::pair<int, MainAppCamera*>(cameraID, new MainAppCamera(imgProc, cameraID, this)));

		QPushButton* btn = new QPushButton();
		btn->setStyleSheet("background-image: url(:/Resources/Images/previewNotAvailableSmall.png);");
		btn->setFixedSize(216, 123);
		btn->setFocusPolicy(Qt::NoFocus);
		btn->setIconSize(QSize(216, 123));
		connect(btn, &QPushButton::clicked, this, [this, layout] {CameraSelected(layout); });
		layout->addWidget(btn, 0, 0, 1, 5);

		QLabel *label = new QLabel(query.value(0).toString() + " (" + query.value(1).toString() + ")");
		label->setStyleSheet("color:rgb(255, 255, 255);");
		label->setFixedSize(216, 23);
		label->setAlignment(Qt::AlignCenter);
		label->setFocusPolicy(Qt::NoFocus);
		layout->addWidget(label, 1, 0, 1, 5);

		btn = new QPushButton();
		btn->setText("Off");
		btn->setFixedSize(40, 40);
		btn->setFocusPolicy(Qt::NoFocus);
		btn->setToolTip("Start monitoring camera");
		btn->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
		connect(btn, &QPushButton::clicked, this, [this, layout] {TurnOnOffCamera(layout); });
		layout->addWidget(btn, 2, 0);

		btn = new QPushButton();
		btn->setFixedSize(40, 40);
		btn->setText("Off");
		btn->setFocusPolicy(Qt::NoFocus);
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOff.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOffHover.png);}");
		btn->setToolTip("Recognation mode: Off");
		if (imgProc->CheckIfModelTrained() && imgProc->CheckIfFaceCascadeExists())
		{
			connect(btn, &QPushButton::clicked, this, [this, btn, cameraID] {RecognitionCamera(btn, cameraID); });
		}
		layout->addWidget(btn, 2, 2);

		btn = new QPushButton();
		btn->setFixedSize(40, 40);
		btn->setFocusPolicy(Qt::NoFocus);
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/snapshot.png); border: none; margin: 0px; padding: 0px;} QPushButton:hover{background-image: url(:/Resources/Images/snapshotHover.png);}");
		btn->setToolTip("Take a picture (disabled)");
		layout->addWidget(btn, 2, 1);

		btn = new QPushButton();
		btn->setFixedSize(40, 40);
		btn->setFocusPolicy(Qt::NoFocus);
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/edit.png);border: none; margin: 0px; padding: 0px;} QPushButton:hover{background-image: url(:/Resources/Images/editHover.png);}");
		btn->setToolTip("Edit camera");
		connect(btn, &QPushButton::clicked, this, [this, cameraID, label, layout] {EditCamera(cameraID, label, (QPushButton*)layout->itemAtPosition(2, 0)->widget()); });
		layout->addWidget(btn, 2, 3);

		btn = new QPushButton();
		btn->setFixedSize(40, 40);
		btn->setFocusPolicy(Qt::NoFocus);
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/remove.png); border: none; margin: 0px; padding: 0px;} QPushButton:hover{background-image: url(:/Resources/Images/removeHover.png);}");
		btn->setToolTip("Remove camera");
		connect(btn, &QPushButton::clicked, this, [this, layout] { RemoveCamera(layout); });
		layout->addWidget(btn, 2, 4);

		label = new QLabel(QString::number(cameraID));
		label->setFixedSize(216, 1);
		label->setVisible(false);
		label->setFocusPolicy(Qt::NoFocus);
		label->setStyleSheet("color: transparent;");
		layout->addWidget(label, 3, 0, 1, 5);

		layout->setHorizontalSpacing(4);
		layout->setVerticalSpacing(2);

		if (vectorCameraLayoutsPages->at(vectorCameraLayoutsPages->size() - 1)->size() == 6)
		{
			AddTab();
			ui.TWCameraPages->setFocusPolicy(Qt::TabFocus);
		}
		else
		{
			ui.TWCameraPages->setCurrentIndex(vectorQGridLayouts->size() - 1);
		}

		vectorQGridLayouts->at(vectorQGridLayouts->size() - 1)->addLayout(layout, vectorCameraLayoutsPages->at(vectorCameraLayoutsPages->size() - 1)->size() / 3, vectorCameraLayoutsPages->at(vectorCameraLayoutsPages->size() - 1)->size() % 3);
		vectorCameraLayoutsPages->at(vectorCameraLayoutsPages->size() - 1)->push_back(layout);

		ui.LTotalNumber->setText("Total number of cameras: " + QString::number((vectorQGridLayouts->size() - 1) * 6 + vectorCameraLayoutsPages->at(vectorCameraLayoutsPages->size() - 1)->size()));
	}
	//else
	//{
	//	
	//}
}
void MainApp::AddTab()
{
	QGridLayout *newLayout = new QGridLayout();
	QWidget *newTab = new QWidget(ui.TWCameraPages);
	newTab->setLayout(newLayout);
	ui.TWCameraPages->addTab(newTab, "");

	vectorCameraLayoutsPages->push_back(new std::vector<QGridLayout*>());
	vectorQGridLayouts->push_back(newLayout);

	ui.TWCameraPages->setCurrentIndex(vectorQGridLayouts->size() - 1);

	ui.TWCameraPages->setStyleSheet("QTabWidget::pane {color: rgb(213, 235, 255);border: 0px;}QTabWidget::tab-bar {left: " + QString::number(360 - 18 * vectorQGridLayouts->size()) + "px;}QTabBar::tab {background-color: transparent;color: rgb(133, 196, 255);height: 18px;width: 36px;}QTabBar::tab:hover{color: rgb(160, 209, 255);}QTabBar::tab:selected{margin-top: -1px;color:rgb(219, 235, 255);}");

}
void MainApp::CameraSelected(QGridLayout* layout)
{
	int cameraID = getCameraIDFromLayout(layout);
	CameraPreview *cameraPreview = new CameraPreview(this, ((QLabel *)layout->itemAtPosition(1, 0)->widget())->text(), (QPushButton *)layout->itemAtPosition(2, 0)->widget(), (QPushButton *)layout->itemAtPosition(2, 2)->widget(), (QPushButton *)layout->itemAtPosition(2, 1)->widget(), cameraID, cameraThread, passHash);
	connect(cameraPreview, SIGNAL(openCameraEdit(int)), this, SLOT(OpenCameraEdit(int)));
	cameraThread->at(cameraID)->SetSendBigPicture(true);
	cameraPreview->exec();
	cameraThread->at(cameraID)->SetSendBigPicture(false);
	delete cameraPreview;
}
struct MainApp::Camera* MainApp::GetCameraFromDBByID(int cameraID)
{
	Camera *cam = nullptr;

	QSqlQuery query;
	query.prepare("SELECT Name, IPAddress, Login, Password FROM Cameras WHERE CameraID=?");
	query.bindValue(0, cameraID);
	bool result = query.exec();
	if (result == true)
	{
		while (query.next())
		{
			//fill cameras
			cam = new struct Camera;
			cam->CameraID = cameraID;
			cam->Name = query.value(0).toString().toStdString();
			cam->IPAddress = query.value(1).toString().toStdString();
			cam->Login = query.value(2).toString().toStdString();
			cam->Password = query.value(3).toString().toStdString();
		}
	}
	return cam;
}
void MainApp::UpdateThumbnail(const QPixmap& pixmap, int cameraID)
{
	for (int i = 0; i < vectorCameraLayoutsPages->size(); i++)
	{
		for (int j = 0; j < vectorCameraLayoutsPages->at(i)->size(); j++)
		{
			if (getCameraIDFromLayout(vectorCameraLayoutsPages->at(i)->at(j)) == cameraID)
			{
				((QPushButton*)vectorCameraLayoutsPages->at(i)->at(j)->itemAtPosition(0, 0)->widget())->setIcon(QIcon(pixmap));
				return;
			}
		}
	}
}
void MainApp::TurnOnOffCamera(QGridLayout* layout)
{

	int cameraID = getCameraIDFromLayout(layout);

	QPushButton *button = (QPushButton*)layout->itemAtPosition(2, 0)->widget();
	disconnect(button, &QPushButton::clicked, this, nullptr);
	if (button->text() == "Off")
	{
		if (activeCameraCounter == QThread::idealThreadCount())
		{
			Utilities::MBAlarm("You can't run more cameras simultaneously!", false);
			return;
		}

		bool result = false;

		layout->itemAtPosition(0, 0)->widget()->setStyleSheet("background-image: url(:/Resources/Images/ConnectingSmall.png);");
		QCoreApplication::processEvents();
		/*Face recognition*/

		//Set state of face recognition module
		bool state = ((QPushButton*)layout->itemAtPosition(2, 2)->widget())->text() == "On";
		cameraThread->at(cameraID)->ChangeFaceRecoState(state);
		//Set stream URI
		struct Camera *cam = GetCameraFromDBByID(cameraID);
		if (cam != nullptr)
		{
			//Decrypt passorrd
			std::string password = Utilities::GetDecrypted(passHash, cam->Password);
			//Get stream URI & start capturing frames thread 
			std::string url = "http://" + cam->IPAddress + "/onvif/device_service";
			OnvifClientDevice onvifDevice(url, cam->Login, password);
			if (onvifDevice.GetCapabilities() == 0)
			{
				OnvifClientMedia media(onvifDevice);
				_trt__GetProfilesResponse profiles;
				media.GetProfiles(profiles);

				if (profiles.Profiles.size() > 0)
				{
					string profileToken = profiles.Profiles[0]->token;
					int cameraFPS = profiles.Profiles[0]->VideoEncoderConfiguration->RateControl->FrameRateLimit;
					_trt__GetStreamUriResponse link;
					media.GetStreamUrl(profileToken, link);

					if (link.MediaUri != NULL)
					{
						std::string streamURI = link.MediaUri->Uri.insert(link.MediaUri->Uri.find("//") + 2, cam->Login + ":" + password + "@");							
						//Set stream URI
						cameraThread->at(cameraID)->SetStreamURI(streamURI);
						//Set camera ID
						cameraThread->at(cameraID)->SetCameraID(cameraID);
						//Set camera FPS
						cameraThread->at(cameraID)->SetFPS(cameraFPS);
						//Start thread
						cameraThread->at(cameraID)->start();
						connect(cameraThread->at(cameraID), SIGNAL(updateThumbnail(const QPixmap&, int)), this, SLOT(UpdateThumbnail(const QPixmap&, int)));
	
						button->setText("On");
						button->setToolTip("Stop monitoring camera");
						button->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
						layout->itemAtPosition(2, 1)->widget()->setToolTip("Take a picture");
						connect(layout->itemAtPosition(2, 1)->widget(), SIGNAL(clicked()), cameraThread->at(cameraID), SLOT(SaveMat()));
						activeCameraCounter += 1;
						result = true;
					}
				}
			}
		}
		if (result != true)
		{
			Utilities::MBAlarm("Cannot connect to this camera. Check camera details and your local network connection, then try again", false);
			layout->itemAtPosition(0, 0)->widget()->setStyleSheet("background-image: url(:/Resources/Images/previewNotAvailableSmall.png);");
		}
	}
	else
	{
		cameraThread->at(cameraID)->SetSendBigPicture(false);
		cameraThread->at(cameraID)->SetSendThumbnail(false);

		button->setText("Off");
		button->setToolTip("Start monitoring camera");
		button->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
		layout->itemAtPosition(2, 1)->widget()->setToolTip("Take a picture (disabled)");
		disconnect(layout->itemAtPosition(2, 1)->widget(), SIGNAL(clicked()), cameraThread->at(cameraID), SLOT(SaveMat()));
		activeCameraCounter -= 1;
		/*Face recognition*/

		//Stop thread
		cameraThread->at(cameraID)->StopThread();
		cameraThread->at(cameraID)->quit();//equivalent to exit(0==success)
		cameraThread->at(cameraID)->wait();
		QCoreApplication::processEvents();
		delete cameraThread->at(cameraID);
		cameraThread->at(cameraID) = new MainAppCamera(imgProc, cameraID, this);
		if (((QPushButton*)layout->itemAtPosition(2, 2)->widget())->text() == "On")
		{
			RecognitionCamera((QPushButton*)layout->itemAtPosition(2, 2)->widget(), cameraID);
		}
		layout->itemAtPosition(0, 0)->widget()->setStyleSheet("background-image: url(:/Resources/Images/previewNotAvailableSmall.png);");
		((QPushButton*)layout->itemAtPosition(0, 0)->widget())->setIcon(QIcon());
	}

	ui.LEnabledNumber->setText("Number of enabled cameras: " + QVariant(activeCameraCounter).toString() + "/" + QVariant(QThread::idealThreadCount()).toString());
	connect(button, &QPushButton::clicked, this, [this, layout] {TurnOnOffCamera(layout); });
}
void MainApp::RecognitionCamera(QPushButton* button, int cameraID)
{
	if (button->text() == "Off")
	{
		cameraThread->at(cameraID)->ChangeFaceRecoState(true);
		button->setText("On");
		button->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}");
	}
	else
	{
		cameraThread->at(cameraID)->ChangeFaceRecoState(false);
		button->setText("Off");
		button->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOff.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOffHover.png);}");
	}
}
void MainApp::EditCamera(int cameraID, QLabel *label, QPushButton *onOffButton)
{
	CameraEdition *cameraEdition = new CameraEdition(this, loggedID, cameraID, passHash);
	bool result = cameraEdition->exec();
	if (result == QDialog::Accepted)
	{
		//vector includes values from QDialog
		std::vector<QString>* controlsValues = cameraEdition->GetValuesFromControls();

		QSqlQuery query;
		query.exec("BEGIN IMMEDIATE TRANSACTION");
		if (controlsValues->at(3) == "")
		{
			query.prepare("UPDATE Cameras SET Name = ?, IPAddress = ?, Login = ?, LastEditDate = ? WHERE CameraID = ?");
			query.bindValue(4, cameraID);
		}
		else
		{
			query.prepare("UPDATE Cameras SET Name = ?, IPAddress = ?, Login = ?, LastEditDate = ?, Password = ? WHERE CameraID = ?");
			std::string encryptedMsg = Utilities::GetEncrypted(passHash, controlsValues->at(3).toStdString());
			query.bindValue(4, QString::fromStdString(encryptedMsg));
			query.bindValue(5, cameraID);
		}
		query.bindValue(0, controlsValues->at(0));
		query.bindValue(1, controlsValues->at(1));
		query.bindValue(2, controlsValues->at(2));
		query.bindValue(3, Utilities::GetCurrentDateTime());
		result = query.exec();
		query.exec("COMMIT");
		if (result == true)
		{
			label->setText(controlsValues->at(0) + " (" + controlsValues->at(1) + ")");
		}
		if (cameraThread->at(cameraID)->isRunning() == true && onOffButton != nullptr)
		{
			onOffButton->click();
			onOffButton->click();
		}
	}
	delete cameraEdition;
}
void MainApp::OpenCameraEdit(int cameraID)
{
	for (std::vector<QGridLayout*> *vec : *vectorCameraLayoutsPages)
	{
		for (QGridLayout *lt : *vec)
		{
			if (getCameraIDFromLayout(lt) == cameraID)
			{
				EditCamera(cameraID, (QLabel*)lt->itemAtPosition(1, 0)->widget(), nullptr);
				emit closeCameraEdit(((QLabel*)lt->itemAtPosition(1, 0)->widget())->text());
				return;
			}
		}
	}
}
void MainApp::DeleteCameraFromMemory(QGridLayout* layout)
{
	if (layout->count() > 1)
	{
		int cameraID = getCameraIDFromLayout(layout);
		if (cameraThread->find(cameraID) != cameraThread->end())
		{
			cameraThread->at(cameraID)->StopThread();
			cameraThread->at(cameraID)->quit();//equivalent to exit(0==success)
			cameraThread->at(cameraID)->wait();
			delete cameraThread->at(cameraID);
			cameraThread->erase(cameraID);
		}
	}
	int pageIndex = 0;
	for (const auto& item : *vectorCameraLayoutsPages)
	{
		if (std::find(item->begin(), item->end(), layout) != item->end())
		{
			int indexOfLayoutInPage = 0;
			for (indexOfLayoutInPage = 0; indexOfLayoutInPage < item->size(); indexOfLayoutInPage++)
			{
				if (item->at(indexOfLayoutInPage) == layout)
				{
					break;
				}
			}

			if (((QPushButton*)(layout->itemAt(2)->widget()))->text() == "On")
			{
				int numberEnabled = ui.LEnabledNumber->text().split(" ").last().split("/").first().toInt();
				ui.LEnabledNumber->setText("Number of enabled cameras: " + QVariant(numberEnabled - 1).toString() + "/" + QVariant(QThread::idealThreadCount()).toString());
			}
			int number = ui.LTotalNumber->text().split(" ").last().toInt();
			ui.LTotalNumber->setText("Total number of cameras: " + QVariant(number - 1).toString());

			//Removing all item in layout
			QLayoutItem * itemLayout;
			QWidget * widget;
			while ((itemLayout = layout->takeAt(0)))
			{
				if ((widget = itemLayout->widget()) != 0)
				{
					widget->hide();
					delete widget;
				}
				else
				{
					delete itemLayout;
				}
			}

			item->erase(std::remove(item->begin(), item->end(), layout), item->end());
			delete layout;

			while (pageIndex < vectorCameraLayoutsPages->size())
			{
				while (indexOfLayoutInPage < vectorCameraLayoutsPages->at(pageIndex)->size())
				{
					QLayoutItem* layoutToMove = vectorQGridLayouts->at(pageIndex)->itemAtPosition((indexOfLayoutInPage + 1) / 3, (indexOfLayoutInPage + 1) % 3);
					vectorQGridLayouts->at(pageIndex)->removeItem(layoutToMove);

					vectorQGridLayouts->at(pageIndex)->addLayout((QGridLayout *)layoutToMove, indexOfLayoutInPage / 3, indexOfLayoutInPage % 3);
					indexOfLayoutInPage += 1;
				}

				if ((pageIndex + 1) < vectorCameraLayoutsPages->size())
				{
					if (vectorCameraLayoutsPages->at(pageIndex + 1)->size() > 0)
					{
						QLayoutItem* layoutToMove = vectorQGridLayouts->at(pageIndex + 1)->itemAtPosition(0, 0);
						vectorQGridLayouts->at(pageIndex + 1)->removeItem(layoutToMove);

						vectorQGridLayouts->at(pageIndex)->addLayout((QGridLayout *)layoutToMove, 1, 2);

						vectorCameraLayoutsPages->at(pageIndex + 1)->erase(vectorCameraLayoutsPages->at(pageIndex + 1)->begin(), vectorCameraLayoutsPages->at(pageIndex + 1)->begin() + 1);
						vectorCameraLayoutsPages->at(pageIndex)->push_back((QGridLayout *)layoutToMove);

					}
					indexOfLayoutInPage = 0;
				}
				pageIndex += 1;
			}
			if (vectorCameraLayoutsPages->at(vectorCameraLayoutsPages->size() - 1)->size() == 0 && vectorQGridLayouts->size() > 1)
			{
				QGridLayout *qgridlayout = vectorQGridLayouts->at(vectorQGridLayouts->size() - 1);
				delete qgridlayout;
				vectorQGridLayouts->pop_back();

				std::vector<QGridLayout*> *vectorqlayout = vectorCameraLayoutsPages->at(vectorQGridLayouts->size());
				delete vectorqlayout;
				vectorCameraLayoutsPages->pop_back();

				if (activeCameraPage == vectorQGridLayouts->size())
				{
					ui.TWCameraPages->setCurrentIndex(vectorQGridLayouts->size() - 1);
					TWCameraPagesChanged(vectorQGridLayouts->size() - 1);
				}

				ui.TWCameraPages->removeTab(vectorQGridLayouts->size());
				ui.TWCameraPages->setStyleSheet("QTabWidget::pane {color: rgb(213, 235, 255);border: 0px;}QTabWidget::tab-bar {left: " + QString::number(360 - 18 * vectorQGridLayouts->size()) + "px;}QTabBar::tab {background-color: transparent;color: rgb(133, 196, 255);height: 18px;width: 36px;}QTabBar::tab:hover{color: rgb(160, 209, 255);}QTabBar::tab:selected{margin-top: -1px;color:rgb(219, 235, 255);}");

			}
			TWCameraPagesChanged(activeCameraPage);
			if (vectorQGridLayouts->size() == 1)
			{
				ui.TWCameraPages->setTabText(0, "");
				ui.TWCameraPages->setFocusPolicy(Qt::NoFocus);
			}
			break;
		}
		else
		{
			pageIndex += 1;
		}
	}
}
void MainApp::RemoveCamera(QGridLayout* layout)
{
	int cameraID = getCameraIDFromLayout(layout);
	QSqlQuery query;
	query.exec("BEGIN IMMEDIATE TRANSACTION");
	query.prepare("DELETE FROM Cameras WHERE CameraID=?");
	query.bindValue(0, cameraID);
	bool result = query.exec();
	query.exec("COMMIT");
	if (result == true)
	{
		DeleteCameraFromMemory(layout);
		query.clear();
		query.exec("BEGIN IMMEDIATE TRANSACTION");
		query.prepare("DELETE FROM GreenAlerts WHERE CameraID=?");
		query.bindValue(0, cameraID);
		query.exec();
		query.clear();
		query.prepare("DELETE FROM RedAlerts WHERE CameraID=?");
		query.bindValue(0, cameraID);
		query.exec();
		query.exec("COMMIT");
	}
}
void MainApp::LESearchChanged()
{
	if (ui.LESearch->text() == "")
	{
		return;
	}
	bool loopBreak = false;
	bool first = true;
	for (int i = activeCameraPage; i != activeCameraPage || first == true; i = (i + 1) % vectorCameraLayoutsPages->size())
	{
		first = false;
		for each (QGridLayout* oneLayout in *vectorCameraLayoutsPages->at(i))
		{
			if (((QLabel *)oneLayout->itemAtPosition(1, 0)->widget())->text().startsWith(ui.LESearch->text(), Qt::CaseInsensitive))
			{
				//activeCameraPage = i;
				ui.TWCameraPages->setCurrentIndex(i);
				oneLayout->itemAtPosition(1, 0)->widget()->setStyleSheet("color:rgb(255, 100, 100);");
				loopBreak = true;
			}
		}
		if (loopBreak == true)
		{
			QCoreApplication::processEvents();
			Sleep(500);
			for each (QGridLayout* oneLayout in *vectorCameraLayoutsPages->at(i))
			{
				oneLayout->itemAtPosition(1, 0)->widget()->setStyleSheet("color:rgb(255, 255, 255);");
			}
			break;
		}
	}
}
void MainApp::LESearchPressed()
{
	if (ui.LESearch->text() == "")
	{
		return;
	}
	bool loopBreak = false;
	bool first = true;
	for (int i = (activeCameraPage + 1) % vectorCameraLayoutsPages->size(); i != (activeCameraPage + 1) % vectorCameraLayoutsPages->size() || first == true; i = (i + 1) % vectorCameraLayoutsPages->size())
	{
		first = false;
		for each (QGridLayout* oneLayout in *vectorCameraLayoutsPages->at(i))
		{
			if (((QLabel *)oneLayout->itemAtPosition(1, 0)->widget())->text().startsWith(ui.LESearch->text(), Qt::CaseInsensitive))
			{
				//activeCameraPage = i;
				ui.TWCameraPages->setCurrentIndex(i);
				oneLayout->itemAtPosition(1, 0)->widget()->setStyleSheet("color:rgb(255, 100, 100);");
				loopBreak = true;
			}
		}
		if (loopBreak == true)
		{
			QCoreApplication::processEvents();
			Sleep(500);
			for each (QGridLayout* oneLayout in *vectorCameraLayoutsPages->at(i))
			{
				oneLayout->itemAtPosition(1, 0)->widget()->setStyleSheet("color:rgb(255, 255, 255);");
			}
			break;
		}
	}
}
void MainApp::TWCameraPagesChanged(int newIndex)
{
	int cameraID = -1;
	if (vectorCameraLayoutsPages->size() > activeCameraPage)
	{
		for each (QGridLayout* layout in *vectorCameraLayoutsPages->at(activeCameraPage))
		{
			cameraID = getCameraIDFromLayout(layout);
			cameraThread->at(cameraID)->SetSendThumbnail(false);
		}
	}
	ui.TWCameraPages->setTabText(activeCameraPage, QString::fromStdWString(L"\u25CB"));
	ui.TWCameraPages->setTabText(newIndex, QString::fromStdWString(L"\u25CF"));
	activeCameraPage = newIndex;
	if (vectorCameraLayoutsPages->size() > activeCameraPage)
	{
		for each (QGridLayout* layout in *vectorCameraLayoutsPages->at(activeCameraPage))
		{
			cameraID = getCameraIDFromLayout(layout);
			cameraThread->at(cameraID)->SetSendThumbnail(true);
		}
	}
}
void MainApp::LogOut()
{
	LogIn *login = new LogIn(nullptr);
	login->show();
	this->close();
}
void MainApp::closeEvent(QCloseEvent *event)
{
	//Get proper user from DB
	QSqlQuery query;
	query.prepare("SELECT COUNT (*) FROM Users WHERE Username = ?");
	query.bindValue(0, username);
	bool result = query.exec();
	if (result == true)
	{
		query.next();
		int result = query.value(0).toInt();
		if (result == 1)
		{
			//set LastLogoutDate
			query.clear();
			query.exec("BEGIN IMMEDIATE TRANSACTION");
			query.prepare("UPDATE Users SET LastLogoutDate = ? WHERE Username = ?");
			query.bindValue(0, Utilities::GetCurrentDateTime());
			query.bindValue(1, username);
			bool result = query.exec();
			query.exec("COMMIT");
			if (result == false)
			{
				Utilities::MBAlarm("User has not been logged out properly. Please, restart application.", false);
			}

		}
	}

	event->accept();
	delete this;
}
//Faces base
void MainApp::AdjustFaceBaseTW()
{
	//ui.TWFacesBase->horizontalHeader()->setSortIndicator(0, Qt::DescendingOrder);
	//Set adjusted column width
	ui.TWFacesBase->setColumnWidth(0, 0);//ID
	ui.TWFacesBase->setColumnWidth(1, 150);//Name
	ui.TWFacesBase->setColumnWidth(2, 150);//Surname
	ui.TWFacesBase->setColumnWidth(3, 95);//Go to the folder
	ui.TWFacesBase->setColumnWidth(4, 95);//Take a photo
	ui.TWFacesBase->setColumnWidth(5, 95);//Edit
	ui.TWFacesBase->setColumnWidth(6, 95);//Delete
	ui.TWFacesBase->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	//Disable dotted border
	ui.TWFacesBase->setFocusPolicy(Qt::NoFocus);
}
void MainApp::AdjustGreenReportsTW()
{
	ui.TWGreenReport->setColumnWidth(0, 0);//ID
	ui.TWGreenReport->setColumnWidth(1, 72);//CameraID
	ui.TWGreenReport->setColumnWidth(2, 0);//FaceID
	ui.TWGreenReport->setColumnWidth(3, 80);//Name
	ui.TWGreenReport->setColumnWidth(4, 80);//Surname
	ui.TWGreenReport->setColumnWidth(5, 118);//StartDate
	ui.TWGreenReport->setColumnWidth(6, 118);//StopDate
	ui.TWGreenReport->setColumnWidth(7, 68);//Go to the folder
	ui.TWGreenReport->setColumnWidth(8, 84);//Delete alert
	ui.TWGreenReport->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	//Disable dotted border
	ui.TWGreenReport->setFocusPolicy(Qt::NoFocus);
}
void MainApp::AdjustRedReportsTW()
{
	ui.TWRedReport->setColumnWidth(0, 0);//ID
	ui.TWRedReport->setColumnWidth(1, 72);//CameraID
	ui.TWRedReport->setColumnWidth(2, 118);//StartDate
	ui.TWRedReport->setColumnWidth(3, 118);//StopDate
	ui.TWRedReport->setColumnWidth(4, 87);//Go to the folder
	ui.TWRedReport->setColumnWidth(5, 87);//Open Movie
	ui.TWRedReport->setColumnWidth(6, 138);//Delete alert and photo
	ui.TWRedReport->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	//Disable dotted border
	ui.TWRedReport->setFocusPolicy(Qt::NoFocus);
}
void MainApp::AddRowToFB(int faceID, QString name, QString surname)
{
	ui.TWFacesBase->setSortingEnabled(false);
	QWidget *widget;
	QPushButton *button;
	QHBoxLayout *layout;
	QTableWidgetItem *item;
	int rowCount = ui.TWFacesBase->rowCount();

	//Inserts an empty row into the table at row
	ui.TWFacesBase->insertRow(ui.TWFacesBase->rowCount());

	//Set the widget in the cell
	item = new QTableWidgetItem(QVariant(faceID).toString());
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWFacesBase->setItem(rowCount, 0, item);

	item = new QTableWidgetItem(name);
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWFacesBase->setItem(rowCount, 1, item);

	item = new QTableWidgetItem(surname);
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWFacesBase->setItem(rowCount, 2, item);

	//New widget
	widget = new QWidget();
	//Button to go to the folder (in the cell)
	button = new QPushButton(ui.TWFacesBase);
	button->setFixedSize(25, 25);
	button->setStyleSheet("QPushButton{border-image: url(:/Resources/Images/folder.png) 0 0 0 0 stretch stretch; border: none; margin: 0px; padding: 0px;} QPushButton:hover{border-image: url(:/Resources/Images/folderHover.png) 0 0 0 0 stretch stretch;}");
	button->setFocusPolicy(Qt::NoFocus);
	//Layout
	layout = new QHBoxLayout(ui.TWFacesBase);
	layout->addWidget(button);
	layout->setAlignment(Qt::AlignCenter);
	layout->setContentsMargins(0, 0, 0, 0);
	//Set the layout on the widget
	widget->setLayout(layout);
	ui.TWFacesBase->setCellWidget(rowCount, 3, widget);
	connect(button, &QPushButton::clicked, this, [this, faceID] {Utilities::OpenFileExplorer(".\\FaceBase\\" + QVariant(faceID).toString()); });

	//New widget
	widget = new QWidget();
	//Button to take picture (in the cell)
	button = new QPushButton(ui.TWFacesBase);
	button->setFixedSize(25, 25);
	button->setStyleSheet("QPushButton{border-image: url(:/Resources/Images/snapshot.png) 0 0 0 0 stretch stretch; border: none; margin: 0px; padding: 0px;} QPushButton:hover{border-image: url(:/Resources/Images/snapshotHover.png) 0 0 0 0 stretch stretch;}");
	button->setFocusPolicy(Qt::NoFocus);
	//Layout
	layout = new QHBoxLayout(ui.TWFacesBase);
	layout->addWidget(button);
	layout->setAlignment(Qt::AlignCenter);
	layout->setContentsMargins(0, 0, 0, 0);
	//Set the layout on the widget
	widget->setLayout(layout);
	//Set the widget in the cell
	ui.TWFacesBase->setCellWidget(rowCount, 4, widget);
	connect(button, &QPushButton::clicked, this, [this, faceID] {TakePicture(faceID); });

	//New widget
	widget = new QWidget();
	//Button to edit person (in the cell)
	button = new QPushButton(ui.TWFacesBase);
	button->setFixedSize(25, 25);
	button->setStyleSheet("QPushButton{border-image: url(:/Resources/Images/edit.png) 0 0 0 0 stretch stretch; border: none; margin: 0px; padding: 0px;} QPushButton:hover{border-image: url(:/Resources/Images/editHover.png) 0 0 0 0 stretch stretch;}");
	button->setFocusPolicy(Qt::NoFocus);
	//Layout
	layout = new QHBoxLayout(ui.TWFacesBase);
	layout->addWidget(button);
	layout->setAlignment(Qt::AlignCenter);
	layout->setContentsMargins(0, 0, 0, 0);
	//Set the layout on the widget
	widget->setLayout(layout);
	//Set the widget in the cell
	ui.TWFacesBase->setCellWidget(rowCount, 5, widget);
	connect(button, &QPushButton::clicked, this, [this, faceID] {EditPerson(faceID); });

	//New widget
	widget = new QWidget();
	//Button to remove person (in the cell)
	button = new QPushButton(ui.TWFacesBase);
	button->setFixedSize(25, 25);
	button->setStyleSheet("QPushButton{border-image: url(:/Resources/Images/remove.png) 0 0 0 0 stretch stretch; border: none; margin: 0px; padding: 0px;} QPushButton:hover{border-image: url(:/Resources/Images/removeHover.png) 0 0 0 0 stretch stretch;}");
	button->setFocusPolicy(Qt::NoFocus);
	//Layout
	layout = new QHBoxLayout(ui.TWFacesBase);
	layout->addWidget(button);
	layout->setAlignment(Qt::AlignCenter);
	layout->setContentsMargins(0, 0, 0, 0);
	//Set the layout on the widget
	widget->setLayout(layout);
	//Set the widget in the cell
	ui.TWFacesBase->setCellWidget(rowCount, 6, widget);
	connect(button, &QPushButton::clicked, this, [this, faceID] {RemovePerson(faceID); });
	ui.TWFacesBase->setSortingEnabled(true);
}
void MainApp::AddRowToGreenReports(int greenAlertID, int cameraID, int faceID, QString name, QString surname, QString startDate, QString stopDate)
{
	ui.TWGreenReport->setSortingEnabled(false);
	QWidget *widget;
	QPushButton *button;
	QHBoxLayout *layout;
	QTableWidgetItem *item;
	int rowCount = ui.TWGreenReport->rowCount();

	//Inserts an empty row into the table at row
	ui.TWGreenReport->insertRow(ui.TWGreenReport->rowCount());

	//Set the widget in the cell
	item = new QTableWidgetItem(QVariant(greenAlertID).toString());
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWGreenReport->setItem(rowCount, 0, item);

	item = new QTableWidgetItem(QVariant(cameraID).toString());
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWGreenReport->setItem(rowCount, 1, item);

	item = new QTableWidgetItem(QVariant(faceID).toString());
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWGreenReport->setItem(rowCount, 2, item);

	item = new QTableWidgetItem(name);
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWGreenReport->setItem(rowCount, 3, item);

	item = new QTableWidgetItem(surname);
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWGreenReport->setItem(rowCount, 4, item);

	item = new QTableWidgetItem(startDate);
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWGreenReport->setItem(rowCount, 5, item);

	item = new QTableWidgetItem(stopDate);
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWGreenReport->setItem(rowCount, 6, item);

	//New widget
	widget = new QWidget();
	//Button to go to the folder (in the cell)
	button = new QPushButton(ui.TWGreenReport);
	button->setFixedSize(25, 25);
	button->setStyleSheet("QPushButton{border-image: url(:/Resources/Images/folder.png) 0 0 0 0 stretch stretch; border: none; margin: 0px; padding: 0px;} QPushButton:hover{border-image: url(:/Resources/Images/folderHover.png) 0 0 0 0 stretch stretch;}");
	button->setFocusPolicy(Qt::NoFocus);
	//Layout
	layout = new QHBoxLayout(ui.TWGreenReport);
	layout->addWidget(button);
	layout->setAlignment(Qt::AlignCenter);
	layout->setContentsMargins(0, 0, 0, 0);
	//Set the layout on the widget
	widget->setLayout(layout);
	ui.TWGreenReport->setCellWidget(rowCount, 7, widget);
	connect(button, &QPushButton::clicked, this, [this, faceID] {Utilities::OpenFileExplorer(".\\FaceBase\\" + QVariant(faceID).toString()); });

	//New widget
	widget = new QWidget();
	//Button to delete alert (in the cell)
	button = new QPushButton(ui.TWGreenReport);
	button->setFixedSize(25, 25);
	button->setStyleSheet("QPushButton{border-image: url(:/Resources/Images/remove.png) 0 0 0 0 stretch stretch; border: none; margin: 0px; padding: 0px;} QPushButton:hover{border-image: url(:/Resources/Images/removeHover.png) 0 0 0 0 stretch stretch;}");
	button->setFocusPolicy(Qt::NoFocus);
	//Layout
	layout = new QHBoxLayout(ui.TWGreenReport);
	layout->addWidget(button);
	layout->setAlignment(Qt::AlignCenter);
	layout->setContentsMargins(0, 0, 0, 0);
	//Set the layout on the widget
	widget->setLayout(layout);
	//Set the widget in the cell
	ui.TWGreenReport->setCellWidget(rowCount, 8, widget);
	connect(button, &QPushButton::clicked, this, [this, greenAlertID] {RemoveGreenAlert(greenAlertID); });
	ui.TWGreenReport->setSortingEnabled(true);
}
void MainApp::AddRowToRedReports(int redAlertID, int cameraID, QString startDate, QString stopDate)
{
	ui.TWRedReport->setSortingEnabled(false);
	QWidget *widget;
	QPushButton *button;
	QHBoxLayout *layout;
	QTableWidgetItem *item;
	int rowCount = ui.TWRedReport->rowCount();

	//Inserts an empty row into the table at row
	ui.TWRedReport->insertRow(ui.TWRedReport->rowCount());

	//Set the widget in the cell
	item = new QTableWidgetItem(QVariant(redAlertID).toString());
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWRedReport->setItem(rowCount, 0, item);

	item = new QTableWidgetItem(QVariant(cameraID).toString());
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWRedReport->setItem(rowCount, 1, item);

	item = new QTableWidgetItem(startDate);
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWRedReport->setItem(rowCount, 2, item);

	item = new QTableWidgetItem(stopDate);
	item->setFlags(item->flags() & ~Qt::ItemIsEditable);
	ui.TWRedReport->setItem(rowCount, 3, item);

	//New widget
	widget = new QWidget();
	//Button to go to the folder (in the cell)
	button = new QPushButton(ui.TWRedReport);
	button->setFixedSize(25, 25);
	button->setStyleSheet("QPushButton{border-image: url(:/Resources/Images/folder.png) 0 0 0 0 stretch stretch; border: none; margin: 0px; padding: 0px;} QPushButton:hover{border-image: url(:/Resources/Images/folderHover.png) 0 0 0 0 stretch stretch;}");
	button->setFocusPolicy(Qt::NoFocus);
	//Layout
	layout = new QHBoxLayout(ui.TWRedReport);
	layout->addWidget(button);
	layout->setAlignment(Qt::AlignCenter);
	layout->setContentsMargins(0, 0, 0, 0);
	//Set the layout on the widget
	widget->setLayout(layout);
	ui.TWRedReport->setCellWidget(rowCount, 4, widget);

	connect(button, &QPushButton::clicked, this, [this, cameraID, redAlertID] {	Utilities::OpenFileExplorer(".\\RedAlerts\\" + QVariant(cameraID).toString()); });

	//New widget
	widget = new QWidget();
	//Button to open movie (in the cell)
	button = new QPushButton(ui.TWRedReport);
	button->setFixedSize(25, 25);
	button->setStyleSheet("QPushButton{border-image: url(:/Resources/Images/movie.png) 0 0 0 0 stretch stretch; border: none; margin: 0px; padding: 0px;} QPushButton:hover{border-image: url(:/Resources/Images/movieHover.png) 0 0 0 0 stretch stretch;}");
	button->setFocusPolicy(Qt::NoFocus);
	//Layout
	layout = new QHBoxLayout(ui.TWRedReport);
	layout->addWidget(button);
	layout->setAlignment(Qt::AlignCenter);
	layout->setContentsMargins(0, 0, 0, 0);
	//Set the layout on the widget
	widget->setLayout(layout);
	//Set the widget in the cell
	ui.TWRedReport->setCellWidget(rowCount, 5, widget);		
	connect(button, &QPushButton::clicked, this, [this, cameraID, redAlertID] {	PlayMovie(".\\RedAlerts\\" + QVariant(cameraID).toString() + "\\" + QVariant(redAlertID).toString() + ".avi"); });
	ui.TWRedReport->setSortingEnabled(true);

	//New widget
	widget = new QWidget();
	//Button to delete alert (in the cell)
	button = new QPushButton(ui.TWRedReport);
	button->setFixedSize(25, 25);
	button->setStyleSheet("QPushButton{border-image: url(:/Resources/Images/remove.png) 0 0 0 0 stretch stretch; border: none; margin: 0px; padding: 0px;} QPushButton:hover{border-image: url(:/Resources/Images/removeHover.png) 0 0 0 0 stretch stretch;}");
	button->setFocusPolicy(Qt::NoFocus);
	//Layout
	layout = new QHBoxLayout(ui.TWRedReport);
	layout->addWidget(button);
	layout->setAlignment(Qt::AlignCenter);
	layout->setContentsMargins(0, 0, 0, 0);
	//Set the layout on the widget
	widget->setLayout(layout);
	//Set the widget in the cell
	ui.TWRedReport->setCellWidget(rowCount, 6, widget);
	connect(button, &QPushButton::clicked, this, [this, redAlertID] {RemoveRedAlert(redAlertID); });
	ui.TWRedReport->setSortingEnabled(true);
}
void MainApp::FillFacesBaseTW()
{
	AdjustFaceBaseTW();
	//http://doc.qt.io/qt-5/qhboxlayout.html
	//http://www.qtcentre.org/threads/3416-Center-a-widget-in-a-cell-on-a-QTableWidget
	//https://stackoverflow.com/a/14715980

	QSqlQuery query;
	query.prepare("SELECT * FROM Faces");
	bool result = query.exec();
	if (result == true)
	{
		while (query.next())
		{
			AddRowToFB(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString());
		}
	}
}
void MainApp::GetAlertDeleteSettings()
{
	QSqlQuery query;
	query.prepare("SELECT * FROM AlertsDeleteSettings");
	bool result = query.exec();
	if (result == true)
	{
		while (query.next())
		{
			alertDeleteSettingsToCB.insert(std::pair<int, std::string>(query.value(0).toInt(), query.value(1).toString().toStdString()));
		}
	}
}
void MainApp::FillCBSetsWithAlertDelSets()
{
	for (std::pair<int, std::string> elem : alertDeleteSettingsToCB)
	{
		ui.CBSettings->addItem(QString::fromStdString(elem.second), elem.first);
	}
}
void MainApp::FillReportsTW()
{
	AdjustGreenReportsTW();
	AdjustRedReportsTW();
	ui.TWRedReport->setVisible(false);
	GetAlertDeleteSettings();
	FillCBSetsWithAlertDelSets();
	ui.CBSettings->setCurrentIndex(ui.CBSettings->findData(greenAlertDelSets));
	//Fill green alerts
	QSqlQuery query;
	query.prepare("SELECT * FROM GreenAlerts WHERE UserID = ?");
	query.bindValue(0, loggedID);
	bool result = query.exec();
	if (result == true)
	{
		if (query.next())
		{		
			QSqlQuery queryFaces;
			queryFaces.prepare("SELECT FaceID, Name, Surname FROM Faces");
			result = queryFaces.exec();
			if (result == true)
			{
				do
				{
					queryFaces.seek(-1, false);
					//size() no supported
					while (queryFaces.next())
					{
						if (queryFaces.value(0).toInt() == query.value(1).toInt())
						{
							AddRowToGreenReports(query.value(0).toInt(), query.value(2).toInt(), query.value(1).toInt(), queryFaces.value(1).toString(), queryFaces.value(2).toString(), query.value(3).toString(), query.value(4).toString());
							break;
						}
					}
				} while (query.next());
			}
		}
	}
	//Fill red alerts
	query.clear();
	query.prepare("SELECT * FROM RedAlerts WHERE UserID = ?");
	query.bindValue(0, loggedID);
	result = query.exec();
	if (result == true)
	{
		while (query.next())
		{
			AddRowToRedReports(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toString(), query.value(3).toString());
		}
	}
}
void MainApp::UpdateDBAfterCellChanged(int row, int column)
{
	Utilities::MBAlarm("DB Update " + QVariant(row).toString() + " " + QVariant(column).toString(), true);
}
void MainApp::TakePicture(int faceID)
{
	QString name;
	QString surname;
	//Search in table
	for (int i = 0; i < ui.TWFacesBase->rowCount(); i++)
	{
		if (faceID == ui.TWFacesBase->item(i, 0)->text().toInt())
		{
			name=ui.TWFacesBase->item(i, 1)->text();
			surname = ui.TWFacesBase->item(i, 2)->text();
		}
	}
	//vector of ON cameras ID
	std::vector<int> cameraIDs;
	for (std::vector<QGridLayout*> *vec : *vectorCameraLayoutsPages)
	{
		for (QGridLayout *lt: *vec)
		{
			//3 row and 1 column - check if OnOff button is On or not
			QPushButton *button = (QPushButton*)lt->itemAtPosition(2, 0)->widget();
			if (button->text() == "On")
			{
				cameraIDs.push_back(getCameraIDFromLayout(lt));
			}
		}
	}

	if (cameraIDs.empty())
	{
		Utilities::MBAlarm("No camera is turned on! You can't take a photo", false);
		return;
	}
	if (imgProc->CheckIfFaceCascadeExists() == false)
	{
		Utilities::MBAlarm("lbpcascade_frontalface.xml doesn't exist", false);
		return;
	}
	if (imgProc->CheckIfFaceCascadeLoaded() == false)
	{
		Utilities::MBAlarm("CascadeClassifier hasn't been loaded, please try take photo again", false);
		return;
	}
	else 
	{
		NewPhoto *newPhoto = new NewPhoto(cameraIDs, passHash, name, surname, loggedID, faceID, imgProc, cameraThread, this);
		newPhoto->exec();
		delete newPhoto;
		//update model
		imgProc->GetModel()->update(imgProc->GetImages(), imgProc->GetLabels());
		imgProc->ClearImagesVector();
		imgProc->ClearLabelsVector();
	}
}
void MainApp::LESearchFBChanged()
{
	QString typedSurname = ui.LESearchFB->text();
	for (int i = 0; i < ui.TWFacesBase->rowCount(); i++)
	{
		if (ui.TWFacesBase->item(i, 2)->text().startsWith(typedSurname, Qt::CaseInsensitive))
		{
			ui.TWFacesBase->showRow(i);
		}
		else
		{
			ui.TWFacesBase->hideRow(i);
		}
	}
}
void MainApp::AddPerson()
{
	QString name = ui.LEUsername->text();
	QString surname = ui.LESurname->text();
	int ID = 0;
	if (name != "" && surname != "") 
	{
		//Add row to DB
		QSqlQuery query;
		query.exec("BEGIN IMMEDIATE TRANSACTION");
		query.prepare("INSERT INTO Faces (Name, Surname, LastEditedBy, LastEditDate) VALUES (?, ?, ?, ?)");
		query.addBindValue(name);
		query.addBindValue(surname);
		int loggedID = this->loggedID;
		query.addBindValue(loggedID);
		QString currentDateTimeS = Utilities::GetCurrentDateTime();
		query.addBindValue(currentDateTimeS);
		bool result;
		result = query.exec();
		query.exec("COMMIT");
		if (result == true)
		{
			int faceID = query.lastInsertId().toInt();
			if (faceID>0)
			{ 
				AddRowToFB(faceID, name, surname);
				ui.LEUsername->setText("");
				ui.LESurname->setText("");
			}
		}
		else
		{
			Utilities::MBAlarm("DB error. Person hasn't been added to DB", false);
		}
	}
	else
	{
		Utilities::MBAlarm("At least one field is incomplete", false);
	}

}
void MainApp::EditPerson(int faceID)
{
	for (int i = 0; i < ui.TWFacesBase->rowCount(); i++)
	{
		if (faceID == ui.TWFacesBase->item(i, 0)->text().toInt())
		{
			//Create Qdialog
			QDialog *qDialog = new QDialog(0, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
			QPixmap pixmap(iconPath);
			QIcon ButtonIcon(pixmap);
			qDialog->setWindowIcon(ButtonIcon);

			QDialogButtonBox *dialogBB = new QDialogButtonBox();
			dialogBB->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

			QFormLayout *formLayout = new QFormLayout();
			QLabel *nameL = new QLabel();
			nameL->setText("Name:");
			QLineEdit *nameLE = new QLineEdit();
			//Set name form table
			nameLE->setText(ui.TWFacesBase->item(i, 1)->text());

			QLabel *surnameL = new QLabel();
			surnameL->setText("Surname:");
			QLineEdit *surnameLE = new QLineEdit();
			//Set surname from table
			surnameLE->setText(ui.TWFacesBase->item(i, 2)->text());

			//Check if fields are empty
			connect(nameLE, &QLineEdit::textEdited, this, [this, nameLE, surnameLE, dialogBB]
			{
				if (nameLE->text() == "" || surnameLE->text() == "")
				{
					dialogBB->button(QDialogButtonBox::Ok)->setDisabled(true);
				}
				else
				{
					dialogBB->button(QDialogButtonBox::Ok)->setEnabled(true);
				}
			});
			connect(surnameLE, &QLineEdit::textEdited, this, [this, nameLE, surnameLE, dialogBB]
			{
				if (surnameLE->text() == "" || nameLE->text() == "")
				{
					dialogBB->button(QDialogButtonBox::Ok)->setDisabled(true);
				}
				else
				{
					dialogBB->button(QDialogButtonBox::Ok)->setEnabled(true);
				}
			});

			formLayout->addRow(nameL, nameLE);
			formLayout->addRow(surnameL, surnameLE);

			QGridLayout *gridLayout = new QGridLayout();
			gridLayout->addLayout(formLayout, 0, 0, 1, 2, Qt::AlignCenter);

			qDialog->setLayout(gridLayout);

			gridLayout->addWidget(dialogBB, 3, 0, 1, 2, Qt::AlignRight);
			qDialog->adjustSize();
			qDialog->setMinimumSize(qDialog->width(), qDialog->height());
			qDialog->setMaximumSize(qDialog->width(), qDialog->height());

			connect(dialogBB, SIGNAL(accepted()), qDialog, SLOT(accept()));
			connect(dialogBB, SIGNAL(rejected()), qDialog, SLOT(reject()));

			int result = qDialog->exec();
			if (result == QDialog::Accepted)
			{
				if (nameLE->text() != "" && surnameLE->text() != "") 
				{
					//Update row in DB
					QSqlQuery query;
					query.exec("BEGIN IMMEDIATE TRANSACTION");
					query.clear();
					query.prepare("UPDATE Faces SET Name = ?, Surname = ?, LastEditedBy = ?, LastEditDate = ?  WHERE FaceID = ?");
					query.bindValue(0, nameLE->text());
					query.bindValue(1, surnameLE->text());
					query.bindValue(2, this->loggedID);
					query.bindValue(3, Utilities::GetCurrentDateTime());
					query.bindValue(4, faceID);
					bool result = query.exec();
					query.exec("COMMIT");
					if (result == false)
					{
						Utilities::MBAlarm("DB problem. Please, try update fields again", false);
					}
					else
					{
						ui.TWFacesBase->item(i, 1)->setText(nameLE->text());
						ui.TWFacesBase->item(i, 2)->setText(surnameLE->text());
					}
				}
			}
			break;
		}
	}
}
void MainApp::RemovePerson(int faceID)
{
	if (Utilities::MBQuestion("<b>Warning</b>: Are you sure, you want to <b>remove</b> person with ID: " + ((QVariant)faceID).toString() + "?"))
	{
		//Remove row from table
		for (int i = 0; i < ui.TWFacesBase->rowCount(); i++)
		{
			if (faceID == ui.TWFacesBase->item(i, 0)->text().toInt())
			{
				ui.TWFacesBase->removeCellWidget(i, 3);
				ui.TWFacesBase->removeCellWidget(i, 4);
				ui.TWFacesBase->removeCellWidget(i, 5);
				ui.TWFacesBase->removeCellWidget(i, 6);
				ui.TWFacesBase->removeRow(i);
				break;
			}
		}

		//Remove from Faces DB
		QSqlQuery query;
		query.exec("BEGIN IMMEDIATE TRANSACTION");
		query.exec("DELETE FROM Faces WHERE FaceID = ?");
		query.bindValue(0, faceID);
		bool result = query.exec();
		query.exec("COMMIT");
		if (result == false)
		{
			Utilities::MBAlarm("Something went wrong. Row hasn't been deleted", false);
		}
		else
		{
			Utilities::RemoveFolderRecursively(".\\FaceBase\\" + QVariant(faceID).toString());
			//Remove trained model file if parson has been removed
			QFile file;
			file.remove(".\\TrainedFaceRecognizer.xml");
		}
		//Delete from GreenAlert
		query.clear();
		query.exec("BEGIN IMMEDIATE TRANSACTION");
		query.exec("DELETE FROM GreenAlerts WHERE FaceID = ?");
		query.bindValue(0, faceID);
		query.exec();
		query.exec("COMMIT");
	}
}
void MainApp::RemoveGreenAlert(int greenAlertID)
{
	int cameraID = -1;
	if (Utilities::MBQuestion("<b>Warning</b>: Are you sure, you want to <b>remove</b> green alert with ID: " + ((QVariant)greenAlertID).toString() + "?"))
	{
		//Remove row from table
		for (int i = 0; i < ui.TWGreenReport->rowCount(); i++)
		{
			if (greenAlertID == ui.TWGreenReport->item(i, 0)->text().toInt())
			{
				cameraID = ui.TWGreenReport->item(i, 1)->text().toInt();
				ui.TWGreenReport->removeCellWidget(i, 7);
				ui.TWGreenReport->removeCellWidget(i, 8);
				ui.TWGreenReport->removeRow(i);
				break;
			}
		}
		QSqlQuery query;
		QString startGreenDate;
		query.exec("SELECT StartDate FROM GreenAlerts WHERE GreenAlertID = ?");
		query.bindValue(0, greenAlertID);
		bool result = query.exec();
		if (result == true)
		{
			query.next();
			startGreenDate = query.value(0).toString();
		}
		//Remove from DB
		query.clear();
		query.exec("BEGIN IMMEDIATE TRANSACTION");
		query.exec("DELETE FROM GreenAlerts WHERE GreenAlertID = ?");
		query.bindValue(0, greenAlertID);
		result = query.exec();
		query.exec("COMMIT");
		if (result == false)
		{
			Utilities::MBAlarm("Something went wrong. Row hasn't been deleted", false);
		}
		if (cameraID > -1)
		{
			connect(this, SIGNAL(checkGreenAlertInList(int)), cameraThread->at(cameraID), SLOT(CheckGreenAlertInList(int)));
			emit checkGreenAlertInList(greenAlertID);
			disconnect(this, SIGNAL(checkGreenAlertInList(int)), cameraThread->at(cameraID), SLOT(CheckGreenAlertInList(int)));
			//Difference should be 0 in most cases, but it can be >0 or <0
			//todayDateTime = QDateTime::fromString("2017-11-20 21:40:00", "yyyy-MM-dd HH:mm:ss");
			int diff = (todayDateTime.date()).daysTo(QDateTime::fromString(Utilities::GetCurrentDateTime(), "yyyy-MM-dd HH:mm:ss").date());
			QChart *chart = ((QChartView*)ui.VLLayout->itemAt(0)->widget())->chart();
			QBarSeries *series = (QBarSeries *)chart->series().at(0);
			QBarSet *setGreen = series->barSets().at(1);
			int greenDiff = (QDateTime::fromString(startGreenDate, "yyyy-MM-dd HH:mm:ss").date()).daysTo(QDateTime::fromString(Utilities::GetCurrentDateTime(), "yyyy-MM-dd HH:mm:ss").date());
			if (greenDiff < 7)
			{
				int value = setGreen->at(6 - greenDiff);
				value--;
				weekChartGreenMap[greenDiff]--;
				setGreen->replace(6 - greenDiff, value);
				int range = GetChartRange();
				chart->axisY()->setRange(0, range);
			}
			if (diff != 0)
			{
				//Data for bar series: second has people counter on <today - diff> position
				for (int i = 6; i > 0; i--)
				{
					weekChartGreenMap[i] = weekChartGreenMap[i - 1];
					weekChartRedMap[i] = weekChartRedMap[i - 1];
				}
				//Move week names by 1
				weekChartGreenMap[0] = 0;
				QString category0 = ((QBarCategoryAxis *)(chart->axisX()))->at(0);
				((QBarCategoryAxis *)(chart->axisX()))->remove(category0);
				((QBarCategoryAxis *)(chart->axisX()))->append(category0);
				chart->axisX()->setRange(((QBarCategoryAxis *)(chart->axisX()))->at(0),	((QBarCategoryAxis *)(chart->axisX()))->at(6));

				setGreen->remove(0);
				setGreen->append(0);

				//move red
				weekChartRedMap[0] = 0;

				QBarSet *setRed = series->barSets().at(0);
				setRed->remove(0);
				setRed->append(0);

				todayDateTime = QDateTime::fromString(Utilities::GetCurrentDateTime(), "yyyy-MM-dd HH:mm:ss");
				int range = GetChartRange();
				chart->axisY()->setRange(0, range);
			}
		}
	}
}
void MainApp::RemoveRedAlert(int redAlertID)
{
	int cameraID = -1;

	if (Utilities::MBQuestion("<b>Warning</b>: Are you sure, you want to <b>remove</b> red alert with ID: " + ((QVariant)redAlertID).toString() + "?"))
	{
		//Remove row from table
		for (int i = 0; i < ui.TWRedReport->rowCount(); i++)
		{
			if (redAlertID == ui.TWRedReport->item(i, 0)->text().toInt())
			{
				cameraID = ui.TWRedReport->item(i, 1)->text().toInt();
				ui.TWRedReport->removeCellWidget(i, 4);
				ui.TWRedReport->removeCellWidget(i, 5);
				ui.TWRedReport->removeCellWidget(i, 6);
				ui.TWRedReport->removeRow(i);
				break;
			}
		}
		QSqlQuery query;
		QString startRedDate;
		query.exec("SELECT StartDate FROM RedAlerts WHERE RedAlertID = ?");
		query.bindValue(0, redAlertID);
		bool result = query.exec();
		if (result == true)
		{
			query.next();
			startRedDate = query.value(0).toString();
		}

		//Remove from DB
		query.clear();
		query.exec("BEGIN IMMEDIATE TRANSACTION");
		query.exec("DELETE FROM RedAlerts WHERE RedAlertID = ?");
		query.bindValue(0, redAlertID);
		result = query.exec();
		query.exec("COMMIT");
		if (result == false)
		{
			Utilities::MBAlarm("Something went wrong. Row hasn't been deleted", false);
		}
		else
		{
			if (cameraID > -1)
			{
				connect(this, SIGNAL(checkRedAlertID(int)), cameraThread->at(cameraID), SLOT(CheckRedAlertID(int)));
				emit checkRedAlertID(redAlertID);
				disconnect(this, SIGNAL(checkRedAlertID(int)), cameraThread->at(cameraID), SLOT(CheckRedAlertID(int)));
			}
			//Difference should be 0 in most cases, but it can be >0 or <0
			int diff = (todayDateTime.date()).daysTo(QDateTime::fromString(Utilities::GetCurrentDateTime(), "yyyy-MM-dd HH:mm:ss").date());
			QChart *chart = ((QChartView*)ui.VLLayout->itemAt(0)->widget())->chart();
			QBarSeries *series = (QBarSeries *)chart->series().at(0);
			QBarSet *setRed = series->barSets().at(0);
			int redDiff = (QDateTime::fromString(startRedDate, "yyyy-MM-dd HH:mm:ss").date()).daysTo(QDateTime::fromString(Utilities::GetCurrentDateTime(), "yyyy-MM-dd HH:mm:ss").date());
			if (redDiff < 7)
			{
				int value = setRed->at(6 - redDiff);
				value--;
				weekChartRedMap[redDiff]--;
				setRed->replace(6 - redDiff, value);
				int range = GetChartRange();
				chart->axisY()->setRange(0, range);
			}
			if (diff != 0)
			{
				//Data for bar series: second has people counter on <today - diff> position
				for (int i = 6; i > 0; i--)
				{
					weekChartGreenMap[i] = weekChartGreenMap[i - 1];
					weekChartRedMap[i] = weekChartRedMap[i - 1];
				}

				//Move week names by 1
				weekChartGreenMap[0] = 0;

				QString category0 = ((QBarCategoryAxis *)(chart->axisX()))->at(0);
				((QBarCategoryAxis *)(chart->axisX()))->remove(category0);
				((QBarCategoryAxis *)(chart->axisX()))->append(category0);
				chart->axisX()->setRange(((QBarCategoryAxis *)(chart->axisX()))->at(0), ((QBarCategoryAxis *)(chart->axisX()))->at(6));

				setRed->remove(0);
				setRed->append(0);

				//move red
				weekChartRedMap[0] = 0;

				QBarSet *setGreen = series->barSets().at(1);
				setGreen->remove(0);
				setGreen->append(0);

				todayDateTime = QDateTime::fromString(Utilities::GetCurrentDateTime(), "yyyy-MM-dd HH:mm:ss");
				int range = GetChartRange();
				chart->axisY()->setRange(0, range);
			}

			QFile file;
			QString fileName = ".\\RedAlerts\\" + QVariant(cameraID).toString() + "\\" + QVariant(redAlertID).toString() + ".avi";
			file.remove(fileName);
		}
	}
}
void MainApp::ChangeTWReport(int i)
{
	greenOrRedAlert = i;
	if (greenOrRedAlert == 1) //TWGreenReport is active
	{
		ui.TWGreenReport->setVisible(false);
		ui.TWRedReport->setVisible(true);
		ui.LChooseAlertDelSet->setStyleSheet("QLabel{color: rgb(255, 255, 255);background-color: rgb(255, 77, 61);}");
		ui.CBSettings->setCurrentIndex(ui.CBSettings->findData(redAlertDelSets));

	}
	else
	{
		ui.TWGreenReport->setVisible(true);
		ui.TWRedReport->setVisible(false);
		ui.LChooseAlertDelSet->setStyleSheet("QLabel{color: rgb(255, 255, 255);background-color:rgb(36, 118, 59);}");
		ui.CBSettings->setCurrentIndex(ui.CBSettings->findData(greenAlertDelSets));
	}
}
void MainApp::PlayMovie(QString path)
{
	if (Utilities::NotEmptyFileExists(path))
	{
		//ShellExecuteA(0, 0, (LPCSTR)path.toStdString().c_str(), 0, 0, SW_SHOW);
		QDesktopServices::openUrl(QUrl::fromLocalFile(path));
	}
	else
	{
		Utilities::MBAlarm("No movie associated with the alert", false);
	}
}
void MainApp::CurrentIndexChanged()
{
	//Get selected ID
	int settingID = ui.CBSettings->currentData().toInt();
	//Get User from DB with ID <loggedID>
	QSqlQuery query;
	query.prepare("SELECT COUNT(*) FROM Users WHERE UserID=?");
	query.bindValue(0, loggedID);
	bool result = query.exec();
	if (result == true)
	{
		query.next();
		int counter = query.value(0).toInt();
		if (counter == 1) //Somebody delete account...
		{
			//Update <loggedID> user settings
			query.clear();
			query.exec("BEGIN IMMEDIATE TRANSACTION");
			//Check if green or Red
			if (greenOrRedAlert == 0)//0 - green
			{
				greenAlertDelSets = settingID;
				query.prepare("UPDATE Users SET GreenAlertDeleteSettingID = ?  WHERE UserID = ?");
			}
			else //1 - red
			{
				redAlertDelSets = settingID;
				query.prepare("UPDATE Users SET RedAlertDeleteSettingID = ?  WHERE UserID = ?");
			}			

			query.bindValue(0, settingID);
			query.bindValue(1, loggedID);
			bool result = query.exec();
			query.exec("COMMIT");
			if (result == false)
			{
				Utilities::MBAlarm("Account error has occured. Please log in again", false);
				LogOut();
			}
		}
		else
		{
			Utilities::MBAlarm("Account error has occured. Please log in again", false);
			LogOut();
		}
	}
}
void MainApp::InsertGreenAlert(int greenAlertID, int faceID, int cameraID, QString dateTimeNow)
{
	QSqlQuery query;
	query.prepare("SELECT Name, Surname FROM Faces WHERE FaceID = ?");
	query.bindValue(0, faceID);
	bool result = query.exec();

	if (result == true)
	{
		query.next();
		QString name = query.value(0).toString();
		QString surname = query.value(1).toString();
		AddRowToGreenReports(greenAlertID, cameraID, faceID, name, surname, dateTimeNow, dateTimeNow);
		//Difference should be 0 in most cases, but it can be >0
		//todayDateTime = QDateTime::fromString("2017-11-20 21:40:00", "yyyy-MM-dd HH:mm:ss");
		int diff = (todayDateTime.date()).daysTo(QDateTime::fromString(dateTimeNow, "yyyy-MM-dd HH:mm:ss").date());
		QChart *chart = ((QChartView*)ui.VLLayout->itemAt(0)->widget())->chart();
		QBarSeries *series = (QBarSeries *)chart->series().at(0);
		QBarSet *setGreen = series->barSets().at(1);
		if (diff == 0) 
		{
			int value = setGreen->at(setGreen->count() - 1);
			value++;
			weekChartGreenMap[0]++;
			setGreen->replace(setGreen->count() - 1, value);
			int range = GetChartRange();
			chart->axisY()->setRange(0, range);
		}
		else
		{
			//Data for bar series: second has people counter on <today - diff> position
			for (int i = 6; i >0; i--)
			{
				weekChartGreenMap[i] = weekChartGreenMap[i - 1];
				weekChartRedMap[i] = weekChartRedMap[i - 1];
			}

			//Move week names by 1
			weekChartGreenMap[0] = 1;

			QString category0 = ((QBarCategoryAxis *)(chart->axisX()))->at(0);
			((QBarCategoryAxis *)(chart->axisX()))->remove(category0);
			((QBarCategoryAxis *)(chart->axisX()))->append(category0);
			chart->axisX()->setRange(((QBarCategoryAxis *)(chart->axisX()))->at(0), ((QBarCategoryAxis *)(chart->axisX()))->at(6));

			setGreen->remove(0);
			setGreen->append(1);

			//move red
			weekChartRedMap[0] = 0;

			QBarSet *setRed= series->barSets().at(0);
			setRed->remove(0);
			setRed->append(0);

			todayDateTime = QDateTime::fromString(dateTimeNow, "yyyy-MM-dd HH:mm:ss");
			int range = GetChartRange();
			chart->axisY()->setRange(0, range);
		}
	}
}
void MainApp::InsertRedAlert(int redAlertID, int cameraID, QString dateTimeNow)
{
	AddRowToRedReports(redAlertID, cameraID, dateTimeNow, dateTimeNow);
	//add to chart
	QChart *chart = ((QChartView*)ui.VLLayout->itemAt(0)->widget())->chart();
	QBarSeries *series = (QBarSeries *)chart->series().at(0);
	QBarSet *setRed = series->barSets().at(0);
	//Difference should be 0 in most cases, but it can be >0
	//todayDateTime = QDateTime::fromString("2017-11-20 21:40:00", "yyyy-MM-dd HH:mm:ss");
	int diff = (todayDateTime.date()).daysTo(QDateTime::fromString(dateTimeNow, "yyyy-MM-dd HH:mm:ss").date());
	if (diff == 0)
	{
		int value = setRed->at(setRed->count() - 1);
		value++;
		weekChartRedMap[0]++;
		setRed->replace(setRed->count() - 1, value);
		int range = GetChartRange();
		chart->axisY()->setRange(0, range);
	}
	else
	{
		//Data for bar series: second has people counter on <today - diff> position
		for (int i = 6; i > 0; i--)
		{
			weekChartGreenMap[i] = weekChartGreenMap[i - 1];
			weekChartRedMap[i] = weekChartRedMap[i - 1];
		}

		//Move week names by 1
		weekChartRedMap[0] = 1;

		QString category0 = ((QBarCategoryAxis *)(chart->axisX()))->at(0);
		((QBarCategoryAxis *)(chart->axisX()))->remove(category0);
		((QBarCategoryAxis *)(chart->axisX()))->append(category0);
		chart->axisX()->setRange(((QBarCategoryAxis *)(chart->axisX()))->at(0), ((QBarCategoryAxis *)(chart->axisX()))->at(6));

		QBarSet *setGreen = series->barSets().at(1);
		setGreen->remove(0);
		setGreen->append(0);

		//move red
		weekChartGreenMap[0] = 0;

		setRed->remove(0);
		setRed->append(1);

		todayDateTime = QDateTime::fromString(dateTimeNow, "yyyy-MM-dd HH:mm:ss");
		int range = GetChartRange();
		chart->axisY()->setRange(0, range);
	}

	for (int i = 0; i < vectorCameraLayoutsPages->size(); i++)
	{
		for (int j = 0; j < vectorCameraLayoutsPages->at(i)->size(); j++)
		{
			if (getCameraIDFromLayout(vectorCameraLayoutsPages->at(i)->at(j)) == cameraID)
			{
				ui.TWCameraPages->setCurrentIndex(i);
				return;
			}
		}
	}
}
void MainApp::UpdateGreenAlert(int greenAlertID, QString stopDate)
{
	for (int i = 0; i < ui.TWGreenReport->rowCount(); i++)
	{
		if (greenAlertID == ui.TWGreenReport->item(i, 0)->text().toInt())
		{
			ui.TWGreenReport->item(i, 6)->setText(stopDate);
			break;
		}
	}
}
void MainApp::UpdateRedAlert(int redAlertID, QString stopDate)
{
	for (int i = 0; i < ui.TWRedReport->rowCount(); i++)
	{
		if (redAlertID == ui.TWRedReport->item(i, 0)->text().toInt())
		{
			ui.TWRedReport->item(i, 3)->setText(stopDate);
			break;
		}
	}
}
int MainApp::GetChartRange()
{
	int range = 0;
	//Get redRange
	for (std::map<int, int>::iterator it = weekChartRedMap.begin(); it != weekChartRedMap.end(); ++it)
	{
		range = max(range, it->second);
	}
	//Get greenRange
	for (std::map<int, int>::iterator it = weekChartGreenMap.begin(); it != weekChartGreenMap.end(); ++it)
	{
		range = max(range, it->second);
	}

	float rangeRes = 0;
	rangeRes = (float)range / 4;
	range = ceil(rangeRes) * 4;
	return max(range, 4);
}
void MainApp::StatisticsChart()
{
	//https://doc.qt.io/qt-5/qtcharts-lineandbar-example.html

	QBarSet *setGreen = new QBarSet("Recognized");
	QBarSet *setRed = new QBarSet("Unrecognized");
	setRed->setBrush(QColor(255, 53, 53));//border

	todayDateTime = QDateTime::fromString(Utilities::GetCurrentDateTime(), "yyyy-MM-dd HH:mm:ss");
	QDateTime readDateTime;
	int diff;
	for (int i = 0; i <= 6; i++)
	{
		weekChartGreenMap.insert(std::pair<int, int>(i, 0));
		weekChartRedMap.insert(std::pair<int, int>(i, 0));
	}
	//Get data from green alert
	for (int i = 0; i < ui.TWGreenReport->rowCount(); i++)
	{
		//Get startDate
		readDateTime = QDateTime::fromString(ui.TWGreenReport->item(i, 5)->text(), "yyyy-MM-dd HH:mm:ss");
		diff = (readDateTime.date()).daysTo(todayDateTime.date());
		if (diff >= 0 && diff <= 6)
		{
			weekChartGreenMap.at(diff)++;
		}
	}

	//Get data from red alert
	for (int i = 0; i < ui.TWRedReport->rowCount(); i++)
	{
		readDateTime = QDateTime::fromString(ui.TWRedReport->item(i, 2)->text(), "yyyy-MM-dd HH:mm:ss");
		diff = (readDateTime.date()).daysTo(todayDateTime.date());
		if (diff >= 0 && diff <= 6)
		{
			weekChartRedMap.at(diff)++;
		}
	}

	//Data for bar series: second has people counter on <today - diff> position
	for (std::map<int, int>::reverse_iterator it = weekChartGreenMap.rbegin(); it != weekChartGreenMap.rend(); ++it)
	{
		*setGreen << it->second;
	}
	for (std::map<int, int>::reverse_iterator it = weekChartRedMap.rbegin(); it != weekChartRedMap.rend(); ++it)
	{
		*setRed << it->second;
	}

	//Create bar series
	QBarSeries *barseries = new QBarSeries();
	//Append sets to it
	barseries->append(setRed);
	barseries->append(setGreen);
	//Create chart
	QChart *chart = new QChart();
	chart->addSeries(barseries);
	//Days from today to 6 days ago
	QStringList categories;
	QLocale locale(QLocale::English);
	QString weekDayName;
	QDate calculateDate;

	for (int i = 6; i >= 0; i--)
	{
		calculateDate = todayDateTime.date().addDays(-i);
		weekDayName = locale.toString(calculateDate, "dddd");
		categories << weekDayName;
	}

	QBarCategoryAxis *axisX = new QBarCategoryAxis();
	axisX->append(categories);
	chart->setAxisX(axisX, barseries);
	axisX->setRange(categories.at(0), categories.at(categories.size() - 1));

	QValueAxis *axisY = new QValueAxis();
	chart->setAxisY(axisY, barseries);

	int range = GetChartRange();

	axisY->setRange(0, range);

	//Show Legend
	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);

	//Add chart onto a view
	QChartView *chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	ui.VLLayout->addWidget(chartView);
}
void MainApp::ChangeLogin()
{
	if (ui.LEChangeLoginUsername->text() != "" && ui.LEChangeLoginPassword->text() != "")
	{
		QSqlQuery query;
		query.prepare("SELECT Username, Password FROM Users WHERE UserID = ?");
		query.bindValue(0, loggedID);
		if (query.exec())
		{
			query.next();

			std::string concatHelp = ui.LEChangeLoginPassword->text().toStdString() + query.value(0).toString().toStdString();
			QString passwordHash = QString::fromStdString(Utilities::Sha256HEX(concatHelp));

			if (query.value(1).toString() == passwordHash)
			{
				query.clear();

				std::string newPassHash = Utilities::Sha256HEX(Utilities::Sha256HEX(ui.LEChangeLoginPassword->text().toStdString() + ui.LEChangeLoginUsername->text().toStdString()) + ui.LEChangeLoginUsername->text().toStdString());

				int camID = 0;
				std::string cameraPassword = "";
				query.prepare("SELECT CameraID, Password FROM Cameras WHERE UserID = ?");
				query.bindValue(0, loggedID);
				if (query.exec())
				{
					QSqlQuery queryUpdate;
					std::string encMsg;
					queryUpdate.exec("BEGIN IMMEDIATE TRANSACTION");
					while (query.next())
					{
						queryUpdate.clear();
						camID = query.value(0).toInt();
						encMsg = query.value(1).toString().toStdString();
						//Decrypt camera password
						cameraPassword = Utilities::GetDecrypted(passHash, encMsg);
						//Encrypt new camera password
						cameraPassword = Utilities::GetEncrypted(newPassHash, cameraPassword);
						//Update password
						queryUpdate.prepare("UPDATE Cameras SET Password = ?  WHERE UserID = ?");
						queryUpdate.bindValue(0, QString::fromStdString(cameraPassword));
						queryUpdate.bindValue(1, loggedID);
						queryUpdate.exec();
					}
					queryUpdate.exec("COMMIT");
					query.clear();
					//Update Password
					query.exec("BEGIN IMMEDIATE TRANSACTION");
					query.prepare("UPDATE Users SET Username = ?, Password = ?  WHERE UserID = ?");
					query.bindValue(0, ui.LEChangeLoginUsername->text());
					query.bindValue(1, QString::fromStdString(Utilities::Sha256HEX(ui.LEChangeLoginPassword->text().toStdString() + ui.LEChangeLoginUsername->text().toStdString())));
					query.bindValue(2, loggedID);
					bool result = query.exec();
					query.exec("COMMIT");
					if (result)
					{
						Utilities::MBAlarm("Your login has been changed succesfully. Please log in again", true);
						ui.PBLogout->click();
					}
					else
					{
						Utilities::MBAlarm("Typed login is occupied by antother profile. Please type another one", false);
					}
				}
				else
				{
					Utilities::MBAlarm("Something went wrong. Please try again", false);
				}
			}
			else
			{
				Utilities::MBAlarm("Typed password is incorrect. Please try again", false);
			}
		}
		else
		{
			Utilities::MBAlarm("Something went wrong. Please try again", false);
		}
	}
	else
	{
		Utilities::MBAlarm("At least one field is incomplete", false);
	}
}
void MainApp::ChangePassword()
{
	if (ui.LEChangePasswordOldPassword->text() != "" && ui.LEChangePasswordPassword->text() != "" && ui.LEChangePasswordConfPass->text() != "")
	{
		if (ui.LEChangePasswordPassword->text() == ui.LEChangePasswordConfPass->text())
		{
			/*Requirements:
			minimum 8 characters
			minimum 1 digit
			minimum 1 capital letter
			minimum lowercase*/
			std::regex passwordPattern("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])[a-zA-Z0-9]{8,}$");
			if (std::regex_match(ui.LEChangePasswordPassword->text().toStdString(), passwordPattern) == false)
			{
				Utilities::MBAlarm("Password incompatible format", false);
				return;
			}

			QSqlQuery query;
			query.prepare("SELECT Username, Password FROM Users WHERE UserID = ?");
			query.bindValue(0, loggedID);
			if (query.exec())
			{
				query.next();

				std::string login = query.value(0).toString().toStdString();
				std::string concatHelp = ui.LEChangePasswordOldPassword->text().toStdString() + login;
				QString passwordHash = QString::fromStdString(Utilities::Sha256HEX(concatHelp));

				if (query.value(1).toString() == passwordHash)
				{
					query.clear();

					std::string newPassHash = Utilities::Sha256HEX(Utilities::Sha256HEX(ui.LEChangePasswordPassword->text().toStdString() + login) + login);

					int camID = 0;
					std::string cameraPassword = "";
					query.prepare("SELECT CameraID, Password FROM Cameras WHERE UserID = ?");
					query.bindValue(0, loggedID);
					if (query.exec())
					{
						QSqlQuery queryUpdate;
						std::string encMsg;
						queryUpdate.exec("BEGIN IMMEDIATE TRANSACTION");
						while (query.next())
						{
							queryUpdate.clear();
							camID = query.value(0).toInt();
							encMsg = query.value(1).toString().toStdString();
							//Decrypt camera password
							cameraPassword = Utilities::GetDecrypted(passHash, encMsg);
							//Encrypt new camera password
							cameraPassword = Utilities::GetEncrypted(newPassHash, cameraPassword);
							//Update password
							queryUpdate.prepare("UPDATE Cameras SET Password = ?  WHERE UserID = ?");
							queryUpdate.bindValue(0, QString::fromStdString(cameraPassword));
							queryUpdate.bindValue(1, loggedID);
							queryUpdate.exec();
						}
						queryUpdate.exec("COMMIT");

						query.clear();
						query.exec("BEGIN IMMEDIATE TRANSACTION");
						query.prepare("UPDATE Users SET Password = ? WHERE UserID = ?");

						std::string concatHelp = ui.LEChangePasswordPassword->text().toStdString() + login;
						QString passwordHash = QString::fromStdString(Utilities::Sha256HEX(concatHelp));
						query.bindValue(0, passwordHash);
						query.bindValue(1, loggedID);
						bool result = query.exec();
						query.exec("COMMIT");
						if (result)
						{
							Utilities::MBAlarm("Your password has been changed succesfully. Please log in again", true);
							ui.PBLogout->click();
						}
						else
						{
							Utilities::MBAlarm("Something went wrong. Please try again", false);
						}
					}
					else
					{
						Utilities::MBAlarm("Something went wrong. Please try again", false);
					}
				}
				else
				{
					Utilities::MBAlarm("Typed password is incorrect. Please try again", false);
				}
			}
			else
			{
				Utilities::MBAlarm("Something went wrong. Please try again", false);
			}
		}
		else
		{
			Utilities::MBAlarm("New passwords are not the same. Please try again", false);
		}
	}
	else
	{
		Utilities::MBAlarm("At least one field is incomplete", false);
	}
}
void MainApp::DeleteProfile()
{
	if (ui.LEDeleteLoginUsername->text() != "" && ui.LEDeleteProfilePassword->text() != "")
	{
		QSqlQuery query;
		query.prepare("SELECT Password FROM Users WHERE UserID = ?");
		query.bindValue(0, loggedID);
		if (query.exec())
		{
			query.next();

			std::string concatHelp = ui.LEDeleteProfilePassword->text().toStdString() + ui.LEDeleteLoginUsername->text().toStdString();
			QString passwordHash = QString::fromStdString(Utilities::Sha256HEX(concatHelp));

			if (query.value(0).toString() == passwordHash)
			{
				query.clear();
				query.exec("BEGIN IMMEDIATE TRANSACTION");
				query.prepare("DELETE FROM Users WHERE UserID = ?");
				query.bindValue(0, loggedID);
				bool result = query.exec();
				query.exec("COMMIT");
				if (result == true)
				{
					for (int j = vectorCameraLayoutsPages->size() - 1; j >= 0; j--)
					{
						for (int i = vectorCameraLayoutsPages->at(j)->size() - 1; i >= 0; i--)
						{
							RemoveCamera(vectorCameraLayoutsPages->at(j)->at(i));
						}
					}

					Utilities::MBAlarm("Your profile has been deleted succesfully.", true);
					ui.PBLogout->click();
				}
				else
				{
					Utilities::MBAlarm("Something went wrong. Please try again", false);
				}
			}
			else
			{
				Utilities::MBAlarm("Typed password is incorrect. Please try again", false);
			}
		}
		else
		{
			Utilities::MBAlarm("Something went wrong. Please try again", false);
		}
	}
	else
	{
		Utilities::MBAlarm("At least one field is incomplete", false);
	}
}
void MainApp::ChangeSecurityQuestion()
{
	if (ui.LEChangeSecQuestionPassword->text() != "" && ui.LEChangeSecQuestionSecQuest->text() != "" && ui.LEChangeSecQuestionNewAnswer->text() != "")
	{
		QSqlQuery query;
		query.prepare("SELECT Username, Password FROM Users WHERE UserID = ?");
		query.bindValue(0, loggedID);
		if (query.exec())
		{
			query.next();

			std::string concatHelp = ui.LEChangeSecQuestionPassword->text().toStdString() + query.value(0).toString().toStdString();
			QString passwordHash = QString::fromStdString(Utilities::Sha256HEX(concatHelp));

			if (query.value(1).toString() == passwordHash)
			{
				query.clear();
				query.exec("BEGIN IMMEDIATE TRANSACTION");
				query.prepare("UPDATE Users SET SecurityQuestion = ?, Answer = ? WHERE UserID = ?");
				query.bindValue(0, ui.LEChangeSecQuestionSecQuest->text());

				std::string concatHelp = ui.LEChangeSecQuestionSecQuest->text().toStdString() + ui.LEChangeSecQuestionNewAnswer->text().toStdString();
				QString answerHash = QString::fromStdString(Utilities::Sha256HEX(concatHelp));
				query.bindValue(1, answerHash);
				query.bindValue(2, loggedID);
				bool result = query.exec();
				query.exec("COMMIT");
				if (result)
				{
					Utilities::MBAlarm("Your security question has been changed succesfully. Please log in again", true);
					ui.PBLogout->click();
				}
				else
				{
					Utilities::MBAlarm("Something went wrong. Please try again", false);
				}
			}
			else
			{
				Utilities::MBAlarm("Typed password is incorrect. Please try again", false);
			}
		}
		else
		{
			Utilities::MBAlarm("Something went wrong. Please try again", false);
		}
	}
	else
	{
		Utilities::MBAlarm("At least one field is incomplete", false);
	}
}