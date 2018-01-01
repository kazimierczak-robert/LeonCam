#pragma once
#include <QSqlDatabase>
#include "qdir.h"
#include "qsqlquery.h"
#include "qvariant.h"
#include "Utilities.h"

class DataBase
{
public:
	DataBase();
	~DataBase();
	bool DataBase::CreateDB();
private:
	QSqlDatabase dataBase;
	QString pathToDB;
	void SetPathToDB();
	bool CreateUsers();
	bool CreateRedAlerts();
	bool CreateGreenAlerts();
	bool CreateAlertsDeleteSettings();
	bool CreateCameras();
	bool CreateFaces();
};

