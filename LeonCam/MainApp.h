#pragma once

#include <QMainWindow>
#include "ui_MainApp.h"
#include <qlabel.h>
#include <qlayout.h>
#include "LogIn.h"
#include "CameraPreview.h"
#include "UserCamera.h"
#include "CameraEdition.h"
#include <algorithm>
#include <QHBoxLayout>
#include <QFormLayout>
#include <qdialogbuttonbox.h>
#include "NewPhoto.h"
#include <map>
#include "MainAppCamera.h"
#include "qsqlresult.h"

class MainApp : public QMainWindow
{
	Q_OBJECT

public:
	MainApp(QWidget *parent = Q_NULLPTR, int loggedID=-1, std::string passHash="");
	~MainApp();
signals:
	void closeCameraEdit(const QString& cameraDetails);
private slots:
	void AddCamera();
	void LogOut();
	void LESearchChanged();
	void LESearchPressed();
	void TWCameraPagesChanged(int newIndex);
	//Faces Base
	void UpdateDBAfterCellChanged(int row, int column);
	void TakePicture(int FaceID);
	void LESearchFBChanged();
	void AddPerson();
	void EditPerson(int FaceID);
	void RemovePerson(int FaceID);
	void RemoveGreenAlert(int greenAlertID);
	void RemoveRedAlert(int redAlertID);
	void ChangeTWReport();
public slots:
	void OpenCameraEdit(int camID);
	void UpdateThumbnail(const QPixmap& pixmap, int cameraID);
	void InsertGreenAlert(int greenAlertID, int faceID, int cameraID, QString dateTimeNow);
	void InsertRedAlert(int redAlertID, int cameraID, QString dateTimeNow);
private:
	bool greenOrRedAlert = 0; //0-green, 1-red
	int loggedID;
	std::string passHash;
	Ui::MainApp ui;
	QString username = "";
	std::vector<std::vector<QGridLayout*>*> *vectorCameraLayoutsPages;
	std::vector<QGridLayout*> *vectorQGridLayouts;
	std::map<int, std::string> alertDeleteSettingsToCB;
	ImgProc *imgProc = nullptr;
	map<int, MainAppCamera *> *cameraThread;
	int activeCameraPage;
	struct Camera
	{
		int CameraID;
		std::string Name;
		std::string IPAddress;
		std::string Login;
		std::string Password;
	};
	Camera* GetCameraFromDBByID(int CameraID);
	void TurnOnOffCamera(QGridLayout* layout);
	void TakePictureCamera(QPushButton* button);
	void RecognitionCamera(QPushButton* button, int cameraID);
	void EditCamera(int CameraID, QLabel *label);
	void DeleteCameraFromMemory(QGridLayout* layout);
	void RemoveCamera(QGridLayout* layout);
	void AddCameraFromDB(int CameraID);
	void addTab();
	void CameraSelected(QGridLayout* layout);
	void closeEvent(QCloseEvent *event);
	void AdjustFaceBaseTW();
	void AdjustGreenReportsTW();
	void AdjustRedReportsTW();
	void FillFacesBaseTW();
	void GetAlertDeleteSettings();
	void FillCBSetsWithAlertDelSets();
	void FillReportsTW();
	void AddRowToFB(int ID, QString name, QString surname);
	void AddRowToGreenReports(int greenAlertID, int cameraID, int faceID, QString name, QString surname, QString startDate, QString stopDate);
	void AddRowToRedReports(int redAlertID, int cameraID, QString startDate, QString stopDate);
	void CurrentIndexChanged();
};
