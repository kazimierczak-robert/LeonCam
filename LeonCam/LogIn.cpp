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

	SHA256 *sha256 = new SHA256();
	std::string concatHelp = "";
	concatHelp = password.toStdString() + username.toStdString();
	QString passwordHash = QString::fromStdString(sha256->sha256_abbreviation(concatHelp));

	//Get proper user from DB
	QSqlQuery query;
	query.prepare("SELECT COUNT (*) FROM Users WHERE Username = ? AND Password = ?");
	query.bindValue(0, username);
	query.bindValue(1, passwordHash);
	bool result = query.exec() == true ? true : false;
	if (result == true)
	{
		query.next();
		int result = query.value(0).toInt();
		if (result == 1)
		{
			if (ui.CBKeepMeLoggedIn->isChecked() == true)
			{
				query.clear();
				query.prepare("UPDATE Users SET KeepMeLoggedIn = 1 WHERE Username = ? AND Password = ?");
				query.bindValue(0, username);
				query.bindValue(1, passwordHash);
				bool result = query.exec() == true ? true : false;
				if (result == false)
				{
					designB->gif->stop();
					Utilities::MBAlarm("<i>Keep me logged in</i> option has been skipped", false);
				}
			}
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
	if (ui.LEUsername->text() == "")
	{
		QToolTip::showText(ui.PBForgotPassword->mapToGlobal(QPoint(0, 0)),ui.PBForgotPassword->toolTip());
	}
	else
	{
		ForgottenPassword *forgottenPassword = new ForgottenPassword(this);
		forgottenPassword->SetSecurityQuestion(ui.LEUsername->text());
		forgottenPassword->exec();
		delete forgottenPassword;
	}
}
void LogIn::NewProfileClicked()
{
	NewProfile *newProfile = new NewProfile(this);
	newProfile->exec();
	delete newProfile;
}