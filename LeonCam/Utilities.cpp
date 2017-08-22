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


bool Utilities::SaveToBinFile(std::string fileName, BYTE *data)
{
	FILE *file = NULL;
	fopen_s(&file, fileName.c_str(), "wb");
	if (file != NULL)
	{
		fwrite(data, 1, 32, file);
	}
	else
	{
		printf("%s is corrupted!", fileName.c_str());
		fclose(file);
		return false;
	}

	fclose(file);
	return true;
}
BYTE * Utilities::ReadFromBinFile(std::string fileName)
{
	FILE *file = NULL;
	fopen_s(&file, fileName.c_str(), "rb");
	if (file != NULL)
	{
		long lSize;
		BYTE * data;
		size_t result;

		fseek(file, 0, SEEK_END);
		lSize = ftell(file);
		rewind(file);

		data = new BYTE[lSize];
		if (data != NULL)
		{
			result = fread(data, 1, lSize, file);

			if (result == lSize)
			{
				fclose(file);
				return data;
			}
			else
			{
				fclose(file);
				return NULL;
			}

		}
	}
	else
	{
		//std::cout << fileName << " is corrupted!" << std::endl;
		return NULL;
	}
}
int Utilities::BinFileElementsNo(std::string fileName)
{
	FILE *file = NULL;
	int lSize = 0;
	fopen_s(&file, fileName.c_str(), "rb");
	if (file != NULL)
	{

		BYTE * data;
		size_t result;

		fseek(file, 0, SEEK_END);
		lSize = ftell(file);

		fclose(file);
	}
	return lSize;
}
