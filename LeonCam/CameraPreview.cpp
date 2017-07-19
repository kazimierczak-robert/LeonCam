#include "CameraPreview.h"

CameraPreview::CameraPreview(QWidget *parent, QString cameraDetails)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.cameraDetailsLabel->setText(cameraDetails);
	connect(ui.backButton, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
}

CameraPreview::~CameraPreview()
{
}

void CameraPreview::BackButtonClicked()
{
	this->close();
}
