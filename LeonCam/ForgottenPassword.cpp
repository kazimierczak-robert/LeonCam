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

void ForgottenPassword::SetSecurityQuestion(QString username)
{
	this->username = username;
	//Get user from DB with Username==<Username>
	QSqlQuery query;
	query.exec("SELECT SecurityQuestion FROM Users WHERE Username = ?");
	query.bindValue(0, this->username);
	bool result = query.exec() == true ? true : false;
	if (result == true)
	{
		query.next();
		QString securityQuestion = query.value(0).toString();
		ui.LESecurityQuestion->setText(securityQuestion);
	}
	else
	{
		Utilities::MBAlarm("Problem with loading <i> Security Question </i>", false);
	}
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
