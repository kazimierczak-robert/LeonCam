#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LogIn.h"
#include <qpushbutton.h>
#include "ForgottenPassword.h"
#include "DesignBase.h"
#include "NewProfile.h"
#include "MainApp.h"
#include <qtooltip.h>

#define loginAttemptCounterMAX 3
#define loginTimeLock 900

class LogIn : public QMainWindow
{
	Q_OBJECT

public:
	LogIn(QWidget *parent = Q_NULLPTR);
	~LogIn();
	static void UpdateAttempts(int loginAttemptCounter, QString username);
	static void UpdateCounter(QString username);
private slots:
	void LogInClicked();
	void ForgotPasswordClicked();
	void NewProfileClicked();
private:
	Ui::LogInClass ui;
	DesignBase *designB = nullptr;
	QFuture<void> *future;
	QFutureWatcher<void> *watcher;
	int loggedID;
	std::string passHash;
};
