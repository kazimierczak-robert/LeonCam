#pragma once
//http://develnoter.blogspot.com/2012/05/integrating-opencv-in-qt-gui.html

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <opencv2/opencv.hpp>

class CVImageWidget : public QWidget
{
	Q_OBJECT
private:
	QImage qImage;
	cv::Mat tmp;
public:
	explicit CVImageWidget(QWidget *parent = 0) : QWidget(parent){}
	~CVImageWidget() {}
	QSize SizeHint () const;
	QSize MinimumSizeHint() const;
public slots:
	void ShowImage(const cv::Mat& image);
protected:
	void paintEvent(QPaintEvent* /*event*/);
};
