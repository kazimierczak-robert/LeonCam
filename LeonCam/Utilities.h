#pragma once
#include <QMessageBox>
#include <qicon.h>
#include <qdesktopwidget.h>
#include "qdatetime.h"

#define iconPath ":/Resources/Images/logo.ico"
typedef unsigned char BYTE;// 8-bit byte

class Utilities
{
public:
	Utilities();
	~Utilities();
	static void MBAlarm(QString alarm, bool errorOrSuccess);
	static QString Utilities::GetCurrentDateTime();

	static bool SaveToBinFile(std::string fileName, BYTE *data);
	static BYTE *ReadFromBinFile(std::string fileName);
	static int BinFileElementsNo(std::string fileName);
	static bool MBQuestion(QString nameAndSurname);
};

