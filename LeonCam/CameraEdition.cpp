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
	connect(ui.PBBack, &QPushButton::clicked, this, [this]	{this->close();	});
	connect(ui.PBEdit, SIGNAL(clicked()), this, SLOT(EditClicked()));
	this->userID = userID;
	this->camID = camID;
	this->passHash = passHash;

	future = nullptr;
	watcher = nullptr;

	QSqlQuery *query = new QSqlQuery();
	query->prepare("SELECT Name, IPAddress, Login FROM Cameras WHERE CameraID=?");
	query->bindValue(0, camID);
	if (query->exec() == true)
	{
		query->next();
		ui.LEDescripton->setText(query->value(0).toString());
		ui.LEIPv4Address->setText(query->value(1).toString());
		ui.LELogin->setText(query->value(2).toString());
	}
	delete query;
}

CameraEdition::~CameraEdition()
{
	delete designB;
	if (watcher != nullptr)
	{
		watcher->waitForFinished();
	}
	/*if (future != nullptr)
	{
		delete future;
	}
	if (watcher != nullptr)
	{
		delete watcher;
	}*/
}

std::vector<QString>* CameraEdition::GetValuesFromControls()
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
	result = "";
	future = new QFuture<void>();
	watcher = new QFutureWatcher<void>();
	connect(watcher, &QFutureWatcher<void>::finished, this, [this] 
	{
		if (result=="")
		{
			this->done(QDialog::Accepted);
		}
		else
		{
			Utilities::MBAlarm(QString::fromStdString(result), false);
		}
		designB->gif->stop();
	});
	*future = QtConcurrent::run([=]()
	{
		if (ui.LEDescripton->text() == "" || ui.LEIPv4Address->text() == "" || ui.LELogin->text() == "")
		{
			result = "At least one necessary field is incomplete";
			return;
		}

		int passCounter = 0;
		passCounter += ui.LEOldPassword->text() == "" ? 0 : 1;
		passCounter += ui.LEPassword->text() == "" ? 0 : 1;
		passCounter += ui.LEConfPass->text() == "" ? 0 : 1;
		if (passCounter % 3 != 0)
		{
			result = "At least one necessary field in \"Change Password\" is incomplete";
			return;
		}

		std::regex IPv4AddressPattern("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])(:[0-9]{1,5})?$");
		if (std::regex_match(ui.LEIPv4Address->text().toStdString(), IPv4AddressPattern) == false)
		{
			result = "IPv4 address incompatible format";
			return;
		}

		if (ui.LEPassword->text() != ui.LEConfPass->text())
		{
			result = "Passwords are not the same";
			return;
		}

		QSqlQuery query;
		query.prepare("SELECT COUNT (*) FROM Cameras WHERE UserID = ? AND Name = ? AND CameraID != ?");
		query.bindValue(0, userID);
		query.bindValue(1, ui.LEDescripton->text());
		query.bindValue(2, camID);
		if (query.exec() == true)
		{
			query.next();
			int counter = query.value(0).toInt();
			if (counter > 0)
			{
				result = "This name is occupied by your another camera. Please type another one";
				return;
			}
		}

		if (passCounter == 3)
		{
			query.clear();
			query.prepare("SELECT Password FROM Cameras WHERE CameraID = ?");
			query.bindValue(0, camID);
			if (query.exec() == true)
			{
				query.next();
				std::string encryptedMsg = Utilities::GetEncrypted(passHash, ui.LEPassword->text().toStdString());
				if (QString::fromStdString(encryptedMsg) != query.value(0).toString())
				{
					result = "Old password is incorrect";
					return;
				}
			}
		}
	});
	watcher->setFuture(*future);
}