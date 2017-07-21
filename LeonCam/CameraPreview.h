#pragma once

#include <QDialog>
#include "ui_CameraPreview.h"

class CameraPreview : public QDialog
{
	Q_OBJECT

public:
	CameraPreview(QWidget *parent = Q_NULLPTR, QString cameraDetails = "None");
	~CameraPreview();
private slots:
	void BackButtonClicked();
private:
	Ui::CameraPreview ui;
	//void SetArrowPictureInButton(QPushButton* button, int rotationDegree);
};
