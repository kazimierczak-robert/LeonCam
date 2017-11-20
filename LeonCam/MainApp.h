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
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLineSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QDate>
#include <QLocale>
#include <algorithm>

using namespace QtCharts;


class MainApp : public QMainWindow
{
	Q_OBJECT

		enum chartOption
	{
		week = 0,
		day = 1,
		hour = 2
	};
	
public:
	MainApp(QWidget *parent = Q_NULLPTR, int loggedID=-1, std::string passHash="");
	~MainApp();
signals:
	void closeCameraEdit(const QString& cameraDetails);
public: signals:
		void checkGreenAlertInList(int greenAlertID);
		void checkRedAlertID(int redAlertID);
private slots:
	void AddCamera();
	void LogOut();
	void LESearchChanged();
	void LESearchPressed();
	void TWCameraPagesChanged(int newIndex);
	//Faces Base
	void UpdateDBAfterCellChanged(int row, int column);
	void TakePicture(int faceID);
	void LESearchFBChanged();
	void AddPerson();
	void EditPerson(int faceID);
	void RemovePerson(int faceID);
	void RemoveGreenAlert(int greenAlertID);
	void RemoveRedAlert(int redAlertID);
	void ChangeTWReport(int i);
public slots:
	void OpenCameraEdit(int cameraID);
	void UpdateThumbnail(const QPixmap& pixmap, int cameraID);
	void InsertGreenAlert(int greenAlertID, int faceID, int cameraID, QString dateTimeNow);
	void InsertRedAlert(int redAlertID, int cameraID, QString dateTimeNow);
	void UpdateGreenAlert(int greenAlertID, QString stopDate);
	void UpdateRedAlert(int redAlertID, QString stopDate);
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
	std::map<int, int> weekChartGreenMap;
	std::map<int, int> weekChartRedMap;
	QDateTime todayDateTime;
	int getCameraIDFromLayout(QGridLayout* layout);
	Camera* GetCameraFromDBByID(int cameraID);
	void TurnOnOffCamera(QGridLayout* layout);
	void RecognitionCamera(QPushButton* button, int cameraID);
	void EditCamera(int cameraID, QLabel *label);
	void DeleteCameraFromMemory(QGridLayout* layout);
	void RemoveCamera(QGridLayout* layout);
	void AddCameraFromDB(int cameraID);
	void AddTab();
	void CameraSelected(QGridLayout* layout);
	void closeEvent(QCloseEvent *event);
	void AdjustFaceBaseTW();
	void AdjustGreenReportsTW();
	void AdjustRedReportsTW();
	void FillFacesBaseTW();
	void GetAlertDeleteSettings();
	void FillCBSetsWithAlertDelSets();
	void FillReportsTW();
	void AddRowToFB(int faceID, QString name, QString surname);
	void AddRowToGreenReports(int greenAlertID, int cameraID, int faceID, QString name, QString surname, QString startDate, QString stopDate);
	void AddRowToRedReports(int redAlertID, int cameraID, QString startDate, QString stopDate);
	void CurrentIndexChanged();
	int GetChartRange();
	void StatisticsChart();
};
