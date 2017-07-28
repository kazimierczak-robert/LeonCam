#include "MainApp.h"

MainApp::MainApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	vectorCameraLayouts = new std::vector<QLayout*>();

	vectorIsEnabledButtonToRowIndex = new std::vector<QPushButton*>();
	vectorPatrolButtonToRowIndex = new std::vector<QPushButton*>();
	vectorRecognationButtonToRowIndex = new std::vector<QPushButton*>();
	vectorEditButtonToRowIndex = new std::vector<QPushButton*>();
	vectorRemoveButtonToRowIndex = new std::vector<QPushButton*>();

	connect(ui.PBAddCamera, SIGNAL(clicked()), this, SLOT(AddCamera()));
	//connect(this, SIGNAL(closed()), this, SLOT(LogOut()));
	connect(ui.LESearch, SIGNAL(textChanged(const QString&)), this, SLOT(LESearchChanged()));

	QPushButton* btn = new QPushButton();
	btn->setFixedSize(20, 20);
	btn->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");

	ui.HLCameraPages->addWidget(btn, 2, 0);

}

MainApp::~MainApp()
{
}

void MainApp::AddCamera()
{
	UserCamera *UserCam = new UserCamera(this);
	bool result = UserCam->exec();
	if (result == QDialog::Accepted)
	{
		//vector includes values from QDialog
		std::vector<QString>* controlsValues = UserCam->GetValuesFromControls();

		QGridLayout *layout = new QGridLayout();
		ui.GLCameras->addLayout(layout, vectorCameraLayouts->size()/3, vectorCameraLayouts->size() % 3);
		vectorCameraLayouts->push_back(layout);

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
	}
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
	//int number = ui.LEnabledNumber->text().split(" ").last().toInt();

	if (button->text() == "Off")
	{
		button->setText("On");
		button->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
		//number += 1;
	}
	else
	{
		button->setText("Off");
		button->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
		//number -= 1;
	}

	//ui.LEnabledNumber->setText("Number of enabled cameras: " + QVariant(number).toString());

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