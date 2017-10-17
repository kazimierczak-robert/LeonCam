#pragma once

#include <QDialog>
#include "ui_UserCamera.h"
#include "DesignBase.h"
#include "Utilities.h"
#include <regex>

class UserCamera : public QDialog
{
	Q_OBJECT

public:
	UserCamera(QWidget *parent=Q_NULLPTR);
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
};
