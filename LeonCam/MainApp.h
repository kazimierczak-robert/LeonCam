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
private:
	Ui::MainApp ui;
	QString username;
	std::vector<std::vector<QLayout*>*> *vectorCameraLayoutsPages;
	std::vector<QGridLayout*> *vectorQGridLayouts;
	std::vector<QPushButton*> *vectorIsEnabledButtonToRowIndex;
	std::vector<QPushButton*> *vectorPatrolButtonToRowIndex;
	std::vector<QPushButton*> *vectorRecognationButtonToRowIndex;
	std::vector<QPushButton*> *vectorEditButtonToRowIndex;
	std::vector<QPushButton*> *vectorRemoveButtonToRowIndex;
	void TurnOnOffCamera(QPushButton* button);
	void PatrolCamera(QPushButton* button);
	void RecognationCamera(QPushButton* button);
	void EditCamera(QPushButton* button);
	void RemoveCamera(QGridLayout* layout);
	int activeCameraPage;
	void addTab();
	void CameraSelected(QGridLayout* layout);
	void MainApp::closeEvent(QCloseEvent *event);
};
