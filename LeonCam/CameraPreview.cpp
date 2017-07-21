#include "CameraPreview.h"

CameraPreview::CameraPreview(QWidget *parent, QString cameraDetails, bool isEnabled)
	: QDialog(parent)
{
	ui.setupUi(this);
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