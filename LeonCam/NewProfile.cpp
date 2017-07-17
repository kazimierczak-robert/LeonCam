#include "NewProfile.h"


NewProfile::NewProfile(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//Create DesignB instance
	DesignB = new DesignBase(this);
	//Set gif in Lloading label
	DesignB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBCreate, SIGNAL(clicked()), this, SLOT(CreateClicked()));
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackClicked()));
}

NewProfile::~NewProfile()
{
}
void NewProfile::CreateClicked()
{
	DesignB->gif->start();
}
void NewProfile::BackClicked()
{
	this->close();
}