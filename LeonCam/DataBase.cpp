#include "DataBase.h"


DataBase::DataBase()
{	
}


DataBase::~DataBase()
{
}

void DataBase::SetPathToDB()
{
	QDir databasePath;
	pathToDB = databasePath.currentPath() + "/DataBase/LeonCamDB.sqlite";
}
bool DataBase::CreateUsers()
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS Users("
					"UserID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"Username VARCHAR(50) UNIQUE NOT NULL,"
					"Password CHAR(64) NOT NULL,"
					"SecurityQuestion TEXT NOT NULL,"
					"Answer CHAR(64) NOT NULL,"
					"RedAlertDeleteSettingID INTEGER NOT NULL REFERENCES AlertsDeleteSettings(AlertDeleteSettingID),"
					"GreenAlertDeleteSettingID INTEGER NOT NULL REFERENCES AlertsDeleteSettings(AlertDeleteSettingID),"
					"LastLogoutDate DATETIME NOT NULL,"
					"LastLoginAttemptDate DATETIME NOT NULL,"
					"LoginAttemptCounter INTEGER NOT NULL,"
					"RegistrationDate DATETIME NOT NULL);");

	bool result;
	result=query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateRedAlerts() 
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS RedAlerts("
					"RedAlertID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"CameraID INTEGER REFERENCES Cameras(CameraID),"
					"StartDate DATETIME NOT NULL,"
					"StopDate DATETIME NOT NULL,"
					"UserID INTEGER REFERENCES Users(UserID));");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateGreenAlerts() 
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS GreenAlerts("
					"GreenAlertID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"FaceID INTEGER REFERENCES Faces(FaceID),"
					"CameraID INTEGER REFERENCES Cameras(CameraID),"
					"StartDate DATETIME NOT NULL,"
					"StopDate DATETIME NOT NULL,"
					"UserID INTEGER REFERENCES Users(UserID));");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateAlertsDeleteSettings()
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS AlertsDeleteSettings("
					"AlertDeleteSettingID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"Date TEXT NOT NULL);");

	bool result;
	result = query.isActive() == true ? true : false;
	
	if (result == true) 
	{
		query.clear();
		query.prepare("SELECT COUNT(*) FROM AlertsDeleteSettings");
		query.exec();
		result = query.isActive() == true ? true : false;

		query.next();
		int queryResult = query.value(0).toInt();
		if (queryResult == 0 && result==true)
		{
			query.clear();
			query.exec("BEGIN IMMEDIATE TRANSACTION");
			query.prepare("INSERT INTO AlertsDeleteSettings (Date) VALUES (?)");
			QVariantList times;
			times << "never" << "1 day" << "1 week" << "1 month" << "half a year" << "1 year";
			query.addBindValue(times);

			result = query.execBatch() == true ? true : false;
			query.exec("COMMIT");
		}
	}

	return result;
}
bool DataBase::CreateCameras()
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS Cameras("
					"CameraID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"Name TEXT NOT NULL,"
					"IPAddress VARCHAR(45) NOT NULL," /*With port No*/
					"Login TEXT NOT NULL,"
					"Password TEXT NOT NULL,"
					"UserID INTEGER REFERENCES Users(UserID),"
					"LastEditDate DATETIME NOT NULL);");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}

bool DataBase::CreateFaces() 
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS Faces("
					"FaceID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"Name VARCHAR(50) NOT NULL,"
					"Surname VARCHAR(50) NOT NULL,"
					"LastEditedBy INTEGER REFERENCES Users(UserID) NOT NULL,"
					"LastEditDate DATETIME NOT NULL);");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateMoviesSettings() 
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS MoviesSettings("
					"UserID INTEGER PRIMARY KEY REFERENCES Users(UserID),"
					"CameraID INTEGER REFERENCES Cameras(CameraID));");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateFacesModulesSettings() 
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS MoviesSettings("
					"UserID INTEGER PRIMARY KEY REFERENCES Users(UserID),"
					"Time TIME NOT NULL);");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateDB()
{
	bool creationResult = true;
	SetPathToDB();
	dataBase = QSqlDatabase::addDatabase("QSQLITE");//create a default connection
	dataBase.setDatabaseName(pathToDB);

	if (dataBase.open() == false) //open the physical connection to DB
	{
		Utilities::MBAlarm("connection with database failed", false);
	}
	else
	{
		creationResult &= CreateUsers();
		creationResult &= CreateRedAlerts();
		creationResult &= CreateGreenAlerts();
		creationResult &= CreateAlertsDeleteSettings();
		creationResult &= CreateCameras();
		creationResult &= CreateFaces();
		creationResult &= CreateMoviesSettings();
		creationResult &= CreateFacesModulesSettings();

	}
	dataBase.removeDatabase("QSQLITE"); //Removes the DB connection [connectionName] from the list of database connections
	return creationResult;
	
}