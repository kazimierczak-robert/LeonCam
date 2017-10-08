#include "NewPhoto.h"

NewPhoto::NewPhoto(QString name, QString surname, int ID, QWidget *parent)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	this->setWindowTitle(name + " " + surname +" (ID: " + (QVariant(ID)).toString() + ") - LeonCam");
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
	connect(ui.PBFolder, &QPushButton::clicked, this, [this, ID] {Utilities::OpenFileExplorer(ID); });
	//connect(ui.PBFolder, SIGNAL(clicked()), this, SLOT(OpenFileExplorer(ID)));
}

NewPhoto::~NewPhoto()
{
}
void NewPhoto::BackButtonClicked()
{
	this->close();
}