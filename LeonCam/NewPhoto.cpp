#include "NewPhoto.h"

NewPhoto::NewPhoto(std::vector<int> cameraIDs, std::string passHash, QString name, QString surname, int loggedID, QWidget *parent)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	this->setWindowTitle(name + " " + surname +" (ID: " + (QVariant(loggedID)).toString() + ") - LeonCam");
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
	connect(ui.PBFolder, &QPushButton::clicked, this, [this, loggedID] {Utilities::OpenFileExplorer(loggedID); });
	GetCamerasInfo(loggedID, cameraIDs);
	FillCBWithCamerasToCB();
	//connect(ui.PBFolder, SIGNAL(clicked()), this, SLOT(OpenFileExplorer(ID)));
	//future = QtConcurrent::run([=]() {CameraPreviewUpdate(cameraURIs); }); //run preview from camera
	connect(ui.CBPresets, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
		[=](int index) {CurrentIndexChanged(); });
	CurrentIndexChanged();
}

NewPhoto::~NewPhoto()
{
}

void NewPhoto::BackButtonClicked()
{
	this->close();
}
void NewPhoto::CameraPreviewUpdate(std::string streamURI)
{
	//QThread::currentThread()->setPriority(QThread::Priority::HighestPriority);
	cv::VideoCapture vcap;
	cv::Mat img;
	if (vcap.open(streamURI))
	{
		while (true)
		{
			if (vcap.read(img))
			{
				cvtColor(img, img, CV_BGR2RGB);
				ui.LPreviewScreen->setPixmap(QPixmap::fromImage(QImage(img.data, 760, 427, img.step, QImage::Format_RGB888)));
			}
		}
	}
}
void NewPhoto::GetCamerasInfo(int loggedID, std::vector<int> cameraIDs)
{
	//Get Cameras where UserID equals loggedID
	QSqlQuery query;
	query.prepare("SELECT CameraID, Name, IPAddress, Login, Password FROM Cameras WHERE UserID=?");
	query.bindValue(0, loggedID);
	bool result = query.exec() == true ? true : false;
	if (result == true)
	{
		while (query.next())
		{
			//https://stackoverflow.com/a/3450906
			//if cameraIDs contains
			if (std::find(cameraIDs.begin(), cameraIDs.end(), query.value(0).toInt()) != cameraIDs.end())
			{
				//fill camerasToCB
				camerasToCB.insert(std::pair<int, std::string>(query.value(0).toInt(), query.value(1).toString().toStdString()));
				//fill cameras
				struct Camera *cam = new struct Camera;
				cam->CameraID = query.value(0).toInt();
				cam->Name = query.value(1).toString().toStdString();
				cam->IPAddress = query.value(2).toString().toStdString();
				cam->Login = query.value(3).toString().toStdString();
				cam->Password = query.value(4).toString().toStdString();

				cameras.insert(std::pair<int, struct Camera*>(query.value(0).toInt(), cam));
			}
		}
	}
}
void NewPhoto::FillCBWithCamerasToCB()
{
	for (std::pair<int, std::string> elem : camerasToCB)
	{
		ui.CBPresets->addItem(QString::fromStdString(elem.second), elem.first);
	}

}
void NewPhoto::CurrentIndexChanged()
{
	//Utilities::MBAlarm(ui.CBPresets->currentData().toString(), true);
}