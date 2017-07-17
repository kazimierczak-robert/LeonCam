#pragma once

#include <QDialog>
#include "ui_ForgotPassword.h"
#include "DesignBase.h"

class ForgotPassword : public QDialog
{
	Q_OBJECT

public:
	ForgotPassword(QWidget *parent = Q_NULLPTR);
	~ForgotPassword();
	Ui::ForgotPassword getLLoading() { return ui; }
private slots:
	void VerifyClicked();
	void BackClicked();
private:
	DesignBase *DesignB;
	Ui::ForgotPassword ui;
};
