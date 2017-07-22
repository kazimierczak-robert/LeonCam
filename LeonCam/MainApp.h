#pragma once

#include <QMainWindow>
#include "ui_MainApp.h"
#include <qlabel.h>
#include <qlayout.h>
#include "LogIn.h"
#include "CameraPreview.h"

class MainApp : public QMainWindow
{
	Q_OBJECT

public:
	MainApp(QWidget *parent = Q_NULLPTR);
	~MainApp();
private slots:
	void AddNewCamera();
	void LogOut();
	void RowSelected(const QModelIndex& modelIndex);
private:
	Ui::MainApp ui;
	void TurnOnOffCamera(QPushButton* button);
	std::vector<QPushButton*> *vectorIsEnabledButtonToRowIndex;
	std::vector<QPushButton*> *vectorRemoveButtonToRowIndex;
	void RemoveCamera(QPushButton* button);
};
