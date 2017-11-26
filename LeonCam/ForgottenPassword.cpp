#include "ForgottenPassword.h"

ForgottenPassword::ForgottenPassword(QWidget *parent, QString username)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
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
	bool result = query.exec();
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
		std::string answer = ui.LEAnswer->text().toStdString();
		std::string concatHelp = ui.LESecurityQuestion->text().toStdString() + answer;

		QSqlQuery query;
		query.prepare("SELECT * FROM Users WHERE Username = ? AND ANSWER = ?");
		query.bindValue(0, username);
		QString answerHash = QString::fromStdString(Utilities::Sha256HEX(concatHelp));
		query.bindValue(1, answerHash);
		bool result = query.exec();
		if (result == true)
		{
			query.next();
			int result = query.value(0).toInt();
			if (result > 0)
			{			
				QDateTime currentDateTime = QDateTime::fromString(Utilities::GetCurrentDateTime(), "yyyy-MM-dd HH:mm:ss");
				QDateTime lastLoginAttemptDate = query.value(8).toDateTime();
				int loginAttemptCounter = query.value(9).toInt();
				int secondsDiff = lastLoginAttemptDate.secsTo(currentDateTime);
				if (secondsDiff > loginTimeLock) { loginAttemptCounter = 0; }
				if (loginAttemptCounter < loginAttemptCounterMAX)
				{
					LogIn::UpdateAttempts(0, username);
					loggedID = query.value(0).toInt();
					/*Requirements:
					minimum 8 characters
					minimum 1 digit
					minimum 1 capital letter
					minimum lowercase*/
					//8 letters
					std::map<int, char> passwordMap;
					srand(time(NULL));
					//capital letter and position
					int positionPrev = rand() % 8;
					int positionNext;
					passwordMap.insert(std::pair<int, char>(positionPrev, rand() % 26 + 65));
					do
					{
						positionNext = rand() % 8;
					} while (positionPrev == positionNext);
					//digits and position
					passwordMap.insert(std::pair<int, char>(positionNext, rand() % 10 + 48));
					QString passwordFromMap = "";
					for (int i = 0; i < 8; i++)
					{
						if (i == positionNext || i == positionPrev)
						{
							passwordFromMap += passwordMap.at(i);
							continue;
						}
						//letter and position
						passwordMap.insert(std::pair<int, char>(i, rand() % 26 + 97));
						passwordFromMap += passwordMap.at(i);
					}

					//Get password hash from DB
					query.clear();
					query.prepare("SELECT Password FROM Users WHERE UserID = ?");
					query.bindValue(0, loggedID);
					bool result = query.exec();
					if (result == true)
					{
						query.next();
						QString oldPasswordHash = query.value(0).toString();
						passHash = QString::fromStdString(Utilities::Sha256HEX(oldPasswordHash.toStdString() + username.toStdString()));

							query.clear();
							int camID = 0;
							std::string cameraPassword = "";
							result = true;
							query.prepare("SELECT CameraID, Password FROM Cameras WHERE UserID = ?");
							query.bindValue(0, loggedID);
							result = query.exec();
							if (result == true) 
							{
								QSqlQuery queryUpdate;
								std::string encMsg;
								queryUpdate.exec("BEGIN IMMEDIATE TRANSACTION");
								std::string newHashPass = Utilities::Sha256HEX(Utilities::Sha256HEX(passwordFromMap.toStdString() + username.toStdString()) + QString(username).toStdString());
								while (query.next())
								{
									camID = query.value(0).toInt();
									encMsg = query.value(1).toString().toStdString();
									//Decrypt camera password
									cameraPassword = Utilities::GetDecrypted(passHash.toStdString(), encMsg);
									//Encrypt new camera password
									cameraPassword = Utilities::GetEncrypted(newHashPass, cameraPassword);
									//Update password
									queryUpdate.prepare("UPDATE Cameras SET Password = ?  WHERE UserID = ?");
									queryUpdate.bindValue(0, QString::fromStdString(cameraPassword));
									queryUpdate.bindValue(1, loggedID);
									result == result && queryUpdate.exec();
								}
								queryUpdate.exec("COMMIT");
								if (result == true)
								{
									query.clear();
									//Update Password
									query.exec("BEGIN IMMEDIATE TRANSACTION");
									query.prepare("UPDATE Users SET Password = ?  WHERE UserID = ?");
									query.bindValue(0, QString::fromStdString(Utilities::Sha256HEX(passwordFromMap.toStdString() + username.toStdString())));
									query.bindValue(1, loggedID);
									bool result = query.exec();
									query.exec("COMMIT");
									if (result == false)
									{
										Utilities::MBAlarm("Acount error has occured. Please log in again", false);
									}
									else
									{
										passHash = QString::fromStdString(newHashPass);
										Utilities::ChangePasswordBox("You should copy the password to the clipboard, then go to the Settings tab and change it!", passwordFromMap);
										this->done(QDialog::Accepted);
									}
								}
							}
						}
					}
				}
				else
				{
					designB->gif->stop();
					Utilities::MBAlarm("Your account is blocked! Try again after few minutes", false);
				}
			}
			else
			{
				designB->gif->stop();
				LogIn::UpdateCounter(username);
				return;
			}
		}
	designB->gif->stop();
}
void ForgottenPassword::BackClicked()
{
	this->close();
}
