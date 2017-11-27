#pragma once

#include <QDialog>
#include "ui_ForgottenPassword.h"
#include "DesignBase.h"
#include "LogIn.h"
#include "qsystemtrayicon.h"
#include "qsqlquery.h"
#include <cstdlib>

#include <qfuture.h>
#include <QtConcurrent\qtconcurrentrun.h>
#include <qfuturewatcher.h>

class ForgottenPassword : public QDialog
{
	Q_OBJECT

public:
	ForgottenPassword(QWidget *parent = Q_NULLPTR, QString username="");
	~ForgottenPassword();
	void SetSecurityQuestion(QString username);
	QString GetPassHash() { return passHash; }
	int GetLoggedID() { return loggedID; }
private slots:
	void VerifyClicked();
	void BackClicked();
private:
	QString username;
	QString passHash;
	int loggedID;
	DesignBase *designB;
	Ui::ForgottenPassword ui;
	QFuture<void> *future;
	QFutureWatcher<void> *watcher;
	QString passwordFromMap;
};
