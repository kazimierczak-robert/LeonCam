#pragma once

#include <QDialog>
#include "ui_NewPhoto.h"
#include "Utilities.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include "opencv2/contrib/contrib.hpp"
#include <QFuture> 
#include <QtConcurrent\qtconcurrentrun.h>

class NewPhoto : public QDialog
{
	Q_OBJECT

public:
	//ID - photo is saved in the folder named .\\FaceBase\\<ID>
	NewPhoto(std::vector<int> cameraIDs,std::string passHash, QString name, QString surname, int ID, QWidget *parent = Q_NULLPTR);
	~NewPhoto();
private slots:
	void BackButtonClicked();
private:
	Ui::NewPhoto ui;
	QFuture<void> future; //"thread" field
	void NewPhoto::CameraPreviewUpdate(std::string streamUri);//Update video frames
};
