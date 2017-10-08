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
#include <QCloseEvent>
#include <QHBoxLayout>
#include <QFormLayout>
#include <qdialogbuttonbox.h>
#include "NewPhoto.h"

class MainApp : public QMainWindow
{
	Q_OBJECT

public:
	MainApp(QWidget *parent = Q_NULLPTR, QString username = "");
	~MainApp();
private slots:
	void AddCamera();
	void LogOut();
	void LESearchChanged();
	void TWCameraPagesChanged(int newIndex);
	//Faces Base
	void UpdateDBAfterCellChanged(int row, int column);
	void TakePicture(int ID);
	void LESearchFBChanged();
	void AddPerson();
	void EditPerson(int ID);
	void RemovePerson(int ID);
private:
	//TODO: Remove this help var
	int helpVar = 0;
	Ui::MainApp ui;
	QString username;
	std::vector<std::vector<QLayout*>*> *vectorCameraLayoutsPages;
	std::vector<QGridLayout*> *vectorQGridLayouts;
	void TurnOnOffCamera(QPushButton* button);
	void PatrolCamera(QPushButton* button);
	void RecognationCamera(QPushButton* button);
	void EditCamera(QPushButton* button);
	void RemoveCamera(QGridLayout* layout);
	int activeCameraPage;
	void addTab();
	void CameraSelected(QGridLayout* layout);
	void closeEvent(QCloseEvent *event);
	void AdjustFaceBaseTW();
	void FillFacesBaseTW();
	void AddRowToFB(int ID, QString name, QString surname);
};
