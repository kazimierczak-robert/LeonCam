#pragma once

#include <QObject>
#include "qmovie.h"
#include "qlabel.h"
#define loadingGifPath ":/Resources/loading4.gif"

class DesignBase : public QObject
{
	Q_OBJECT

public:
	DesignBase(QObject *parent);
	~DesignBase();
	QMovie *gif;
	QLabel *loadingLabel;
	void SetGifInLabel(QLabel *qlabel);
};
