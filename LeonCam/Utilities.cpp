#include "Utilities.h"



Utilities::Utilities()
{
}


Utilities::~Utilities()
{
}
bool Utilities::MBQuestion(QString message)
{
	//http://doc.qt.io/qt-4.8/qmessagebox.html
	QMessageBox msgBox;
	QPixmap pixmap(iconPath);
	QIcon ButtonIcon(pixmap);
	msgBox.setWindowIcon(ButtonIcon);
	msgBox.setText(message);
	//msgBox.setInformativeText(message);
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::No);
	msgBox.adjustSize();
	int result = msgBox.exec();
	if (result == QMessageBox::Yes)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Utilities::MBAlarm(QString alarm, bool errorOrSuccess)
{
	QMessageBox msgBox;
	QPixmap pixmap(iconPath);
	QIcon ButtonIcon(pixmap);
	msgBox.setWindowIcon(ButtonIcon);
	//msgBox.setStyleSheet("QPushButton{background-color: rgb(36, 118, 59);color: rgb(255, 255, 255); }QPushButton:hover{background-color: rgb(39, 129, 63);}");

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
//https://stackoverflow.com/a/10632725
std::string Utilities::sha256(const std::string str)
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str.c_str(), str.size());
	SHA256_Final(hash, &sha256);
	std::stringstream ss;
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		ss << std::hex << std::uppercase<< std::setw(2) << std::setfill('0') << (int)hash[i];
	}
	return ss.str();
}
void Utilities::OpenFileExplorer(int ID)
{
	QString path = ".\\FaceBase\\" + QVariant(ID).toString();
	//https://stackoverflow.com/a/11517874
	QDir folder(path);
	if (!folder.exists())
	{
		folder.mkpath(".");
	}
	//https://stackoverflow.com/q/3490336
	QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}
void Utilities::CreateFolderIfNotExists(QString path)
{
	//Create Picture folder if doesn't exist
	//https://stackoverflow.com/a/11517874
	QDir folder(path);
	if (!folder.exists())
	{
		folder.mkpath(".");
	}
}
//https://stackoverflow.com/a/27758627
void Utilities::RemoveFolderRecursively(int FaceID)
{
	QString path = ".\\FaceBase\\" + QVariant(FaceID).toString();
	QDir dir(path);
	int result=dir.removeRecursively();
	if (result == true)
	{
		Utilities::MBAlarm("Folder " + path +" has been removed!", true);
	}
	else
	{
		Utilities::MBAlarm("Folder " + path + " hasn't been removed!", true);
	}
}