#include "DesignBase.h"

DesignBase::DesignBase(QObject *parent)
	: QObject(parent)
{
	//set proper gif
	gif = new QMovie(loadingGifPath);
}
DesignBase::~DesignBase()
{
}
void DesignBase::SetGifInLabel(QLabel *qlabel)
{
	loadingLabel = qlabel;
	loadingLabel->setMovie(gif);
	gif->start();
	gif->stop();
}