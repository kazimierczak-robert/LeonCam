#pragma once

#include <QDialog>
#include "ui_CameraEdition.h"
#include "DesignBase.h"
#include "Utilities.h"
#include <regex>
#include <qsqlquery.h>

class CameraEdition : public QDialog
{
	Q_OBJECT

public:
	CameraEdition(QWidget *parent = Q_NULLPTR, int userID = -1, int camID=-1, std::string passHash ="");
	~CameraEdition();
	std::vector<QString>* GetValuesFromControls();
private slots:
	void BackClicked();
	void EditClicked();
private:
	DesignBase *designB;
	Ui::CameraEdition ui;
	int userID;
	int camID;
	std::string passHash;
};
