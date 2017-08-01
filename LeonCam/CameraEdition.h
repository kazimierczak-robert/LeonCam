#pragma once

#include <QDialog>
#include "ui_CameraEdition.h"
#include "DesignBase.h"

class CameraEdition : public QDialog
{
	Q_OBJECT

public:
	CameraEdition(QWidget *parent = Q_NULLPTR);
	~CameraEdition();
private slots:
	void BackClicked();
	void EditClicked();
private:
	DesignBase *designB;
	Ui::CameraEdition ui;
};
