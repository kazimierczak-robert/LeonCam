#include "MainApp.h"

MainApp::MainApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	vectorIsEnabledButtonToRowIndex = new std::vector<QPushButton*>();
	vectorPatrolButtonToRowIndex = new std::vector<QPushButton*>();
	vectorRecognationButtonToRowIndex = new std::vector<QPushButton*>();
	vectorEditButtonToRowIndex = new std::vector<QPushButton*>();
	vectorRemoveButtonToRowIndex = new std::vector<QPushButton*>();
	
	connect(ui.PBAddCamera, SIGNAL(clicked()), this, SLOT(AddCamera()));
	//connect(this, SIGNAL(closed()), this, SLOT(LogOut()));
	connect(ui.TLWCameras, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(RowSelected(const QModelIndex&)));
	connect(ui.LESearch, SIGNAL(textChanged(const QString&)), this, SLOT(LESearchChanged()));

	ui.TLWCameras->setColumnWidth(0, 40);
	ui.TLWCameras->setColumnWidth(1, 77);
	ui.TLWCameras->setColumnWidth(2, 170);
	ui.TLWCameras->setColumnWidth(3, 140);
	ui.TLWCameras->setColumnWidth(4, 95);
	ui.TLWCameras->setColumnWidth(5, 40);
	ui.TLWCameras->setColumnWidth(6, 40);
	ui.TLWCameras->setColumnWidth(7, 40);
	ui.TLWCameras->setColumnWidth(8, 40);

	ui.TLWCameras->setFocusPolicy(Qt::NoFocus);
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
		
		//TODO
		int newIndex = ui.TLWCameras->rowCount();
		ui.TLWCameras->insertRow(newIndex);

		QPushButton* btn = new QPushButton();
		btn->setText("Off");
		btn->setGeometry(0, 0, 45, 45);
		btn->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
		connect(btn, &QPushButton::clicked, this, [this, btn] {TurnOnOffCamera(btn); });
		vectorIsEnabledButtonToRowIndex->push_back(btn);
		ui.TLWCameras->setIndexWidget(ui.TLWCameras->model()->index(newIndex, 0), btn);

		QImage *img = new QImage(":/Resources/Images/unavailablePreview.png");
		QTableWidgetItem *thumbnail = new QTableWidgetItem;
		thumbnail->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
		ui.TLWCameras->setItem(newIndex, 1, thumbnail);

		ui.TLWCameras->setItem(newIndex, 2, new QTableWidgetItem("Garage " + QVariant(newIndex).toString()));
		ui.TLWCameras->setItem(newIndex, 3, new QTableWidgetItem("Media-Tech"));
		ui.TLWCameras->setItem(newIndex, 4, new QTableWidgetItem("192.168.147.227"));

		btn = new QPushButton();
		btn->setGeometry(0, 0, 40, 40);
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/patrol.png); border: none; margin: 0px; padding: 0px;} QPushButton:hover{background-image: url(:/Resources/Images/patrolHover.png);}");
		connect(btn, &QPushButton::clicked, this, [this, btn] {PatrolCamera(btn); });
		vectorPatrolButtonToRowIndex->push_back(btn);
		ui.TLWCameras->setIndexWidget(ui.TLWCameras->model()->index(newIndex, 5), btn);

		btn = new QPushButton();
		btn->setGeometry(0, 0, 45, 45);
		btn->setText("On");
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}");
		connect(btn, &QPushButton::clicked, this, [this, btn] {RecognationCamera(btn); });
		vectorRecognationButtonToRowIndex->push_back(btn);
		ui.TLWCameras->setIndexWidget(ui.TLWCameras->model()->index(newIndex, 6), btn);

		btn = new QPushButton();
		btn->setGeometry(0, 0, 45, 45);
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/edit.png);border: none; margin: 0px; padding: 0px;}");
		connect(btn, &QPushButton::clicked, this, [this, btn] {EditCamera(btn); });
		vectorEditButtonToRowIndex->push_back(btn);
		ui.TLWCameras->setIndexWidget(ui.TLWCameras->model()->index(newIndex, 7), btn);

		btn = new QPushButton();
		btn->setGeometry(0, 0, 45, 45);
		btn->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/remove.png); border: none; margin: 0px; padding: 0px;} QPushButton:hover{background-image: url(:/Resources/Images/removeHover.png);}");
		connect(btn, &QPushButton::clicked, this, [this, btn] { RemoveCamera(btn); });
		vectorRemoveButtonToRowIndex->push_back(btn);

		ui.TLWCameras->setIndexWidget(ui.TLWCameras->model()->index(newIndex, 8), btn);

		for (int i = 1; i < 5; i++)
		{
			ui.TLWCameras->item(newIndex, i)->setFlags(Qt::ItemFlag::ItemIsEnabled);
		}

		ui.LTotalNumber->setText("Total number of cameras: " + QVariant(newIndex + 1).toString());
	}
}

void MainApp::LogOut()
{
	LogIn *login = new LogIn(nullptr);
	login->show();
	this->close();
}

void MainApp::RowSelected(const QModelIndex& modelIndex)
{
	QString cameraDetails = ui.TLWCameras->item(modelIndex.row(), 2)->text() + " | " + ui.TLWCameras->item(modelIndex.row(), 3)->text();
	CameraPreview *cameraPreview = new CameraPreview(this, cameraDetails, vectorIsEnabledButtonToRowIndex->at(modelIndex.row()), vectorRecognationButtonToRowIndex->at(modelIndex.row()), ui.LEnabledNumber);
	cameraPreview->exec();
}

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
				int number = ui.LEnabledNumber->text().split(" ").last().toInt();
				ui.LEnabledNumber->setText("Number of enabled cameras: " + QVariant(number - 1).toString());
			}

			ui.TLWCameras->removeRow(index);
			vectorIsEnabledButtonToRowIndex->erase(vectorIsEnabledButtonToRowIndex->begin() + index);
			vectorRemoveButtonToRowIndex->erase(vectorRemoveButtonToRowIndex->begin() + index);

			ui.LTotalNumber->setText("Total number of cameras: " + QVariant(ui.TLWCameras->rowCount()).toString());
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
	for (int i = 0; i < ui.TLWCameras->rowCount(); i++)
	{
		if (ui.TLWCameras->item(i, 2)->text().startsWith(ui.LESearch->text(), Qt::CaseInsensitive))
		{
			ui.TLWCameras->showRow(i);
		}
		else
		{
			ui.TLWCameras->hideRow(i);
		}
	}
}