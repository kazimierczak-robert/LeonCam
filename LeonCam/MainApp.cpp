#include "MainApp.h"

MainApp::MainApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

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

	QWidget* pWidget = new QWidget();
	QPushButton* btn_edit = new QPushButton();
	btn_edit->setText("Off");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
	
	connect(btn_edit, &QPushButton::clicked, this, [this, btn_edit] { TurnOnOffCamera(btn_edit); });

	QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
	pLayout->addWidget(btn_edit);
	pLayout->setAlignment(Qt::AlignCenter);
	pWidget->setLayout(pLayout);
	ui.TLWCameras->setCellWidget(newIndex, 0, pWidget);

	QImage *img = new QImage(":/Resources/Images/unavailablePreview.png");
	QTableWidgetItem *thumbnail = new QTableWidgetItem;
	thumbnail->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
	ui.TLWCameras->setItem(newIndex, 1, thumbnail);

	ui.TLWCameras->setItem(newIndex, 2, new QTableWidgetItem("Garage " + QVariant(newIndex).toString()));
	ui.TLWCameras->setItem(newIndex, 3, new QTableWidgetItem("Media-Tech"));

	pWidget = new QWidget();
	btn_edit = new QPushButton();
	btn_edit->setText("Patrol");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");
	pLayout = new QHBoxLayout(pWidget);
	pLayout->addWidget(btn_edit);
	pLayout->setAlignment(Qt::AlignCenter);
	pWidget->setLayout(pLayout);
	ui.TLWCameras->setCellWidget(newIndex, 4, pWidget);

	pWidget = new QWidget();
	btn_edit = new QPushButton();
	btn_edit->setText("Recognize");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");
	pLayout = new QHBoxLayout(pWidget);
	pLayout->addWidget(btn_edit);
	pLayout->setAlignment(Qt::AlignCenter);
	pWidget->setLayout(pLayout);
	ui.TLWCameras->setCellWidget(newIndex, 5, pWidget);

	pWidget = new QWidget();
	btn_edit = new QPushButton();
	btn_edit->setText("Edit");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");
	pLayout = new QHBoxLayout(pWidget);
	pLayout->addWidget(btn_edit);
	pLayout->setAlignment(Qt::AlignCenter);
	pWidget->setLayout(pLayout);
	ui.TLWCameras->setCellWidget(newIndex, 6, pWidget);

	pWidget = new QWidget();
	btn_edit = new QPushButton();
	btn_edit->setText("Remove");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");

	pLayout = new QHBoxLayout(pWidget);
	pLayout->addWidget(btn_edit);
	pLayout->setAlignment(Qt::AlignCenter);
	pWidget->setLayout(pLayout);
	ui.TLWCameras->setCellWidget(newIndex, 7, pWidget);

	for (int i = 0; i < 7; i++)
	{
		//ui.TLWCameras->item(0, i)->setFlags(Qt::ItemFlag::ItemIsEnabled);
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
	QString cameraDetails = ui.TLWCameras->item(modelIndex.row(), 2)->text() + " " + ui.TLWCameras->item(modelIndex.row(), 3)->text();
	CameraPreview *cameraPreview;
	
	if (/*ui.TLWCameras->takeItem(0, 0)->text() == "On"*/true)
	{
		cameraPreview = new CameraPreview(this, cameraDetails, true);
	}
	else
	{
		cameraPreview = new CameraPreview(this, cameraDetails, false);
	}
	//hide window
	//this->hide();
	cameraPreview->exec();
	//show window
	//this->show();
}

void MainApp::TurnOnOffCamera(QPushButton* button)
{
	if (button->text() == "Off")
	{
		button->setText("On");
		button->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
	}
	else
	{
		button->setText("Off");
		button->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
	}
}