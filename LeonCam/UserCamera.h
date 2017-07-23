#pragma once

#include <QDialog>
#include "ui_UserCamera.h"
#include "DesignBase.h"

class UserCamera : public QDialog
{
	Q_OBJECT

public:
	UserCamera(QWidget *parent = Q_NULLPTR);
	~UserCamera();
private slots:
	void VerifyClicked();
	void DefineClicked();
	void BackClicked();
	void AssignChecked();
private:
	void UserCamera::DisableIfAssignChanged(bool flag);
	Ui::UserCamera ui;
	DesignBase *DesignB;
};
