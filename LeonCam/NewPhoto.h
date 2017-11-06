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


class NewPhoto : public QDialog
{
	Q_OBJECT

public:
	//ID - photo is saved in the folder named .\\FaceBase\\<ID>
	NewPhoto(std::vector<int> cameraIDs,std::string passHash, QString name, QString surname, int loggedID, int FaceID, ImgProc *imgProc, QWidget *parent = Q_NULLPTR);
	~NewPhoto();
	public slots:
	void UpdatePixmap(const QPixmap& pixmap);
	private slots:
	void BackButtonClicked();
	void PBSnapshotClicked(int faceID);
private:
	Ui::NewPhoto ui;
	QFuture<void> future; //"thread" field
	bool CameraPreviewUpdate(std::string streamUri);//Update video frames
	void GetCamerasInfo(int loggedID, std::vector<int> cameraIDs);
	struct Camera
	{
		int CameraID;
		std::string Name;
		std::string IPAddress;
		std::string Login;
		std::string Password;
	};
	std::map<int, struct Camera*> cameras;
	std::map<int, std::string> camerasToCB;
	string profileToken;
	OnvifClientPTZ *ptz=nullptr;
	CapturingFrame *capThread = nullptr;
	cv::Mat matImg;
	CameraControl *cameraControl = nullptr;
	ImgProc *imgProc = nullptr;
	void FillCBWithCamerasToCB();
	void CurrentIndexChanged(std::string passHash);
};
