#pragma once

#include <QDialog>
#include "ui_UserCamera.h"
#include "DesignBase.h"
#include "Utilities.h"
#include <regex>
#include <qsqlquery.h>
#include "soapDiscoveryLookupBindingProxy.h"
#include <qfuture.h>
#include <QtConcurrent\qtconcurrentrun.h>
#include <qfuturewatcher.h>

class UserCamera : public QDialog
{
	Q_OBJECT

public:
	UserCamera(QWidget *parent=Q_NULLPTR, int userID=-1);
	~UserCamera();
	std::vector<QString>* GetValuesFromControls();
private slots:
	void AddClicked();
private:
	Ui::UserCamera ui;
	DesignBase *designB;
	int userID;
	void SearchForCameraIPs();
	std::string result;
	QFuture<void> *future;
	QFutureWatcher<void> *watcher;
	std::string GenerateUuid();
};
