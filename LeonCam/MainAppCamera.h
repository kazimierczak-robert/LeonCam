#pragma once

#include <QThread>
#include <QThread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/contrib/contrib.hpp"
#include <qimage.h>
#include <qpixmap.h>
#include "ImgProc.h"
#include "Utilities.h"

#define thumbnailWidth 216
#define thumbnailHeight 123
class MainAppCamera : public QThread
{
	Q_OBJECT

public:
	MainAppCamera(ImgProc *imgProc,int cameraID, QObject *parent);
	~MainAppCamera();
	void SetStreamURI(std::string streamURI);
	void StopThread();
	void ChangeFaceRecoState(bool state);
	void SetCameraID(int CameraID) { this->cameraID = CameraID; }
signals:
	void updateThumbnail(const QPixmap& pixmap, int cameraID);
private:
	int cameraID = -1;
	ImgProc *imgProc = nullptr;
	std::string streamURI;
	bool isWorking;
	bool faceRecognitionState = false;
	void run() override;
};
