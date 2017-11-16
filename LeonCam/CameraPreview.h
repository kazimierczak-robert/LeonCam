#pragma once

#include <QDialog>
#include "ui_CameraPreview.h"
#include "onvifclientptz.hpp"
#include "onvifclientmedia.hpp"
#include "onvifclientdevice.hpp"
#include <QCloseEvent>
#include "qsqlquery.h"
#include "Utilities.h"
#include "CameraControl.h"
#include "DesignBase.h"
#include <qfuture.h>
#include <QtConcurrent\qtconcurrentrun.h>
#include "MainAppCamera.h"

class CameraPreview : public QDialog
{
	Q_OBJECT

public:
	CameraPreview(QWidget *parent = Q_NULLPTR, QString cameraDetails = "None", QPushButton *buttonIsEnabledFromParent=nullptr, QPushButton *buttonRecognationFromParent = nullptr, QPushButton *buttonTakePhotoFromParent = nullptr, OnvifClientDevice* onvifDevice = nullptr, int camID = -1, MainAppCamera *thread = nullptr, std::string passHash = "");
	~CameraPreview();
signals:
	void openCameraEdit(int camID);
private slots:
	void TurnOnOffCamera();
	void TurnOnOffRecognizeMode();
public slots:
	void UpdatePixmap(const QPixmap& pixmap);
	void CloseCameraEdit(const QString& cameraDetails);
	void TurnOnLabels();
private:
	Ui::CameraPreview ui;
	DesignBase *designB;
	QPushButton *buttonIsEnabledFromParent;
	QPushButton *buttonRecognationFromParent;
	QPushButton *buttonTakePhotoFromParent;
	OnvifClientPTZ *ptz;
	string profileToken;
	MainAppCamera *capThread;
	int camID;
	CameraControl *ctrl;
	std::string passHash;
	bool SetProfileTokenAndPTZ(OnvifClientDevice *onvifDevice);
	void TurnOffLabels();
	void closeEvent(QCloseEvent *event);
};
