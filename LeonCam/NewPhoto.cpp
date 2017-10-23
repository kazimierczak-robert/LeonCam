#include "NewPhoto.h"

NewPhoto::NewPhoto(std::vector<int> cameraIDs, std::string passHash, QString name, QString surname, int ID, QWidget *parent)
	: QDialog(parent, Qt::WindowSystemMenuHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint)
{
	ui.setupUi(this);
	this->setWindowTitle(name + " " + surname +" (ID: " + (QVariant(ID)).toString() + ") - LeonCam");
	connect(ui.PBBack, SIGNAL(clicked()), this, SLOT(BackButtonClicked()));
	connect(ui.PBFolder, &QPushButton::clicked, this, [this, ID] {Utilities::OpenFileExplorer(ID); });
	//connect(ui.PBFolder, SIGNAL(clicked()), this, SLOT(OpenFileExplorer(ID)));
	//future = QtConcurrent::run([=]() {CameraPreviewUpdate(cameraURIs); }); //run preview from camera
}

NewPhoto::~NewPhoto()
{
}
/*void GetCamerasInfo()
//ip
//login
//haslo
//name*/
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
