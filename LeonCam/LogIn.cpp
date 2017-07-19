#include "LogIn.h"


LogIn::LogIn(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//Create DesignB instance
	DesignB = new DesignBase(this);
	//Set gif in Lloading label
	DesignB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBLogIn, SIGNAL(clicked()), this, SLOT(LogInClicked()));
	connect(ui.PBForgotPassword, SIGNAL(clicked()), this, SLOT(ForgotPasswordClicked()));
	connect(ui.PBNewProfile, SIGNAL(clicked()), this, SLOT(NewProfileClicked()));
}

void LogIn::LogInClicked()
{
	//Start gif
	DesignB->gif->start();
	ui.LUsername->setText("Working");
	MainApp *mainApp = new MainApp(nullptr);	
	mainApp->show();
	this->close();
}
void LogIn::ForgotPasswordClicked()
{
	ForgotPassword *ForgotPass = new ForgotPassword(this);
	//hide window
	//this->hide();
	ForgotPass->exec();
	//show window
	this->show();
}
void LogIn::NewProfileClicked()
{
	NewProfile *NewProf = new NewProfile(this);
	//hide window
	//this->hide();
	NewProf->exec();
	//show window
	this->show();
	ui.LUsername->setText("Working 3");
}