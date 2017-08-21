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
	connect(ui.LEUsername, SIGNAL(returnPressed()), this, SLOT(LogInClicked()));
	connect(ui.LEPassword, SIGNAL(returnPressed()), this, SLOT(LogInClicked()));
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
			//check if account is not locked
			QDateTime currentDateTime = QDateTime::fromString(Utilities::GetCurrentDateTime(), "yyyy-MM-dd HH:mm:ss");
			query.clear();
			query.prepare("SELECT LastLoginAttemptDate, LoginAttemptCounter FROM Users WHERE Username=?");
			query.bindValue(0, username);
			bool result = query.exec() == true ? true : false;
			if (result == true)
			{
				query.next();				
				QDateTime lastLoginAttemptDate = query.value(0).toDateTime();
				int loginAttemptCounter = query.value(1).toInt();
				int secondsDiff = lastLoginAttemptDate.secsTo(currentDateTime);
				if (secondsDiff > loginTimeLock) { loginAttemptCounter = 0; }
				if (loginAttemptCounter < loginAttemptCounterMAX)
				{
					UpdateAttempts(0, username);
					MainApp *mainApp = new MainApp(nullptr, username);
					mainApp->show();
					this->close();
				}
				else
				{
					//QString secondsDiffS = QString::number(15 - secondsDiff/60);
					designB->gif->stop();
					Utilities::MBAlarm("Your account is blocked! Try again after few minutes", false);
				}
			}
		}
		else
		{
			designB->gif->stop();
			UpdateCounter(username);
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
		QSqlQuery query;
		query.prepare("SELECT COUNT (*) FROM Users WHERE Username = ?");
		query.bindValue(0, ui.LEUsername->text());
		bool result = query.exec() == true ? true : false;
		if (result == true)
		{
			query.next();
			int counter = query.value(0).toInt();
			if (counter == 0)
			{
				Utilities::MBAlarm("Typed person is not registered. Please, type proper </i>Username</i>", false);
				return;
			}
		}

		ForgottenPassword *forgottenPassword = new ForgottenPassword(this, ui.LEUsername->text());
		result = forgottenPassword->exec();
		if (result == QDialog::Accepted)
		{
			this->close();
			MainApp *mainApp = new MainApp(nullptr, ui.LEUsername->text());
			mainApp->show();
		}
		delete forgottenPassword;
	}
}
void LogIn::NewProfileClicked()
{
	NewProfile *newProfile = new NewProfile(this);
	newProfile->exec();
	delete newProfile;
}
void LogIn::UpdateAttempts(int loginAttemptCounter, QString username)
{
	QSqlQuery query;
	query.exec("BEGIN IMMEDIATE TRANSACTION");
	query.clear();
	query.prepare("UPDATE Users SET LoginAttemptCounter = ?, LastLoginAttemptDate = ?  WHERE Username = ?");
	query.bindValue(0, loginAttemptCounter);
	query.bindValue(1, Utilities::GetCurrentDateTime());
	query.bindValue(2, username);
	bool result = query.exec() == true ? true : false;
	query.exec("COMMIT");
	if (result == false)
	{
		Utilities::MBAlarm("Something went wrong. Please, try log in again", false);
	}
}
void LogIn::UpdateCounter(QString username)
{
	QSqlQuery query;
	query.clear();
	query.prepare("SELECT LoginAttemptCounter FROM Users WHERE Username = ?");
	query.bindValue(0, username);
	bool result = query.exec() == true ? true : false;
	if (result == true)
	{
		query.next();
		int loginAttemptCounter = query.value(0).toInt();
		loginAttemptCounter += 1;
		if (loginAttemptCounter < loginAttemptCounterMAX)
		{
			UpdateAttempts(loginAttemptCounter, username);
			Utilities::MBAlarm("Typed data is incorrect. Please, try log in again", false);
		}
		else
		{
			loginAttemptCounter = 4;
			int msg = loginTimeLock / 60;
			Utilities::MBAlarm("Your account is blocked. Please, try log in again after " + QString::number(msg) + " minutes", false);
			UpdateAttempts(loginAttemptCounter, username);
		}
	}
	else
	{
		Utilities::MBAlarm("Something went wrong. Please, try log in again", false);
	}
}