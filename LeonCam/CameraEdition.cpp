#include "CameraEdition.h"

CameraEdition::CameraEdition(QWidget *parent, int userID, int camID, std::string passHash)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	//Create DesignB instance
	designB = new DesignBase(this);
	//Set gif in Lloading label
	designB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackClicked()));
	connect(ui.PBEdit, SIGNAL(clicked()), this, SLOT(EditClicked()));
	this->userID = userID;
	this->camID = camID;
	this->passHash = passHash;

	QSqlQuery query;
	query.prepare("SELECT Name, IPAddress, Login FROM Cameras WHERE CameraID=?");
	query.bindValue(0, camID);
	bool result = query.exec() == true ? true : false;
	if (result == true)
	{
		query.next();
		ui.LEDescripton->setText(query.value(0).toString());
		ui.LEIPv4Address->setText(query.value(1).toString());
		ui.LELogin->setText(query.value(2).toString());
	}
}

CameraEdition::~CameraEdition()
{
}

void CameraEdition::BackClicked()
{
	this->close();
}

std::vector<QString>*  CameraEdition::GetValuesFromControls()
{
	std::vector<QString>* controlsValues = new std::vector<QString>();
	controlsValues->push_back(ui.LEDescripton->text());
	controlsValues->push_back(ui.LEIPv4Address->text());
	controlsValues->push_back(ui.LELogin->text());
	controlsValues->push_back(ui.LEPassword->text());

	return controlsValues;
}

void CameraEdition::EditClicked()
{
	designB->gif->start();

	if (ui.LEDescripton->text() == "" || ui.LEIPv4Address->text() == "" || ui.LELogin->text() == "")
	{
		designB->gif->stop();
		Utilities::MBAlarm("At least one necessary field is incomplete", false);
		return;
	}

	int passCounter = 0;
	passCounter += ui.LEOldPassword->text() == "" ? 0 : 1;
	passCounter += ui.LEPassword->text() == "" ? 0 : 1;
	passCounter += ui.LEConfPass->text() == "" ? 0 : 1;
	if (passCounter % 3 != 0)
	{
		designB->gif->stop();
		Utilities::MBAlarm("At least one necessary field in \"Change Password\" is incomplete", false);
		return;
	}

	std::regex IPv4AddressPattern("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
	if (std::regex_match(ui.LEIPv4Address->text().toStdString(), IPv4AddressPattern) == false)
	{
		designB->gif->stop();
		Utilities::MBAlarm("IPv4 address incompatible format", false);
		return;
	}

	if (ui.LEPassword->text() != ui.LEConfPass->text())
	{
		designB->gif->stop();
		Utilities::MBAlarm("Passwords are not the same", false);
		return;
	}

	QSqlQuery query;
	query.prepare("SELECT COUNT (*) FROM Cameras WHERE UserID = ? AND Name = ? AND CameraID != ?");
	query.bindValue(0, userID);
	query.bindValue(1, ui.LEDescripton->text());
	query.bindValue(2, camID);
	bool result = query.exec() == true ? true : false;
	if (result == true)
	{
		query.next();
		int counter = query.value(0).toInt();
		if (counter > 0)
		{
			designB->gif->stop();
			Utilities::MBAlarm("This name is occupied by your another camera. Please type another one", false);
			return;
		}
	}
	
	if (passCounter == 3)
	{
		query.prepare("SELECT Password FROM Cameras WHERE CameraID = ?");
		query.bindValue(0, camID);
		result = query.exec() == true ? true : false;
		if (result == true)
		{
			query.next();
			std::string encryptedMsg = Utilities::GetEncrypted(passHash, ui.LEPassword->text().toStdString());
			if (QString::fromStdString(encryptedMsg) != query.value(0).toString())
			{
				designB->gif->stop();
				Utilities::MBAlarm("Old password is incorrect", false);
				return;
			}
		}
	}

	designB->gif->stop();
	this->done(QDialog::Accepted);
}