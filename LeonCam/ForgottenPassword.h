#pragma once

#include <QDialog>
#include "ui_ForgottenPassword.h"
#include "DesignBase.h"
#include "LogIn.h"
#include "qsystemtrayicon.h"
#include "qsqlquery.h"

class ForgottenPassword : public QDialog
{
	Q_OBJECT

public:
	ForgottenPassword(QWidget *parent = Q_NULLPTR, QString username="");
	~ForgottenPassword();
	void SetSecurityQuestion(QString username);
private slots:
	void VerifyClicked();
	void BackClicked();
private:
	QString username;
	DesignBase *designB;
	Ui::ForgottenPassword ui;

};
