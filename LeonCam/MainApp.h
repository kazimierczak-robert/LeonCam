#pragma once

#include <QMainWindow>
#include "ui_MainApp.h"
#include <qlabel.h>
#include <qlayout.h>
#include "LogIn.h"

class MainApp : public QMainWindow
{
	Q_OBJECT

public:
	MainApp(QWidget *parent = Q_NULLPTR);
	~MainApp();
private slots:
	void AddNewCamera();
	void LogOut();
private:
	Ui::MainApp ui;
};
