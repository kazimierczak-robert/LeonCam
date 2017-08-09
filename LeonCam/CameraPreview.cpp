#include "CameraPreview.h"

CameraPreview::CameraPreview(QWidget *parent, QString cameraDetails, QPushButton *buttonIsEnabledFromParent, QPushButton *buttonRecognationFromParent, QLabel *numberOfEnabledCameras)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->buttonIsEnabledFromParent = buttonIsEnabledFromParent;
	this->buttonRecognationFromParent = buttonRecognationFromParent;
	this->numberOfEnabledCameras = numberOfEnabledCameras;

	connect(ui.PBCameraOnOff, SIGNAL(clicked()), this, SLOT(TurnOnOffCamera()));
	connect(ui.PBRecognize, SIGNAL(clicked()), this, SLOT(TurnOnOffRecognizeMode()));
	ui.LCameraDetails->setText(cameraDetails);
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));

	if (buttonIsEnabledFromParent->text() == "On")
	{
		ui.PBCameraOnOff->setText("On");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
	}
	else
	{
		ui.PBCameraOnOff->setText("Off");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
	}

	if (buttonRecognationFromParent->text() == "On")
	{
		ui.PBRecognize->setText("On");
		ui.PBRecognize->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}");
	}
	else
	{
		ui.PBRecognize->setText("Off");
		ui.PBRecognize->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOff.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOffHover.png);}");
	}
}

CameraPreview::~CameraPreview()
{
}

void CameraPreview::BackButtonClicked()
{
	this->close();
}

void CameraPreview::TurnOnOffCamera()
{
	int number = numberOfEnabledCameras->text().split(" ").last().toInt();

	if (ui.PBCameraOnOff->text() == "Off")
	{
		ui.PBCameraOnOff->setText("On");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
		buttonIsEnabledFromParent->setText("On");
		buttonIsEnabledFromParent->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(36, 118, 59);}QPushButton:hover{background-color: rgb(39, 129, 63);}");
		number += 1;
	}
	else
	{
		ui.PBCameraOnOff->setText("Off");
		ui.PBCameraOnOff->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");

		buttonIsEnabledFromParent->setText("Off");
		buttonIsEnabledFromParent->setStyleSheet("QPushButton{color:rgb(255, 255, 255);background-color: rgb(255, 77, 61);}QPushButton:hover{background-color: rgb(255, 87, 58);}");
		number -= 1;
	}

	numberOfEnabledCameras->setText("Number of enabled cameras: " + QVariant(number).toString());
}

void CameraPreview::TurnOnOffRecognizeMode()
{
	if (buttonRecognationFromParent->text() == "Off")
	{
		buttonRecognationFromParent->setText("On");
		buttonRecognationFromParent->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}");
		ui.PBRecognize->setText("On");
		ui.PBRecognize->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOn.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOnHover.png);}");
	}
	else
	{
		buttonRecognationFromParent->setText("Off");
		buttonRecognationFromParent->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOff.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOffHover.png);}");
		ui.PBRecognize->setText("Off");
		ui.PBRecognize->setStyleSheet("QPushButton{background-image: url(:/Resources/Images/recognizeOff.png); border: none; margin: 0px; padding: 0px; color: transparent;} QPushButton:hover{background-image: url(:/Resources/Images/recognizeOffHover.png);}");
	}
}