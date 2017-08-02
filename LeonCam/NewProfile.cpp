#include "NewProfile.h"


NewProfile::NewProfile(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//Create DesignB instance
	designB = new DesignBase(this);
	//Set gif in Lloading label
	designB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBCreate, SIGNAL(clicked()), this, SLOT(CreateClicked()));
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackClicked()));
}

NewProfile::~NewProfile()
{
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

	if (username == "" || password == "" || confirmedPassword == "" || securityQuestion == "" || answer == "")
	{
		designB->gif->stop();
		Utilities::MBAlarm("At least one field is incomplete", false);
		return;
	}
	if (password != confirmedPassword)
	{
		designB->gif->stop();
		Utilities::MBAlarm("Passwords are not the same", false);
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
		designB->gif->stop();
		Utilities::MBAlarm("Password incompatible format", false);
		ui.LEPassword->setText("");
		ui.LEConfPass->setText("");

		return;
	}

	//https://stackoverflow.com/a/10599161
	SHA256 *sha256 = new SHA256();
	std::string concatHelp = "";
	//password abbreviation
	concatHelp = password.toStdString() + username.toStdString();
	BYTE *passAbbrev = sha256->sha256_abbreviation(concatHelp);
	char passAbbrevC[65];
	passAbbrevC[64] = 0;
	for (size_t i = 0; i < 32; i++)
	{
		sprintf(&passAbbrevC[2 * i], "%02X", passAbbrev[i]);
	}
	QString passwordAbbreviation = QString::fromUtf8(passAbbrevC);
	//answer abbreviation
	concatHelp = username.toStdString() + answer.toStdString();
	BYTE *answerAbbrev = sha256->sha256_abbreviation(concatHelp);
	char answerAbbrevC[65];
	answerAbbrevC[64] = 0;
	for (size_t i = 0; i < 32; i++)
	{
		sprintf(&answerAbbrevC[2 * i], "%02X", answerAbbrev[i]);
	}
	QString answerAbbreviation = QString::fromUtf8(answerAbbrevC);
	delete sha256;

	//get system current time
	QDateTime currentDateTime = QDateTime::currentDateTime();
	QString currentDateTimeS = currentDateTime.toString("yyyy-MM-dd HH:mm:ss");

	QSqlQuery query;
	query.prepare("INSERT INTO Users (Username, Password, KeepMeLoggedIn, SecurityQuestion, Answer, RedAlertDeleteSettingID,GreenAlertDeleteSettingID, LastLogoutDate, RegistrationDate) "
		"VALUES (:Username, :Password, :KeepMeLoggedIn, :SecurityQuestion, :Answer, :RedAlertDeleteSettingID,:GreenAlertDeleteSettingID,:LastLogoutDate, :RegistrationDate)");
	query.bindValue(":Username", username);
	query.bindValue(":Password", passwordAbbreviation);
	query.bindValue(":KeepMeLoggedIn", 0);
	query.bindValue(":SecurityQuestion", securityQuestion);
	query.bindValue(":Answer", answerAbbreviation);
	query.bindValue(":RedAlertDeleteSettingID", 1);
	query.bindValue(":GreenAlertDeleteSettingID", 1);
	query.bindValue(":LastLogoutDate", currentDateTimeS);
	query.bindValue(":RegistrationDate", currentDateTimeS);
	bool result = query.exec() == true ? true : false;

	designB->gif->stop();
	if (result == true)
	{
		Utilities::MBAlarm("Account has been created", true);
		this->close();
	}
	else
	{
		Utilities::MBAlarm("Account has not been created", false);
	}
}
void NewProfile::BackClicked()
{
	this->close();
}