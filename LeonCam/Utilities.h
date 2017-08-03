#pragma once
#include <QMessageBox>
#include <qicon.h>
#include <qdesktopwidget.h>
#include "SHA256.h"

#define iconPath ":/Resources/Images/logo.ico"

class Utilities
{
public:
	Utilities();
	~Utilities();
	static void MBAlarm(QString error, bool errorOrSuccess);
	static QString CreateHash(std::string message);
};

