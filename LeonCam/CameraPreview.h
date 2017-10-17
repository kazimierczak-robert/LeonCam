#pragma once

#include <QDialog>
#include "ui_CameraPreview.h"

#include "onvifclientptz.hpp"
#include "onvifclientmedia.hpp"
#include "onvifclientdevice.hpp"

class CameraPreview : public QDialog
{
	Q_OBJECT

public:
	CameraPreview(QWidget *parent = Q_NULLPTR, QString cameraDetails = "None", QPushButton *buttonIsEnabledFromParent=nullptr, QPushButton *buttonRecognationFromParent = nullptr, QLabel *numberOfEnabledCameras=nullptr, OnvifClientDevice* onvifDevice = nullptr, string profileToken="");
	~CameraPreview();
private slots:
	void BackButtonClicked();
	void TurnOnOffCamera();
	void TurnOnOffRecognizeMode();
	void MoveCamera(float panSpeed, float tiltSpeed);
	void StopCamera();
	void GoHomeCamera();
private:
	Ui::CameraPreview ui;
	QPushButton *buttonIsEnabledFromParent;
	QPushButton *buttonRecognationFromParent;
	QLabel *numberOfEnabledCameras;
	OnvifClientPTZ *ptz;
	string profileToken;
};
