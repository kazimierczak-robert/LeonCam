#pragma once

#include <QDialog>
#include "ui_CameraPreview.h"
#include "onvifclientptz.hpp"
#include "onvifclientmedia.hpp"
#include "onvifclientdevice.hpp"
#include <QCloseEvent>
#include "CapturingFrame.h"
#include "qsqlquery.h"
#include "Utilities.h"

#define MAXCONNECTIONTRIES 5

class CameraPreview : public QDialog
{
	Q_OBJECT

public:
	CameraPreview(QWidget *parent = Q_NULLPTR, QString cameraDetails = "None", QPushButton *buttonIsEnabledFromParent=nullptr, QPushButton *buttonRecognationFromParent = nullptr, QLabel *numberOfEnabledCameras=nullptr, OnvifClientDevice* onvifDevice = nullptr, int camID = -1, std::string passHash = "");
	~CameraPreview();
signals:
	void openCameraEdit(int camID);
private slots:
	void BackButtonClicked();
	void TurnOnOffCamera();
	void TurnOnOffRecognizeMode();
	void MoveCamera(float panSpeed, float tiltSpeed);
	void StopCamera();
	void GoHomeCamera();
public slots:
	void UpdatePixmap(const QPixmap& pixmap);
	void CloseCameraEdit(const QString& cameraDetails);
private:
	Ui::CameraPreview ui;
	QPushButton *buttonIsEnabledFromParent;
	QPushButton *buttonRecognationFromParent;
	QLabel *numberOfEnabledCameras;
	OnvifClientPTZ *ptz;
	string profileToken;
	OnvifClientDevice *onvifDevice;
	CapturingFrame *capThread;
	int camID;
	std::string passHash;
	bool StartShowingPreview();
	void StopShowingPreview();
	void closeEvent(QCloseEvent *event);
};
