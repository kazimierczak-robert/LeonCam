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
	watcher = nullptr;
}
LogIn::~LogIn()
{
	if (designB != nullptr)
	{
		delete designB;
	}
	if (watcher != nullptr)
	{
		watcher->waitForFinished();
	}
}
void LogIn::LogInClicked()
{
	ui.PBLogIn->setDisabled(true);
	designB->gif->start();

	QString username = "";
	QString password = "";
	username = ui.LEUsername->text();
	password = ui.LEPassword->text();
	loggedID = -1;
	passHash = "";

	Utilities::resultMsg = "";
	future = new QFuture<void>();
	watcher = new QFutureWatcher<void>();
	connect(watcher, &QFutureWatcher<void>::finished, this, [this]
	{
		if (Utilities::resultMsg == "")
		{
			MainApp *mainApp = new MainApp(nullptr, loggedID, passHash);
			mainApp->show();
			this->close();
		}
		else
		{
			ui.LEPassword->setText("");
			Utilities::MBAlarm(QString::fromStdString(Utilities::resultMsg), false);
		}
		designB->gif->stop();
		ui.PBLogIn->setDisabled(false);
		Utilities::resultMsg = "";
	});
	*future = QtConcurrent::run([=]()
	{
		if (username == "" || password == "")
		{
			Utilities::resultMsg = "At least one field is incomplete";
			return;
		}

		std::string concatHelp = "";
		concatHelp = password.toStdString() + username.toStdString();
		QString passwordHash = QString::fromStdString(Utilities::Sha256HEX(concatHelp));
		passHash = Utilities::Sha256HEX(passwordHash.toStdString() + username.toStdString());

		//Get proper user from DB
		QSqlQuery query;
		query.prepare("SELECT * FROM Users WHERE Username = ? AND Password = ?");
		query.bindValue(0, username);
		query.bindValue(1, passwordHash);
		bool result = query.exec();
		if (result == true)
		{
			query.next();
			int result = query.value(0).toInt();
			if (result > 0)
			{
				//check if account is not locked
				QDateTime currentDateTime = QDateTime::fromString(Utilities::GetCurrentDateTime(), "yyyy-MM-dd HH:mm:ss");
				QDateTime lastLoginAttemptDate = query.value(9).toDateTime();
				int loginAttemptCounter = query.value(10).toInt();
				int secondsDiff = lastLoginAttemptDate.secsTo(currentDateTime);
				if (secondsDiff > loginTimeLock) { loginAttemptCounter = 0; }
				if (loginAttemptCounter < loginAttemptCounterMAX)
				{
					UpdateAttempts(0, username);
					loggedID = query.value(0).toInt();
					return;
				}
				else
				{
					Utilities::resultMsg = "Your account is blocked! Try again after few minutes";
					return;
				}
			}
			else
			{
				UpdateCounter(username);
			}
		}
		else
		{
			Utilities::resultMsg = "Something went wrong. Please, try log in again";
		}
	});
	watcher->setFuture(*future);
}
void LogIn::ForgotPasswordClicked()
{
	if (ui.LEUsername->text() == "")
	{
		QToolTip::showText(ui.PBForgotPassword->mapToGlobal(QPoint(0, 0)), ui.PBForgotPassword->toolTip());
	}
	else
	{
		QSqlQuery query;
		query.prepare("SELECT COUNT (*) FROM Users WHERE Username = ?");
		query.bindValue(0, ui.LEUsername->text());
		bool result = query.exec();
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
			int logID = forgottenPassword->GetLoggedID();
			QString passH = forgottenPassword->GetPassHash();
			this->close();
			MainApp *mainApp = new MainApp(nullptr, logID, passH.toStdString());
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
	query.prepare("UPDATE Users SET LoginAttemptCounter = ?, LastLoginAttemptDate = ?  WHERE Username = ?");
	query.bindValue(0, loginAttemptCounter);
	query.bindValue(1, Utilities::GetCurrentDateTime());
	query.bindValue(2, username);
	bool result = query.exec();
	query.exec("COMMIT");
	if (result == false)
	{
		Utilities::resultMsg = "Something went wrong. Please, try log in again";
	}
}
void LogIn::UpdateCounter(QString username)
{
	QSqlQuery query;
	query.clear();
	query.prepare("SELECT LoginAttemptCounter FROM Users WHERE Username = ?");
	query.bindValue(0, username);
	bool result = query.exec();
	if (result == true)
	{
		query.next();
		int loginAttemptCounter = query.value(0).toInt();
		loginAttemptCounter += 1;
		if (loginAttemptCounter < loginAttemptCounterMAX)
		{
			UpdateAttempts(loginAttemptCounter, username);
			Utilities::resultMsg="Typed data is incorrect. Please, try log in again";
		}
		else
		{
			loginAttemptCounter = 4;
			int msg = loginTimeLock / 60;
			Utilities::resultMsg = "Your account is blocked. Please, try log in again after " + QString::number(msg).toStdString() + " minutes";
			UpdateAttempts(loginAttemptCounter, username);
		}
	}
	else
	{
		Utilities::resultMsg = "Something went wrong. Please, try log in again";
	}
}