#include "UserCamera.h"

UserCamera::UserCamera(QWidget *parent)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	this->setResult(QDialog::Rejected);
	//Create DesignB instance
	designB = new DesignBase(this);
	//Set gif in Lloading label
	designB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBAdd, SIGNAL(clicked()), this, SLOT(AddClicked()));
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackClicked()));
	connect(ui.CBAssign, SIGNAL(stateChanged(int)), this, SLOT(AssignChecked()));
}

UserCamera::~UserCamera()
{
	
}

void UserCamera::DisableIfAssignChanged(bool flag)
{
	ui.LEDescripton->setDisabled(flag);
	ui.LEIPv4Address->setDisabled(flag);
}
void UserCamera::AssignChecked()
{
	if (ui.CBAssign->isChecked())
	{
		//TODO: write values from combobox (it must be map)
		DisableIfAssignChanged(true);
		ui.LTip->setToolTip("");
	}
	else
	{
		DisableIfAssignChanged(false);
		ui.LTip->setToolTip("<html><head/><body><p><span style=\"font-weight:600;\">Model</span> and <span style=\" font-weight:600;\">Description</span> have <span style=\" font-weight:600;\">X</span> letters limits.</p></body></html>");
	}
}
std::vector<QString>*  UserCamera::GetValuesFromControls()
{
	std::vector<QString>* controlsValues = new std::vector<QString>();
	controlsValues->push_back(ui.LEDescripton->text());
	controlsValues->push_back(ui.LEIPv4Address->text());
	controlsValues->push_back(ui.LELogin->text());
	controlsValues->push_back(ui.LEPassword->text());

	return controlsValues;
}
void UserCamera::AddClicked() 
{	
	//TODO
	designB->gif->start();

	if (ui.LEDescripton->text() == "" || ui.LEIPv4Address->text() == "" || ui.LELogin->text() == "" || ui.LEPassword->text() == "")
	{
		designB->gif->stop();
		Utilities::MBAlarm("At least one field is incomplete", false);
		return;
	}

	std::regex IPv4AddressPattern("^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$");
	if (std::regex_match(ui.LEIPv4Address->text().toStdString(), IPv4AddressPattern) == false)
	{
		designB->gif->stop();
		Utilities::MBAlarm("IPv4 address incompatible format", false);
		return;
	}

	designB->gif->stop();
	this->done(QDialog::Accepted);
	//this->setResult(QDialog::Accepted);
	//this->close();
}
void UserCamera::BackClicked() 
{
	this->close();
}