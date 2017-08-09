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
QString Utilities::GetCurrentDateTime()
{
	//get system current time
	QDateTime currentDateTime = QDateTime::currentDateTime();
	QString currentDateTimeS = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");
	return currentDateTimeS;
}
