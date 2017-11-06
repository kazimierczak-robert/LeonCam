#include "CapturingFrame.h"

CapturingFrame::CapturingFrame(QObject *parent)
	: QThread(parent)
{

}

CapturingFrame::~CapturingFrame()
{

}

void CapturingFrame::SetStreamURI(std::string streamURI)
{
	this->streamURI = streamURI;
}

void CapturingFrame::run() 
{
	this->isWorking = true;

	//QThread::currentThread()->setPriority(QThread::Priority::HighestPriority);
	cv::VideoCapture vcap;
	cv::Mat img;
	if (vcap.open(streamURI))
	{
		emit turnOnLabels();
		while (isWorking)
		{
			if (vcap.read(img))
			{
				cvtColor(img, img, CV_BGR2RGB);
				cv::resize(img, img, cv::Size(760, 427));
				emit updatePixmap(QPixmap::fromImage(QImage(img.data, 760, 427, img.step, QImage::Format_RGB888)));
			}
		}
		vcap.release();
		img.release();
	}
}

void CapturingFrame::StopThread()
{
	this->isWorking = false;
}