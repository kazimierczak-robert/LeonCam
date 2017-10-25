#include "CapturingFrame.h"

CapturingFrame::CapturingFrame(QObject *parent)
	: QThread(parent)
{
	this->isWorking = true;
}

CapturingFrame::~CapturingFrame()
{

}

void CapturingFrame::setStreamURI(std::string streamURI)
{
	this->streamURI = streamURI;
}

void CapturingFrame::run() 
{
	//QThread::currentThread()->setPriority(QThread::Priority::HighestPriority);
	cv::VideoCapture vcap;
	cv::Mat img;
	if (vcap.open(streamURI))
	{
		while (isWorking)
		{
			if (vcap.read(img))
			{
				cvtColor(img, img, CV_BGR2RGB);
				emit UpdatePixmap(QPixmap::fromImage(QImage(img.data, 760, 427, img.step, QImage::Format_RGB888)));
			}
		}
	}
}

void CapturingFrame::StopThread()
{
	this->isWorking = false;
}