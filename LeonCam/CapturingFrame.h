#pragma once

#include <QThread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/contrib/contrib.hpp"
#include <qimage.h>
#include <qpixmap.h>

class CapturingFrame : public QThread
{
	Q_OBJECT

public:
	CapturingFrame(QObject *parent);
	~CapturingFrame();
	void SetStreamURI(std::string streamURI);
	void StopThread();
signals:
	void updatePixmap(const QPixmap& pixmap);
	void turnOnLabels();
private:
	std::string streamURI;
	bool isWorking;
	void run() override;
};
