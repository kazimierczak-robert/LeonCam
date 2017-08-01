#include "MainApp.h"

MainApp::MainApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	vectorCameraLayoutsPages = new std::vector<std::vector<QLayout*>*>();
	vectorQGridLayouts = new std::vector<QGridLayout*>();

	vectorIsEnabledButtonToRowIndex = new std::vector<QPushButton*>();
	vectorPatrolButtonToRowIndex = new std::vector<QPushButton*>();
	vectorRecognationButtonToRowIndex = new std::vector<QPushButton*>();
	vectorEditButtonToRowIndex = new std::vector<QPushButton*>();
	vectorRemoveButtonToRowIndex = new std::vector<QPushButton*>();

	connect(ui.PBAddCamera, SIGNAL(clicked()), this, SLOT(AddCamera()));
	//connect(this, SIGNAL(closed()), this, SLOT(LogOut()));
	connect(ui.LESearch, SIGNAL(textChanged(const QString&)), this, SLOT(LESearchChanged()));
	connect(ui.TWCameraPages, SIGNAL(currentChanged(int)), this, SLOT(TWCameraPagesChanged(int)));

	activeCameraPage = 0;

	addTab();

}

MainApp::~MainApp()
{
}

void MainApp::AddCamera()
{
	if (vectorCameraLayoutsPages->size() == 20)
	{
		if (vectorCameraLayoutsPages->at(19)->size()==6)
		{
			QMessageBox msgBox;
			msgBox.setText("Error: You can't assign more cameras to your profile");
			msgBox.exec();
			return;
		}
	}
	UserCamera *UserCam = new UserCamera(this);
	bool result = UserCam->exec();
	if (result == QDialog::Accepted)
	{
		//vector includes values from QDialog
		std::vector<QString>* controlsValues = UserCam->GetValuesFromControls();

		QGridLayout *layout = new QGridLayout();

		QLabel *label = new QLabel();
		label->setStyleSheet("background-image: url(:/Resources/Images/unavailablePreview.png);");
		label->setFixedSize(216, 123);
		layout->addWidget(label, 0, 0, 1, 5);

		QLabel *label2 = new QLabel("Garage (192.168.111.111)");
		label2->setStyleSheet("color:rgb(255, 255, 255);");
		label2->setFixedSize(216, 23);
		layout->addWidget(label2, 1, 0, 1, 5);

		QPushButton* btn = new QPushButton();
		btn->setText("Off");
		btn->setFixedSize(40, 40);
		btn->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
		connect(btn, &QPushButton::clicked, this, [this, btn] {TurnOnOffCamera(btn); });
		vectorIsEnabledButtonToRowIndex->push_back(btn);
		layout->addWidget(btn, 2, 0);

		btn = new QPushButton();
		btn->setFixedSize(40, 40);
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/patrol.png); border: none; margin: 0px; padding: 0px;} QPushButton:hover{background-image: url(:/Resources/Images/patrolHover.png);}");
		btn->setToolTip("Turn on camera patrol");
		connect(btn, &QPushButton::clicked, this, [this, btn] {PatrolCamera(btn); });
		vectorPatrolButtonToRowIndex->push_back(btn);
		layout->addWidget(btn, 2, 1);

		btn = new QPushButton();
		btn->setFixedSize(40, 40);
		btn->setText("On");
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}");
		btn->setToolTip("Recognation mode: On");
		connect(btn, &QPushButton::clicked, this, [this, btn] {RecognationCamera(btn); });
		vectorRecognationButtonToRowIndex->push_back(btn);
		layout->addWidget(btn, 2, 2);

		btn = new QPushButton();
		btn->setFixedSize(40, 40);
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/edit.png);border: none; margin: 0px; padding: 0px;} QPushButton:hover{background-image: url(:/Resources/Images/editHover.png);}");
		btn->setToolTip("Edit camera");
		connect(btn, &QPushButton::clicked, this, [this, btn] {EditCamera(btn); });
		vectorEditButtonToRowIndex->push_back(btn);
		layout->addWidget(btn, 2, 3);

		btn = new QPushButton();
		btn->setFixedSize(40, 40);
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/remove.png); border: none; margin: 0px; padding: 0px;} QPushButton:hover{background-image: url(:/Resources/Images/removeHover.png);}");
		btn->setToolTip("Remove camera");
		connect(btn, &QPushButton::clicked, this, [this, btn] { RemoveCamera(btn); });
		vectorRemoveButtonToRowIndex->push_back(btn);
		layout->addWidget(btn, 2, 4);

		layout->setHorizontalSpacing(4);
		layout->setVerticalSpacing(2);

		//layout->itemAtPosition(2,0)->widget()->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}");


		if (vectorCameraLayoutsPages->at(vectorCameraLayoutsPages->size()-1)->size() == 6)
		{
			addTab();
		}

		vectorQGridLayouts->at(vectorQGridLayouts->size()-1)->addLayout(layout, vectorCameraLayoutsPages->at(vectorCameraLayoutsPages->size() - 1)->size() / 3, vectorCameraLayoutsPages->at(vectorCameraLayoutsPages->size() - 1)->size() % 3);
		vectorCameraLayoutsPages->at(vectorCameraLayoutsPages->size() - 1)->push_back(layout);

		ui.LTotalNumber->setText("Total number of cameras: " + QString::number((vectorQGridLayouts->size()-1) * 6 + vectorCameraLayoutsPages->at(vectorCameraLayoutsPages->size() - 1) ->size()));
	}
}

void MainApp::addTab()
{
	QGridLayout *newLayout = new QGridLayout();
	QWidget *newTab = new QWidget(ui.TWCameraPages);
	newTab->setLayout(newLayout);
	ui.TWCameraPages->addTab(newTab, "");
	ui.TWCameraPages->setCurrentIndex(vectorQGridLayouts->size());
	TWCameraPagesChanged(vectorQGridLayouts->size());

	vectorCameraLayoutsPages->push_back(new std::vector<QLayout*>());
	vectorQGridLayouts->push_back(newLayout);

	ui.TWCameraPages->setStyleSheet("QTabWidget::pane {color: rgb(213, 235, 255);border: 0px;}QTabWidget::tab-bar {left: " + QString::number(360 - 18 * vectorQGridLayouts->size()) + "px;}QTabBar::tab {background-color: transparent;color: rgb(133, 196, 255);height: 18px;width: 36px;}QTabBar::tab:hover{color: rgb(160, 209, 255);}QTabBar::tab:selected{margin-top: -1px;color:rgb(219, 235, 255);}");

}

void MainApp::LogOut()
{
	LogIn *login = new LogIn(nullptr);
	login->show();
	this->close();
}

/*void MainApp::RowSelected(const QModelIndex& modelIndex)
{
	QString cameraDetails = ui.TLWCameras->item(modelIndex.row(), 2)->text() + " | " + ui.TLWCameras->item(modelIndex.row(), 3)->text();
	CameraPreview *cameraPreview = new CameraPreview(this, cameraDetails, vectorIsEnabledButtonToRowIndex->at(modelIndex.row()), vectorRecognationButtonToRowIndex->at(modelIndex.row()), ui.LEnabledNumber);
	cameraPreview->exec();
}*/

void MainApp::TurnOnOffCamera(QPushButton* button)
{
	int number = ui.LEnabledNumber->text().split(" ").last().toInt();

	if (button->text() == "Off")
	{
		button->setText("On");
		button->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
		number += 1;
	}
	else
	{
		button->setText("Off");
		button->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
		number -= 1;
	}

	ui.LEnabledNumber->setText("Number of enabled cameras: " + QVariant(number).toString());

}

void MainApp::PatrolCamera(QPushButton* button)
{
	int index = 0;

	for (const auto& item : *vectorPatrolButtonToRowIndex)
	{
		if (item == button)
		{
			if (vectorIsEnabledButtonToRowIndex->at(index)->text() == "On")
			{

			}
			return;
		}
		else
		{
			index += 1;
		}
	}
}
void MainApp::RecognationCamera(QPushButton* button)
{
	if (button->text() == "Off")
	{
		button->setText("On");
		button->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}");
	}
	else
	{
		button->setText("Off");
		button->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOff.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOffHover.png);}");
	}
}
void MainApp::EditCamera(QPushButton* button)
{
	int index = 0;

	for (const auto& item : *vectorEditButtonToRowIndex)
	{
		if (item == button)
		{
			if (vectorIsEnabledButtonToRowIndex->at(index)->text() == "On")
			{
				
			}	
			CameraEdition *cameraEdition = new CameraEdition(this);
			cameraEdition->exec();
			delete cameraEdition;
			return;
		}
		else
		{
			index += 1;
		}
	}
}

void MainApp::RemoveCamera(QPushButton* button)
{
	int index = 0;

	for (const auto& item : *vectorRemoveButtonToRowIndex)
	{
		if (item == button)
		{
			if (vectorIsEnabledButtonToRowIndex->at(index)->text() == "On")
			{
				//int number = ui.LEnabledNumber->text().split(" ").last().toInt();
				//ui.LEnabledNumber->setText("Number of enabled cameras: " + QVariant(number - 1).toString());
			}

			//ui.TLWCameras->removeRow(index);
			vectorIsEnabledButtonToRowIndex->erase(vectorIsEnabledButtonToRowIndex->begin() + index);
			vectorPatrolButtonToRowIndex->erase(vectorPatrolButtonToRowIndex->begin() + index);
			vectorRecognationButtonToRowIndex->erase(vectorRecognationButtonToRowIndex->begin() + index);
			vectorEditButtonToRowIndex->erase(vectorEditButtonToRowIndex->begin() + index);
			vectorRemoveButtonToRowIndex->erase(vectorRemoveButtonToRowIndex->begin() + index);

			//ui.LTotalNumber->setText("Total number of cameras: " + QVariant(ui.TLWCameras->rowCount()).toString());
			return;
		}
		else
		{
			index += 1;
		}
	}
}


void MainApp::LESearchChanged()
{
	/*for (int i = 0; i < ui.TLWCameras->rowCount(); i++)
	{
		if (ui.TLWCameras->item(i, 2)->text().startsWith(ui.LESearch->text(), Qt::CaseInsensitive))
		{
			ui.TLWCameras->showRow(i);
		}
		else
		{
			ui.TLWCameras->hideRow(i);
		}
	}*/
}

void MainApp::TWCameraPagesChanged(int newIndex)
{
	ui.TWCameraPages->setTabText(activeCameraPage, QString::fromStdWString(L"\u25CB"));
	ui.TWCameraPages->setTabText(newIndex, QString::fromStdWString(L"\u25CF"));
	activeCameraPage = newIndex;
}