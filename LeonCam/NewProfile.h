#pragma once

#include <QDialog>
#include "ui_NewProfile.h"
#include "DesignBase.h"
#include "Utilities.h"
#include <regex>
#include <qsqlquery.h>
#include "qdatetime.h"
#include "SHA256.h"

class NewProfile : public QDialog
{
	Q_OBJECT
private slots:
	void CreateClicked();
	void BackClicked();
public:
	NewProfile(QWidget *parent = Q_NULLPTR);
	~NewProfile();

private:
	Ui::NewProfile ui;
	DesignBase *designB;
};
