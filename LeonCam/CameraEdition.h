#pragma once

#include <QDialog>
#include "ui_CameraEdition.h"
#include "DesignBase.h"
#include "Utilities.h"
#include <regex>
#include <qsqlquery.h>
#include <qfuture.h>
#include <QtConcurrent\qtconcurrentrun.h>
#include <qfuturewatcher.h>

class CameraEdition : public QDialog
{
	Q_OBJECT

public:
	CameraEdition(QWidget *parent = Q_NULLPTR, int userID = -1, int camID=-1, std::string passHash ="");
	~CameraEdition();
	std::vector<QString>* GetValuesFromControls();
private slots:
	void EditClicked();
private:
	DesignBase *designB;
	Ui::CameraEdition ui;
	int userID;
	int camID;
	std::string passHash;
	std::string result;
	QFuture<void> *future;
	QFutureWatcher<void> *watcher;
};
