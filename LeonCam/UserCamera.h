#pragma once

#include <QDialog>
#include "ui_UserCamera.h"
#include "DesignBase.h"
#include "Utilities.h"
#include <regex>
#include <qsqlquery.h>

class UserCamera : public QDialog
{
	Q_OBJECT

public:
	UserCamera(QWidget *parent=Q_NULLPTR, int userID=-1);
	~UserCamera();
	std::vector<QString>* GetValuesFromControls();
private slots:
	void AddClicked();
	void BackClicked();
	void AssignChecked();
private:
	void DisableIfAssignChanged(bool flag);
	Ui::UserCamera ui;
	DesignBase *designB;
	int userID;
};
