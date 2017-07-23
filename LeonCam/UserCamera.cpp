#include "UserCamera.h"

UserCamera::UserCamera(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	//Create DesignB instance
	DesignB = new DesignBase(this);
	//Set gif in Lloading label
	DesignB->SetGifInLabel(ui.Lloading);
	//Signals and slots
	connect(ui.PBVerify, SIGNAL(clicked()), this, SLOT(VerifyClicked()));
	connect(ui.PBDefine, SIGNAL(clicked()), this, SLOT(DefineClicked()));
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackClicked()));
	connect(ui.CBAssign, SIGNAL(stateChanged(int)), this, SLOT(AssignChecked()));
}

UserCamera::~UserCamera()
{
	
}

void UserCamera::DisableIfAssignChanged(bool flag)
{
	ui.LEModel->setDisabled(flag);
	ui.LEDescripton->setDisabled(flag);
	ui.LEIPv4Address->setDisabled(flag);
}
void UserCamera::AssignChecked()
{
	if (ui.CBAssign->isChecked())
	{
		DisableIfAssignChanged(true);
		ui.LTip->setToolTip("");
	}
	else
	{
		DisableIfAssignChanged(false);
		ui.LTip->setToolTip("<html><head/><body><p><span style=\"font-weight:600;\">Model</span> and <span style=\" font-weight:600;\">Description</span> have <span style=\" font-weight:600;\">X</span> letters limits.</p></body></html>");
	}
}
void UserCamera::VerifyClicked() 
{
	//operations
	DesignB->gif->start();
}
void UserCamera::DefineClicked() 
{
	//operations
	this->close();
}
void UserCamera::BackClicked() 
{
	this->close();
}