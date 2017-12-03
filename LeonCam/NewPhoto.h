#pragma once

#include <QDialog>
#include "ui_NewPhoto.h"
#include "Utilities.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp> 
#include "opencv2/contrib/contrib.hpp"
#include <QFuture> 
#include <QtConcurrent\qtconcurrentrun.h>
#include "qsqlquery.h"
#include "ONVIF\onvifclientptz.hpp"
#include "ONVIF\onvifclientmedia.hpp"
#include "ONVIF\onvifclientdevice.hpp"
#include "CameraControl.h"
#include "ImgProc.h"
#include "MainAppCamera.h"
#include <QCloseEvent>
#include "CVImageWidget.h"
#include <qfuture.h>
#include <QtConcurrent\qtconcurrentrun.h>
#include <qfuturewatcher.h>

class NewPhoto : public QDialog
{
	Q_OBJECT

public:
	//ID - photo is saved in the folder named .\\FaceBase\\<ID>
	NewPhoto(std::vector<int> cameraIDs,std::string passHash, QString name, QString surname, int loggedID, int FaceID, ImgProc *imgProc, map<int, MainAppCamera *> *cameraThread, QWidget *parent = Q_NULLPTR);
	~NewPhoto();
	public slots:
	void UpdateImage(const cv::Mat& image);
	private slots:
	void BackButtonClicked();
	void PBSnapshotClicked(int faceID);
private:
	int currentCameraID;
	int loggedID;
	Ui::NewPhoto ui;
	string profileToken;
	OnvifClientDevice *onvifDevice = nullptr;
	OnvifClientPTZ *ptz=nullptr;
	cv::Mat matImg;
	CameraControl *cameraControl = nullptr;
	ImgProc *imgProc = nullptr;
	map<int, MainAppCamera *> *cameraThread;
	// Create the image widget
	CVImageWidget* imageWidget = nullptr;
	void CurrentIndexChanged(std::string passHash);
	void NewPhoto::FillPtzAndProfileToken(std::string passHash);
	void GetCamerasInfo(int loggedID, std::vector<int> cameraIDs);
	void closeEvent(QCloseEvent *event);
};
