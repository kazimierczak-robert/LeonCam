#pragma once

#include <QDialog>
#include "ui_CameraPreview.h"

class CameraPreview : public QDialog
{
	Q_OBJECT

public:
	CameraPreview(QWidget *parent = Q_NULLPTR, QString cameraDetails = "None", bool isEnabled = false, QPushButton *cameraButtonFromParent=nullptr, QLabel *numberOfEnabledCameras=nullptr);
	~CameraPreview();
private slots:
	void BackButtonClicked();
	void TurnOnOffCamera();
private:
	Ui::CameraPreview ui;
	//void SetArrowPictureInButton(QPushButton* button, int rotationDegree);
	QPushButton *cameraButtonFromParent;
	QLabel *numberOfEnabledCameras;
};
