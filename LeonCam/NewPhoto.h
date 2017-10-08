#pragma once

#include <QDialog>
#include "ui_NewPhoto.h"
#include "Utilities.h"

class NewPhoto : public QDialog
{
	Q_OBJECT

public:
	//ID - photo is saved in the folder named .\\FaceBase\\<ID>
	NewPhoto(QString name, QString surname, int ID, QWidget *parent = Q_NULLPTR);
	~NewPhoto();
private slots:
	void BackButtonClicked();
private:
	Ui::NewPhoto ui;
};
