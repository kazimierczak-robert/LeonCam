#pragma once

#include <QDialog>
#include "ui_CameraPreview.h"

class CameraPreview : public QDialog
{
	Q_OBJECT

public:
	CameraPreview(QWidget *parent = Q_NULLPTR, QString cameraDetails = "None", QPushButton *buttonIsEnabledFromParent=nullptr, QPushButton *buttonRecognationFromParent = nullptr, QLabel *numberOfEnabledCameras=nullptr);
	~CameraPreview();
private slots:
	void BackButtonClicked();
	void TurnOnOffCamera();
	void TurnOnOffRecognizeMode();
private:
	Ui::CameraPreview ui;
	//void SetArrowPictureInButton(QPushButton* button, int rotationDegree);
	QPushButton *buttonIsEnabledFromParent;
	QPushButton *buttonRecognationFromParent;
	QLabel *numberOfEnabledCameras;
};
