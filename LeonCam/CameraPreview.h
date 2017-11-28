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
#include "MainAppCamera.h"
#include <CVImageWidget.h>
#include "MainApp.h"

class CameraPreview : public QDialog
{
	Q_OBJECT

public:
	CameraPreview(QWidget *parent = Q_NULLPTR, QString cameraDetails = "None", QPushButton *buttonIsEnabledFromParent=nullptr, QPushButton *buttonRecognationFromParent = nullptr, QPushButton *buttonTakePhotoFromParent = nullptr, int cameraID = -1, /*MainAppCamera *thread = nullptr*/std::map<int, MainAppCamera *> *cameraThread = nullptr, std::string passHash = "");
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

	QWidget* parentMainApp;

	Ui::CameraPreview ui;
	QPushButton *buttonIsEnabledFromParent;
	QPushButton *buttonRecognationFromParent;
	QPushButton *buttonTakePhotoFromParent;
	OnvifClientDevice *device;
	OnvifClientPTZ *ptz;
	string profileToken;
	std::map<int, MainAppCamera *> *cameraThread;
	//MainAppCamera *capThread;
	int cameraID;
	CameraControl *ctrl;
	std::string passHash;
	bool SetProfileTokenAndPTZ();
	void TurnOffLabels();
};
