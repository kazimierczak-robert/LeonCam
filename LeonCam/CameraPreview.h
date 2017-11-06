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
#include "CameraControl.h"
#include "DesignBase.h"
#include <qfuture.h>
#include <QtConcurrent\qtconcurrentrun.h>

class CameraPreview : public QDialog
{
	Q_OBJECT

public:
	CameraPreview(QWidget *parent = Q_NULLPTR, QString cameraDetails = "None", QPushButton *buttonIsEnabledFromParent=nullptr, QPushButton *buttonRecognationFromParent = nullptr, OnvifClientDevice* onvifDevice = nullptr, int camID = -1, std::string passHash = "");
	~CameraPreview();
signals:
	void openCameraEdit(int camID);
private slots:
	void BackButtonClicked();
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
	OnvifClientPTZ *ptz;
	string profileToken;
	OnvifClientDevice *onvifDevice;
	CapturingFrame *capThread;
	int camID;
	std::string passHash;
	CameraControl *ctrl;
	bool StartShowingPreview();
	void StopShowingPreview();
	void closeEvent(QCloseEvent *event);
};
