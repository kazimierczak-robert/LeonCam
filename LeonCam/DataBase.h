#pragma once
#include <QSqlDatabase>
#include <QMessageBox>
#include "qdir.h"
#include "qsqlquery.h"


class DataBase
{
public:
	DataBase();
	~DataBase();
	bool DataBase::CreateDB();
	void AlarmAboutError(QString error);
private:
	QSqlDatabase dataBase;
	QString pathToDB;
	void SetPathToDB();
	bool CreateUsers();
	bool CreateRedAlerts();
	bool CreateGreenAlerts();
	bool CreateAlertsDeleteSettings();
	bool CreateCameras();
	bool CreateUsersCameras();
	bool CreatePresets();
	bool CreateCamerasPresets();
	bool CreateFaces();
	bool CreateMoviesSettings();
	bool CreateFacesModulesSettings();
};

