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
		dataBase->AlarmAboutError("Data base is failed, please contact with system administrator");
		delete dataBase;
		return -1;
	}
	delete dataBase;
	w.show();
	return a.exec();
}
