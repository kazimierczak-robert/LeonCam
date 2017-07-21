#include "CameraPreview.h"

CameraPreview::CameraPreview(QWidget *parent, QString cameraDetails)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.LCameraDetails->setText(cameraDetails);
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
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