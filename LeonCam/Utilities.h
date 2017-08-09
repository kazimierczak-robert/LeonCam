#pragma once
#include <QMessageBox>
#include <qicon.h>
#include <qdesktopwidget.h>
#include "qdatetime.h"

#define iconPath ":/Resources/Images/logo.ico"

class Utilities
{
public:
	Utilities();
	~Utilities();
	static void MBAlarm(QString alarm, bool errorOrSuccess);
	static QString Utilities::GetCurrentDateTime();
};

