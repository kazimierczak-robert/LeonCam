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
	designB->gif->start();
	QString username = "";
	QString password = "";
	username = ui.LEUsername -> text();
	password = ui.LEPassword->text();
	if (username == "" || password == "")
	{
		designB->gif->stop();
		Utilities::MBAlarm("At least one field is incomplete", false);
		return;
	}

	std::string concatHelp = "";
	concatHelp = password.toStdString() + username.toStdString();
	QString passwordHash = Utilities::CreateHash(concatHelp);
	//Get proper user from DB
	QSqlQuery query;
	query.prepare("SELECT COUNT(*) FROM Users WHERE Username = (:Username) AND Password = (:Password)");
	query.bindValue(":Username", username);
	query.bindValue(":Passsword", password);
	bool result = query.exec() == true ? true : false;
	if (result == true)
	{
		query.next();
		if (query.value(0).toInt() == 1)
		{
			MainApp *mainApp = new MainApp(nullptr);
			mainApp->show();
			this->close();
		}
		else
		{
			designB->gif->stop();
			Utilities::MBAlarm("Typed data is incorrect. Please, try log in again", false);
		}	
	}
	else
	{
		designB->gif->stop();
		Utilities::MBAlarm("User has not been found. Please, try log in again", false);
	}
	ui.LEPassword->setText("");
}
void LogIn::ForgotPasswordClicked()
{
	ForgottenPassword *forgottenPassword = new ForgottenPassword(this);
	forgottenPassword->exec();
	delete forgottenPassword;
}
void LogIn::NewProfileClicked()
{
	NewProfile *newProfile = new NewProfile(this);
	newProfile->exec();
	delete newProfile;
}