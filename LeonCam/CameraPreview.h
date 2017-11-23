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
#include <CVImageWidget.h>

class CameraPreview : public QDialog
{
	Q_OBJECT

public:
	CameraPreview(QWidget *parent = Q_NULLPTR, QString cameraDetails = "None", QPushButton *buttonIsEnabledFromParent=nullptr, QPushButton *buttonRecognationFromParent = nullptr, QPushButton *buttonTakePhotoFromParent = nullptr, int cameraID = -1, MainAppCamera *thread = nullptr, std::string passHash = "");
	~CameraPreview();
signals:
	void openCameraEdit(int cameraID);
private slots:
	void TurnOnOffCamera();
	void TurnOnOffRecognizeMode();
public slots:
	void CloseCameraEdit(const QString& cameraDetails);
	void TurnOnLabels();
private:
	// Create the image widget
	CVImageWidget* imageWidget;

	Ui::CameraPreview ui;
	DesignBase *designB;
	QPushButton *buttonIsEnabledFromParent;
	QPushButton *buttonRecognationFromParent;
	QPushButton *buttonTakePhotoFromParent;
	OnvifClientDevice *device;
	OnvifClientPTZ *ptz;
	string profileToken;
	MainAppCamera *capThread;
	int cameraID;
	CameraControl *ctrl;
	std::string passHash;
	bool SetProfileTokenAndPTZ();
	void TurnOffLabels();
};
