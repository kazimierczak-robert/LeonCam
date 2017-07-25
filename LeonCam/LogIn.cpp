#include "LogIn.h"


LogIn::LogIn(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//Create DesignB instance
	designB = new DesignBase(this);
	//Set gif in Lloading label
	designB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBLogIn, SIGNAL(clicked()), this, SLOT(LogInClicked()));
	connect(ui.PBForgotPassword, SIGNAL(clicked()), this, SLOT(ForgotPasswordClicked()));
	connect(ui.PBNewProfile, SIGNAL(clicked()), this, SLOT(NewProfileClicked()));
}

void LogIn::LogInClicked()
{
	//Start gif
	designB->gif->start();
	MainApp *mainApp = new MainApp(nullptr);	
	mainApp->show();
	this->close();
}
void LogIn::ForgotPasswordClicked()
{
	ForgottenPassword *ForgottenPass = new ForgottenPassword(this);
	//hide window
	//this->hide();
	ForgottenPass->exec();
	//show window
	//this->show();
}
void LogIn::NewProfileClicked()
{
	NewProfile *NewProf = new NewProfile(this);
	//hide window
	//this->hide();
	NewProf->exec();
	//show window
	this->show();
	ui.LEUsername->setText("Working 3");
}