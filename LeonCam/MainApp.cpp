#include "MainApp.h"

MainApp::MainApp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.newCameraButton, SIGNAL(clicked()), this, SLOT(AddNewCamera()));
	connect(ui.logOutButton, SIGNAL(clicked()), this, SLOT(LogOut()));
	connect(ui.camerasTable, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(RowSelected(const QModelIndex&)));

	ui.camerasTable->setColumnWidth(0, 16);
	ui.camerasTable->setColumnWidth(1, 100);
	ui.camerasTable->setColumnWidth(2, 200);
	ui.camerasTable->setColumnWidth(3, 164);
	ui.camerasTable->setColumnWidth(4, 50);
	ui.camerasTable->setColumnWidth(5, 50);
	ui.camerasTable->setColumnWidth(6, 50);
	ui.camerasTable->setColumnWidth(7, 50);
}

MainApp::~MainApp()
{
}


void MainApp::AddNewCamera()
{
	ui.camerasTable->insertRow(0);

	QImage *img = new QImage(":/Resources/Images/unavailable.png");
	QTableWidgetItem *thumbnail = new QTableWidgetItem;
	thumbnail->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
	ui.camerasTable->setItem(0, 0, thumbnail);

	img = new QImage(":/Resources/Images/unavailablePreview.png");
	thumbnail = new QTableWidgetItem;
	thumbnail->setData(Qt::DecorationRole, QPixmap::fromImage(*img));
	ui.camerasTable->setItem(0, 1, thumbnail);

	ui.camerasTable->setItem(0, 2, new QTableWidgetItem("Garage"));
	ui.camerasTable->setItem(0, 3, new QTableWidgetItem("Media-Tech"));

	QWidget* pWidget = new QWidget();
	QPushButton* btn_edit = new QPushButton();
	btn_edit->setText("Patrol");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");
	QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
	pLayout->addWidget(btn_edit);
	pLayout->setAlignment(Qt::AlignCenter);
	pWidget->setLayout(pLayout);
	ui.camerasTable->setCellWidget(0, 4, pWidget);

	pWidget = new QWidget();
	btn_edit = new QPushButton();
	btn_edit->setText("Recognize");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");
	pLayout = new QHBoxLayout(pWidget);
	pLayout->addWidget(btn_edit);
	pLayout->setAlignment(Qt::AlignCenter);
	pWidget->setLayout(pLayout);
	ui.camerasTable->setCellWidget(0, 5, pWidget);

	pWidget = new QWidget();
	btn_edit = new QPushButton();
	btn_edit->setText("Edit");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");
	pLayout = new QHBoxLayout(pWidget);
	pLayout->addWidget(btn_edit);
	pLayout->setAlignment(Qt::AlignCenter);
	pWidget->setLayout(pLayout);
	ui.camerasTable->setCellWidget(0, 6, pWidget);

	pWidget = new QWidget();
	btn_edit = new QPushButton();
	btn_edit->setText("Remove");
	btn_edit->setGeometry(0, 0, 45, 45);
	btn_edit->setStyleSheet("background-color: rgb(255, 77, 61);");
	pLayout = new QHBoxLayout(pWidget);
	pLayout->addWidget(btn_edit);
	pLayout->setAlignment(Qt::AlignCenter);
	pWidget->setLayout(pLayout);
	ui.camerasTable->setCellWidget(0, 7, pWidget);

	for (int i = 0; i < 7; i++)
	{
		//ui.camerasTable->item(0, i)->setFlags(Qt::ItemFlag::ItemIsEnabled);
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
	QString cameraDetails = ui.camerasTable->item(modelIndex.row(), 2)->text() + " " + ui.camerasTable->item(modelIndex.row(), 3)->text();
	CameraPreview *cameraPreview = new CameraPreview(this, cameraDetails);
	//hide window
	//this->hide();
	cameraPreview->exec();
	//show window
	//this->show();
}