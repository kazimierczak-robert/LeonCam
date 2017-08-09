#include "LogIn.h"
#include <QtWidgets/QApplication>

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
	delete dataBase;
	w.show();

	return a.exec();
}
