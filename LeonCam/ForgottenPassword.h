#pragma once

#include <QDialog>
#include "ui_ForgottenPassword.h"
#include "DesignBase.h"
#include "LogIn.h"
#include "qsystemtrayicon.h"

class ForgottenPassword : public QDialog
{
	Q_OBJECT

public:
	ForgottenPassword(QWidget *parent = Q_NULLPTR);
	~ForgottenPassword();
private slots:
	void VerifyClicked();
	void BackClicked();
private:
	DesignBase *designB;
	Ui::ForgottenPassword ui;
};
