#include "CameraEdition.h"

CameraEdition::CameraEdition(QWidget *parent)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	//Create DesignB instance
	designB = new DesignBase(this);
	//Set gif in Lloading label
	designB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackClicked()));
	connect(ui.PBEdit, SIGNAL(clicked()), this, SLOT(EditClicked()));
}

CameraEdition::~CameraEdition()
{
}

void CameraEdition::BackClicked()
{
	this->close();
}
void CameraEdition::EditClicked()
{
	//TODO
	designB->gif->start();
	this->close();
}