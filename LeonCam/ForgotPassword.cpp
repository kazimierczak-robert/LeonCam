#include "ForgotPassword.h"
#include "LogIn.h"
#include "qsystemtrayicon.h"



ForgotPassword::ForgotPassword(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//Create DesignB instance
	DesignB = new DesignBase(this);
	//Set gif in Lloading label
	DesignB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBVerify, SIGNAL(clicked()), this, SLOT(VerifyClicked()));
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackClicked()));
}

ForgotPassword::~ForgotPassword()
{
}

void ForgotPassword::VerifyClicked()
{
	DesignB->gif->start();
	ui.LSecurityQuestion->setText("Working!");
}
void ForgotPassword::BackClicked()
{
	this->close();
}