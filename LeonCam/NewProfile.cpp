#include "NewProfile.h"


NewProfile::NewProfile(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//Create DesignB instance
	designB = new DesignBase(this);
	//Set gif in Lloading label
	designB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBCreate, SIGNAL(clicked()), this, SLOT(CreateClicked()));
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackClicked()));
}

NewProfile::~NewProfile()
{
}
void NewProfile::CreateClicked()
{
	designB->gif->start();
}
void NewProfile::BackClicked()
{
	this->close();
}