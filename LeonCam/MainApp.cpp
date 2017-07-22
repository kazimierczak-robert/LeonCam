#include "MainApp.h"

MainApp::MainApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	vectorIsEnabledButtonToRowIndex = new std::vector<QPushButton*>();
	vectorRemoveButtonToRowIndex = new std::vector<QPushButton*>();

	connect(ui.PBNewCamera, SIGNAL(clicked()), this, SLOT(AddNewCamera()));
	//connect(this, SIGNAL(closed()), this, SLOT(LogOut()));
	connect(ui.TLWCameras, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(RowSelected(const QModelIndex&)));

	ui.TLWCameras->setColumnWidth(0, 50);
	ui.TLWCameras->setColumnWidth(1, 100);
	ui.TLWCameras->setColumnWidth(2, 180);
	ui.TLWCameras->setColumnWidth(3, 150);
	ui.TLWCameras->setColumnWidth(4, 50);
	ui.TLWCameras->setColumnWidth(5, 50);
	ui.TLWCameras->setColumnWidth(6, 50);
	ui.TLWCameras->setColumnWidth(7, 50);
}

MainApp::~MainApp()
{
}


void MainApp::AddNewCamera()
{
	int newIndex = ui.TLWCameras->rowCount();
	ui.TLWCameras->insertRow(newIndex);

	QPushButton* btn_edit = new QPushButton();
	btn_edit->setText("Off");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");

	connect(btn_edit, &QPushButton::clicked, this, [this, btn_edit] { TurnOnOffCamera(btn_edit); });
	vectorIsEnabledButtonToRowIndex->push_back(btn_edit);
	ui.TLWCameras->setIndexWidget(ui.TLWCameras->model()->index(newIndex, 0), btn_edit);

	QImage *img = new QImage(":/Resources/Images/unavailablePreview.png");
	QTableWidgetItem *thumbnail = new QTableWidgetItem;
	thumbnail->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
	ui.TLWCameras->setItem(newIndex, 1, thumbnail);

	ui.TLWCameras->setItem(newIndex, 2, new QTableWidgetItem("Garage " + QVariant(newIndex).toString()));
	ui.TLWCameras->setItem(newIndex, 3, new QTableWidgetItem("Media-Tech"));

	btn_edit = new QPushButton();
	btn_edit->setText("Patrol");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");
	ui.TLWCameras->setIndexWidget(ui.TLWCameras->model()->index(newIndex, 4), btn_edit);

	btn_edit = new QPushButton();
	btn_edit->setText("Recognize");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");
	ui.TLWCameras->setIndexWidget(ui.TLWCameras->model()->index(newIndex, 5), btn_edit);

	btn_edit = new QPushButton();
	btn_edit->setText("Edit");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");
	ui.TLWCameras->setIndexWidget(ui.TLWCameras->model()->index(newIndex, 6), btn_edit);

	btn_edit = new QPushButton();
	btn_edit->setText("Remove");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");

	connect(btn_edit, &QPushButton::clicked, this, [this, btn_edit] { RemoveCamera(btn_edit); });
	vectorRemoveButtonToRowIndex->push_back(btn_edit);

	ui.TLWCameras->setIndexWidget(ui.TLWCameras->model()->index(newIndex, 7), btn_edit);

	for (int i = 1; i < 4; i++)
	{
		ui.TLWCameras->item(newIndex, i)->setFlags(Qt::ItemFlag::ItemIsEnabled);
	}

	ui.LTotalNumber->setText("Total number of cameras: " + QVariant(newIndex+1).toString());
}

void MainApp::LogOut()
{
	LogIn *login = new LogIn(nullptr);
	login->show();
	this->close();
}

void MainApp::RowSelected(const QModelIndex& modelIndex)
{
	QString cameraDetails = ui.TLWCameras->item(modelIndex.row(), 2)->text() + " " + ui.TLWCameras->item(modelIndex.row(), 3)->text();
	CameraPreview *cameraPreview;
	
	if (vectorIsEnabledButtonToRowIndex->at(modelIndex.row())->text()=="On")
	{
		cameraPreview = new CameraPreview(this, cameraDetails, true, vectorIsEnabledButtonToRowIndex->at(modelIndex.row()), ui.LEnabledNumber);
	}
	else
	{
		cameraPreview = new CameraPreview(this, cameraDetails, false, vectorIsEnabledButtonToRowIndex->at(modelIndex.row()), ui.LEnabledNumber);
	}
	
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