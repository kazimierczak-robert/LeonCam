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
#include "onvifclientptz.hpp"
#include "onvifclientmedia.hpp"
#include "onvifclientdevice.hpp"
#include "CapturingFrame.h"
#include "CameraControl.h"
#include "ImgProc.h"
#include "MainAppCamera.h"


class NewPhoto : public QDialog
{
	Q_OBJECT

public:
	//ID - photo is saved in the folder named .\\FaceBase\\<ID>
	NewPhoto(std::vector<int> cameraIDs,std::string passHash, QString name, QString surname, int loggedID, int FaceID, ImgProc *imgProc, map<int, MainAppCamera *> *cameraThread, QWidget *parent = Q_NULLPTR);
	~NewPhoto();
	public slots:
	void UpdatePixmap(const QPixmap& pixmap);
	private slots:
	void BackButtonClicked();
	void PBSnapshotClicked(int faceID);
private:
	int currentCameraID;
	int loggedID;
	Ui::NewPhoto ui;
	string profileToken;
	OnvifClientPTZ *ptz=nullptr;
	cv::Mat matImg;
	CameraControl *cameraControl = nullptr;
	ImgProc *imgProc = nullptr;
	map<int, MainAppCamera *> *cameraThread;
	void CurrentIndexChanged(std::string passHash);
	bool CameraPreviewUpdate(std::string streamUri);//Update video frames
	void NewPhoto::FillPtzAndProfileToken(std::string passHash);
	void GetCamerasInfo(int loggedID, std::vector<int> cameraIDs);
};
