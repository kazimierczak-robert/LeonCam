#include "CVImageWidget.h"

QSize CVImageWidget:: SizeHint() const
{ 
	return qImage.size(); 
}
QSize CVImageWidget::MinimumSizeHint()const
{ 
	return qImage.size(); 
}
void CVImageWidget::ShowImage(const cv::Mat& image) 
{
	// Convert the image to the RGB888 format
	switch (image.type()) 
	{
		case CV_8UC1:
			cvtColor(image, tmp, CV_GRAY2RGB);
			break;
		case CV_8UC3:
			cvtColor(image, tmp, CV_BGR2RGB);
			break;
	}

	// QImage needs the data to be stored continuously in memory
	assert(tmp.isContinuous());
	// Assign OpenCV's image buffer to the QImage. Note that the bytesPerLine parameter
	// (http://qt-project.org/doc/qt-4.8/qimage.html#QImage-6) is 3*width because each pixel
	// has three bytes.
	qImage = QImage(tmp.data, tmp.cols, tmp.rows, tmp.cols * 3, QImage::Format_RGB888);
	this->setFixedSize(image.cols, image.rows);
	repaint();
}
void CVImageWidget::paintEvent(QPaintEvent* /*event*/) 
{
	// Display the image
	QPainter painter(this);
	//Turn off antialiasing
	//painter.setRenderHint(QPainter::Antialiasing, false);
	painter.drawImage(QPoint(0, 0), qImage);
	painter.end();
}