#include "CameraPreview.h"

CameraPreview::CameraPreview(QWidget *parent, QString cameraDetails, bool isEnabled, QPushButton *cameraButtonFromParent, QLabel *numberOfEnabledCameras)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->cameraButtonFromParent = cameraButtonFromParent;
	this->numberOfEnabledCameras = numberOfEnabledCameras;

	connect(ui.PBCameraOnOff, SIGNAL(clicked()), this, SLOT(TurnOnOffCamera()));
	ui.LCameraDetails->setText(cameraDetails);
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
	if (isEnabled == true)
	{
		ui.PBCameraOnOff->setText("On");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
	}
	else
	{
		ui.PBCameraOnOff->setText("Off");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
	}
}

CameraPreview::~CameraPreview()
{
}

void CameraPreview::BackButtonClicked()
{
	this->close();
}

/*void CameraPreview::SetArrowPictureInButton(QPushButton* button, int rotationDegree)
{
	QPixmap pixmap(":/Resources/Images/up.png");
	QIcon ButtonIcon(pixmap.transformed(QTransform().rotate(rotationDegree)));
	button->setIcon(ButtonIcon);
	button->setIconSize(pixmap.rect().size());
}*/

void CameraPreview::TurnOnOffCamera()
{
	int number = numberOfEnabledCameras->text().split(" ").last().toInt();

	if (ui.PBCameraOnOff->text() == "Off")
	{
		ui.PBCameraOnOff->setText("On");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
		cameraButtonFromParent->setText("On");
		cameraButtonFromParent->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
		number += 1;
	}
	else
	{
		ui.PBCameraOnOff->setText("Off");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");

		cameraButtonFromParent->setText("Off");
		cameraButtonFromParent->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
		number -= 1;
	}

	numberOfEnabledCameras->setText("Number of enabled cameras: " + QVariant(number).toString());
}