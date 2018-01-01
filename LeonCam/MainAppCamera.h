#pragma once

#include <QThread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/contrib/contrib.hpp"
#include <qimage.h>
#include <qpixmap.h>
#include "ImgProc.h"
#include "Utilities.h"
#include "qtimer.h"
#include <iterator>
#include <QCoreApplication>
#include <qpushbutton.h>
#include <QPainter>

#define thumbnailWidth 216
#define thumbnailHeight 123

class MainAppCamera : public QThread//, public QRunnable
{
	Q_OBJECT

public:
	MainAppCamera(ImgProc *imgProc,int cameraID, QObject *parent);
	~MainAppCamera();
	void SetStreamURI(std::string streamURI);
	void StopThread();
	void ChangeFaceRecoState(bool state);
	void SetCameraID(int cameraID) { this->cameraID = cameraID; }
	void SetFPS(int fps);
	void SetSendBigPicture(bool setting);
	void SetSendThumbnail(bool setting);
signals:
	void updateThumbnail(const QPixmap& pixmap, int cameraID);
	void updateImage(const cv::Mat& image);
private:
	struct GreenAlert
	{
		int faceID;
		int cameraID;
		QString startDate;
		QString stopDate;
		int greenAlertID;
	};
	struct RedAlert
	{
		QString startDate;
		QString stopDate;
		int redAlertID;
	};
	int cameraID = -1;
	ImgProc *imgProc = nullptr;
	std::string streamURI;
	bool isWorking;
	bool sendBigPicture;
	bool sendThumbnail;
	bool faceRecognitionState = false;
	bool isRedAlertStop = false;
	cv::VideoCapture vcap;
	cv::VideoWriter videowriter;
	cv::Mat img;
	std::list<GreenAlert> *greenAlertList = nullptr;
	RedAlert *redAlert = nullptr;
	int cameraFPS;
	int updateImagePeriod;
	int processImagePeriod;
	void UpdateDBAfterPrediction(int predictionLabel);
	void run() override;
	void StopRedAlert();
public slots:
	void UpdateGreenAlerts();
	void UpdateRedAlerts();
	void CheckGreenAlertInList(int greenAlertID);
	void CheckRedAlertID(int redAlertID);
	void Process();
	void SaveMat();
signals:
	void startWorking();
	void insertGreenAlert(int greenAlertID, int faceID, int cameraID, QString dateTimeNow);
	void insertRedAlert(int redAlertID, int cameraID, QString dateTimeNow);
	void updateGreenAlert(int greenAlertID, QString stopDate);
	void updateRedAlert(int redAlertID, QString stopDate);
};
