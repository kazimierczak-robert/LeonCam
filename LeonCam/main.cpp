#include "LogIn.h"
#include <QtWidgets/QApplication>
#include "DataBase.h"
#include <qlockfile.h>
//#include <qprocess.h>

std::string Utilities::resultMsg = "";

int main(int argc, char *argv[])
{
	/*QProcessEnvironment e = QProcessEnvironment::systemEnvironment();
	QString ss = e.value("PATH");
	e.insert("PATH", "$(QTDIR)\bin%3bopencv\x64\vc14\bin%3bopenssl-win64\lib%3b" + ss);
	QString ss2 = e.value("PATH");*/

	QApplication a(argc, argv);

	QLockFile lockFile(QDir::temp().absoluteFilePath("leoncam.lock"));
	if (!lockFile.tryLock(100))
	{
		Utilities::MBAlarm("The application is already running.", false);
		return 1;
	}

	LogIn w;
	//Create DB file if not exists
	DataBase *dataBase = new DataBase();
	bool result = false;
	result = dataBase->CreateDB();
	if (result == false)
	{
		Utilities::MBAlarm("Data base is failed, please, contact with system administrator", false);
		delete dataBase;
		return -1;
	}
	
	//Limit number of signs in password 127!
	/*std::string encryptedMsg= Utilities::GetEncrypted("01234567890123456789012345678901", "abcdefghijklłmnńdkjfbkdjfiuegfsabcdefghijklłmnńdkjfbkdjfiuegfsabcdefghijklłmnńdkjfbkdjfiuegfsabcdefghijklłmnńdkjfbkdjfiuegfsas");
	std::string decryptedMSG = Utilities::GetDecrypted("01234567890123456789012345678901", encryptedMsg);
	*/
	delete dataBase;

	w.show();

	return a.exec();
}

