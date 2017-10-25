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
	void run() override;
	void setStreamURI(std::string streamURI);
	void StopThread();
signals:
	void UpdatePixmap(const QPixmap& pixmap);
private:
	std::string streamURI;
	bool isWorking;
};
