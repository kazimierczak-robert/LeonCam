#include "LogIn.h"
#include <QtWidgets/QApplication>
#include "DataBase.h"

std::string Utilities::resultMsg = "";

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
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
	//

	w.show();

	return a.exec();
}

