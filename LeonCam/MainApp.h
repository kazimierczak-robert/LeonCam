#pragma once

#include <QMainWindow>
#include "ui_MainApp.h"
#include <qlabel.h>
#include <qlayout.h>
#include "LogIn.h"
#include "CameraPreview.h"
#include "UserCamera.h"

class MainApp : public QMainWindow
{
	Q_OBJECT

public:
	MainApp(QWidget *parent = Q_NULLPTR);
	~MainApp();
private slots:
	void AddCamera();
	void LogOut();
	//void RowSelected(const QModelIndex& modelIndex);
	void LESearchChanged();
	void TWCameraPagesChanged(int newIndex);
private:
	Ui::MainApp ui;
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
	void RemoveCamera(QPushButton* button);
	int activeCameraPage;
	void addTab();
};
