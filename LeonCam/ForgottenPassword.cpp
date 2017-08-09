#include "ForgottenPassword.h"

ForgottenPassword::ForgottenPassword(QWidget *parent, QString username)
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
	SetSecurityQuestion(username);
	this->setResult(QDialog::Rejected);
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
	if (ui.LEAnswer->text() == "")
	{
		designB->gif->stop();
		Utilities::MBAlarm("Please, fill in the <i> Answer </i> field", false);
		return;
	}
	else
	{
		SHA256 *sha256 = new SHA256();
		std::string answer = ui.LEAnswer->text().toStdString();
		std::string concatHelp = this->username.toStdString() + answer;
		std::string abbreviation=sha256->sha256_abbreviation(concatHelp);
		delete sha256;
		QSqlQuery query;
		query.prepare("SELECT COUNT (*) FROM Users WHERE Username = ? AND ANSWER = ?");
		query.bindValue(0, username);
		query.bindValue(1, QString::fromStdString(abbreviation));
		bool result = query.exec() == true ? true : false;
		if (result == true)
		{
			query.next();
			int result = query.value(0).toInt();
			if (result == 1)
			{
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
						LogIn::UpdateAttempts(0, username);
						this->done(QDialog::Accepted);
					}
					else
					{
						designB->gif->stop();
						Utilities::MBAlarm("Your account is blocked! Try again after few minutes", false);
					}
				}
			}
			else
			{
				designB->gif->stop();
				LogIn::UpdateCounter(username);
				return;
			}
		}
	}

	designB->gif->stop();
}
void ForgottenPassword::BackClicked()
{
	this->close();
}
