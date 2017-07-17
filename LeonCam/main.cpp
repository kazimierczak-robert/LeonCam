#include "LogIn.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LogIn w;
	w.show();
	return a.exec();
}
