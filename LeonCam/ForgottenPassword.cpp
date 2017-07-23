#include "ForgottenPassword.h"

ForgottenPassword::ForgottenPassword(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//Create DesignB instance
	designB = new DesignBase(this);
	//Set gif in Lloading label
	designB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBVerify, SIGNAL(clicked()), this, SLOT(VerifyClicked()));
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackClicked()));
}

ForgottenPassword::~ForgottenPassword()
{
}

void ForgottenPassword::VerifyClicked()
{
	designB->gif->start();
	ui.LSecurityQuestion->setText("Working!");
}
void ForgottenPassword::BackClicked()
{
	this->close();
}
