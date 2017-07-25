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
void DataBase::AlarmAboutError(QString error)
{
	QMessageBox msgBox;
	msgBox.setText("Error: " + error);
	msgBox.exec();
}
bool DataBase::CreateUsers()
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS Users("
					"UserID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"Username VARCHAR(50) UNIQUE NOT NULL,"
					"Password CHAR(64) NOT NULL,"
					"KeepMeLoggedIn BOOLEAN NOT NULL,"
					"SecurityQuestion TEXT NOT NULL,"
					"Answer CHAR(64) NOT NULL,"
					"RedAlertDeleteSettingID INTEGER NOT NULL REFERENCES AlertsDeleteSettings(AlertDeleteSettingID),"
					"GreenAlertDeleteSettingID INTEGER NOT NULL REFERENCES AlertsDeleteSettings(AlertDeleteSettingID),"
					"LastLogoutDate DATETIME NOT NULL,"
					"RegistrationDate DATETIME NOT NULL);");

	bool result;
	result=query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateRedAlerts() 
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS RedAlerts("
					"RedAlertID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"Date DATETIME NOT NULL);");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateGreenAlerts() 
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS GreenAlerts("
					"GreenAlertID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"Date DATETIME NOT NULL,"
					"FaceID INTEGER REFERENCES Faces(FaceID),"
					"UserID INTEGER REFERENCES Users(UserID));");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateAlertsDeleteSettings()
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS AlertsDeleteSettings("
					"AlertDeleteSettingID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"Date DATETIME NOT NULL);");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateCameras()
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS Cameras("
					"CameraID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"Model TEXT NOT NULL,"
					"IPAddress VARCHAR(39) NOT NULL,"
					"Login TEXT NOT NULL);");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateUsersCameras()
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS UsersCameras("
					"UserCameraID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"UserID INTEGER REFERENCES Users(UserID),"
					"CameraID INTEGER REFERENCES Cameras(CameraID),"
					"Password CHAR(256) NOT NULL);");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreatePresets() 
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS Presets("
					"PresetID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"Name TEXT NOT NULL,"
					"Description TEXT NOT NULL);");

	bool result;
	result = query.isActive() == true ? true : false;
	return result;
}
bool DataBase::CreateCamerasPresets() 
{
	QSqlQuery query("CREATE TABLE IF NOT EXISTS CamerasPresets("
					"CameraPresetID INTEGER PRIMARY KEY AUTOINCREMENT,"
					"CameraID INTEGER REFERENCES Cameras(CameraID),"
					"PresetID INTEGER REFERENCES Presets(PresetID));");

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
					"FacePath TEXT NOT NULL);");

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
		AlarmAboutError("connection with database failed");
	}
	else
	{
		creationResult &= CreateUsers();
		creationResult &= CreateRedAlerts();
		creationResult &= CreateRedAlerts();
		creationResult &= CreateAlertsDeleteSettings();
		creationResult &= CreateCameras();
		creationResult &= CreateUsersCameras();
		creationResult &= CreatePresets();
		creationResult &= CreateCamerasPresets();
		creationResult &= CreateFaces();
		creationResult &= CreateMoviesSettings();
		creationResult &= CreateFacesModulesSettings();
	}
	dataBase.removeDatabase("QSQLITE"); //Removes the DB connection [connectionName] from the list of database connections
	return creationResult;
	
}