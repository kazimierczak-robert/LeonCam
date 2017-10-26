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
	void TWCameraPagesChanged(int newIndex);
	//Faces Base
	void UpdateDBAfterCellChanged(int row, int column);
	void TakePicture(int FaceID);
	void LESearchFBChanged();
	void AddPerson();
	void EditPerson(int FaceID);
	void RemovePerson(int FaceID);
	void ChangeTWReport();
public slots:
	void OpenCameraEdit(int camID);
private:
	bool greenOrRedAlert = 0; //0-green, 1-red
	int loggedID;
	std::string passHash;
	Ui::MainApp ui;
	QString username = "";
	std::vector<std::vector<QGridLayout*>*> *vectorCameraLayoutsPages;
	std::vector<QGridLayout*> *vectorQGridLayouts;
	void TurnOnOffCamera(QGridLayout* layout);
	void TakePictureCamera(QPushButton* button);
	void RecognationCamera(QPushButton* button);
	void EditCamera(int CameraID, QLabel *label);
	void RemoveCamera(QGridLayout* layout);
	void AddCameraFromDB(int CameraID);
	int activeCameraPage;
	void addTab();
	void CameraSelected(QGridLayout* layout);
	void closeEvent(QCloseEvent *event);
	void AdjustFaceBaseTW();
	void AdjustGreenReportsTW();
	void AdjustRedReportsTW();
	void FillFacesBaseTW();
	void FillReportsTW();
	void AddRowToFB(int ID, QString name, QString surname);
};
