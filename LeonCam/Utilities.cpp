#include "Utilities.h"



Utilities::Utilities()
{
}


Utilities::~Utilities()
{
}

void Utilities::MBAlarm(QString alarm, bool errorOrSuccess)
{
	QMessageBox msgBox;
	QPixmap pixmap(iconPath);
	QIcon ButtonIcon(pixmap);
	msgBox.setWindowIcon(ButtonIcon);
	msgBox.setStyleSheet("QPushButton{background-color: rgb(36, 118, 59);color: rgb(255, 255, 255); }QPushButton:hover{background-color: rgb(39, 129, 63);}");

	if (errorOrSuccess == true) 
	{
		msgBox.setText("<b>Success:</b> " + alarm);
	}
	else
	{
		msgBox.setText("<b>Error:</b> " + alarm);
	}
	msgBox.exec();
}
//https://stackoverflow.com/a/10599161
QString Utilities::CreateHash(std::string message)
{
	SHA256 *sha256 = new SHA256();
	BYTE *abbreviation = sha256->sha256_abbreviation(message);
	char abbreviationC[65];
	abbreviationC[64] = 0;
	for (size_t i = 0; i < 32; i++)
	{
		sprintf(&abbreviationC[2 * i], "%02X", abbreviation[i]);
	}
	
	delete sha256;
	return QString::fromUtf8(abbreviationC);;
}