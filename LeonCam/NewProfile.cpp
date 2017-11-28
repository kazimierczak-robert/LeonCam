#include "NewProfile.h"

NewProfile::NewProfile(QWidget *parent)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	//Create DesignB instance
	designB = new DesignBase(this);
	//Set gif in Lloading label
	designB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBCreate, SIGNAL(clicked()), this, SLOT(CreateClicked()));
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackClicked()));
	watcher = nullptr;
}
NewProfile::~NewProfile()
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
void NewProfile::CreateClicked()
{
	//Get values from ui and prepare it
	designB->gif->start();
	QString username = "";
	username = ui.LEUsername->text();
	QString password = "";
	password = ui.LEPassword->text();
	QString confirmedPassword = "";
	confirmedPassword = ui.LEConfPass->text();
	QString securityQuestion = "";
	securityQuestion = ui.LESecQuest->text();
	QString answer = "";
	answer = ui.LEAnswer->text();

	Utilities::resultMsg = "";
	future = new QFuture<void>();
	watcher = new QFutureWatcher<void>();
	connect(watcher, &QFutureWatcher<void>::finished, this, [this]
	{
		if (Utilities::resultMsg == "")
		{
			Utilities::MBAlarm("Account has been created", true);
			this->close();
		}
		else
		{
			ui.LEPassword->setText("");
			ui.LEConfPass->setText("");
			Utilities::MBAlarm(QString::fromStdString(Utilities::resultMsg), false);
		}
		designB->gif->stop();
		Utilities::resultMsg = "";
	});
	*future = QtConcurrent::run([=]()
	{
		if (username == "" || password == "" || confirmedPassword == "" || securityQuestion == "" || answer == "")
		{
			Utilities::resultMsg = "At least one field is incomplete";
			return;
		}
		if (password != confirmedPassword)
		{
			Utilities::resultMsg = "Passwords are not the same";
			return;
		}

		/*Requirements:
		minimum 8 characters
		minimum 1 digit
		minimum 1 capital letter
		minimum lowercase*/
		std::regex passwordPattern("(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])[a-zA-Z0-9]{8,}$");
		if (std::regex_match(password.toStdString(), passwordPattern) == false)
		{
			Utilities::resultMsg = "Password incompatible format";
			return;
		}

		std::string concatHelp = "";
		//password abbreviation -> password + username
		concatHelp = password.toStdString() + username.toStdString();
		QString passwordAbbreviation = QString::fromStdString(Utilities::Sha256HEX(concatHelp));

		//answer abbreviation -> question + answer
		concatHelp = securityQuestion.toStdString() + answer.toStdString();

		QString answerAbbreviation = QString::fromStdString(Utilities::Sha256HEX(concatHelp));

		QString currentDateTimeS = Utilities::GetCurrentDateTime();

		QSqlQuery query;
		query.exec("BEGIN IMMEDIATE TRANSACTION");
		query.prepare("INSERT INTO Users (Username, Password, SecurityQuestion, Answer, RedAlertDeleteSettingID, GreenAlertDeleteSettingID, LastLogoutDate, LastLoginAttemptDate, LoginAttemptCounter, RegistrationDate) "
			"VALUES (:Username, :Password, :SecurityQuestion, :Answer, :RedAlertDeleteSettingID,:GreenAlertDeleteSettingID, :LastLogoutDate, :LastLoginAttemptDate, :LoginAttemptCounter, :RegistrationDate)");
		query.bindValue(":Username", username);
		query.bindValue(":Password", passwordAbbreviation);
		query.bindValue(":SecurityQuestion", securityQuestion);
		query.bindValue(":Answer", answerAbbreviation);
		query.bindValue(":RedAlertDeleteSettingID", 1);
		query.bindValue(":GreenAlertDeleteSettingID", 1);
		query.bindValue(":LastLogoutDate", currentDateTimeS);
		query.bindValue(":LastLoginAttemptDate", currentDateTimeS);
		query.bindValue(":LoginAttemptCounter", 0);
		query.bindValue(":RegistrationDate", currentDateTimeS);
		bool result = query.exec();
		query.exec("COMMIT");

		if (result == true)
		{
			return;
		}
		else
		{
			Utilities::resultMsg = "Account has not been created. Your login is occupied";
		}
	});
	watcher->setFuture(*future);	
}
void NewProfile::BackClicked()
{
	this->close();
}