#include "MainAppCamera.h"

MainAppCamera::MainAppCamera(ImgProc *imgProc, int cameraID, QObject *parent)
	: QThread(parent)
{
	this->imgProc = new ImgProc(*imgProc, cameraID);
	this->cameraID = cameraID;

	
}

MainAppCamera::~MainAppCamera()
{


}

void MainAppCamera::SetStreamURI(std::string streamURI) //OK
{
	this->streamURI = streamURI;
}

void MainAppCamera::run()
{
	this->isWorking = true;
	//Image from camera
	if (vcap.open(streamURI)) //OK
	{
		int frameID = -1;
		QTimer greenTimer, redTimer;// , processTimer;
		//conects
		connect(&greenTimer, SIGNAL(timeout()), this, SLOT(UpdateGreenAlerts()), Qt::DirectConnection);
		connect(&redTimer, SIGNAL(timeout()), this, SLOT(UpdateRedAlerts()), Qt::DirectConnection);
		//connect(&processTimer, SIGNAL(timeout()), this, SLOT(Process()), Qt::DirectConnection);
		//set intervals
		greenTimer.setInterval(1*60*1000); //5 minutes
		redTimer.setInterval(1*60*1000); //1 minutes
		//processTimer.setInterval(40);
		//start timers
		greenTimer.start();
		redTimer.start();
		//processTimer.start();

		//start processing frames
		connect(this, SIGNAL(starkWorking()), this, SLOT(Process()), Qt::DirectConnection);
		emit starkWorking();

		exec();

		//stop timers
		greenTimer.stop();
		redTimer.stop();
		//processTimer.stop();
	}
}

void MainAppCamera::StopThread()
{
	this->isWorking = false;
}
void MainAppCamera::ChangeFaceRecoState(bool state)
{
	faceRecognitionState = state;
}

void MainAppCamera::UpdateGreenAlerts()
{
	if (imgProc->GetGreenAlertList()->size() == 0) return;
	QSqlQuery query;
	bool result = false;
	query.exec("BEGIN IMMEDIATE TRANSACTION");
	QString dateTimeNow = Utilities::GetCurrentDateTime();
	int msDifferece = -1;
	QDateTime dTNow;
	QDateTime dtStop;
	//Go through GreenAlertVector
	for (std::list<ImgProc::GreenAlert>::iterator iter = imgProc->GetGreenAlertList()->begin(); iter != imgProc->GetGreenAlertList()->end(); iter++)
	{
		query.prepare("UPDATE GreenAlerts SET StopDate = ? WHERE GreenAlertID = ?");
		query.bindValue(0, iter->stopDate);
		query.bindValue(1, iter->greenAlertID);
		result = query.exec() == true ? true : false;
		if (result == true)
		{
			//TODO
		}
		//Check if 5 minutes has passed
		//Yes: delete from vector
		//DateTime format is"yyyy-MM-dd HH:mm:ss"
		QDateTime dTNow = QDateTime::fromString(dateTimeNow, "yyyy-MM-dd HH:mm:ss");
		QDateTime dtStop = QDateTime::fromString(iter->stopDate, "yyyy-MM-dd HH:mm:ss");
		msDifferece = dtStop.msecsTo(dTNow);
		if (msDifferece > (5 * 60 * 1000))
		{
			iter = imgProc->GetGreenAlertList()->erase(iter);
		}
	}
	query.exec("COMMIT");		
}
void MainAppCamera::UpdateRedAlerts()
{
	if (imgProc->GetRedAlert()->redAlertID < 0) return;
	//TODO: Stop movie
	//update BD
	QSqlQuery query;
	bool result = false;
	query.exec("BEGIN IMMEDIATE TRANSACTION");
	QString dateTimeNow = Utilities::GetCurrentDateTime();

	query.prepare("UPDATE RedAlerts SET StopDate = ? WHERE RedAlertID = ?");
	query.bindValue(0, imgProc->GetRedAlert()->stopDate);
	query.bindValue(1, imgProc->GetRedAlert()->redAlertID);
	result = query.exec() == true ? true : false;

	query.exec("COMMIT");
	//if 1 minute has passed set RedAlert to -1
	int msDifferece = -1;
	QDateTime dTNow = QDateTime::fromString(dateTimeNow, "yyyy-MM-dd HH:mm:ss");
	QDateTime dtStop = QDateTime::fromString(imgProc->GetRedAlert()->stopDate, "yyyy-MM-dd HH:mm:ss");
	msDifferece = dtStop.msecsTo(dTNow);
	if (msDifferece > (1 * 60 * 1000))
	{
		imgProc->SetRedAlertID(-1);
	}
}
void MainAppCamera::Process()
{
	//processTimer.stop();
	int frameID;

	while (isWorking)
	{
		QCoreApplication::processEvents();
		if (vcap.read(img))
		{
			if (faceRecognitionState == true) //OK
			{
				if (imgProc->CheckIfFaceCascadeLoaded() == false)
				{
					Utilities::MBAlarm("CascadeClassifier hasn't been loaded, recognition is disabled", false);
				}
				else
				{
					frameID = vcap.get(CV_CAP_PROP_POS_FRAMES);//current frame number
					if (frameID % 10 == 0 && frameID != 0)
					{
						//Get gray picture 20x20
						std::vector<cv::Rect> faces;
						cv::Mat imgGray;

						cvtColor(img, imgGray, CV_BGR2GRAY);
						cv::equalizeHist(imgGray, imgGray);

						//cv::resize(imgGray, imgGray, cv::Size(380, 213));
						cv::Mat imgCropped;
						//rectangle
						imgProc->getFaceCascade().detectMultiScale(imgGray, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(20, 20));
						for (size_t i = 0; i < faces.size(); i++)
						{
							//Get rect to crop
							cv::Rect myROI(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
							//Crop the full image to that image contained by the rectangle myROI
							imgCropped = imgGray(myROI);
							//cvtColor(imgCropped, imgCropped, CV_BGR2GRAY);
							cv::resize(imgCropped, imgCropped, cv::Size(200, 200), 1.0, 1.0, cv::INTER_CUBIC);
							//save to debug
							//cv::imwrite(".\\x.jpg", imgCropped);
							//Predict person
							imgProc->PredictPerson(imgCropped);
						}
					}
				}

			}

			//Resize oroginal image
			cvtColor(img, img, CV_BGR2RGB);

			cv::resize(img, img, cv::Size(760, 427));
			emit updatePixmap(QPixmap::fromImage(QImage(img.data, 760, 427, img.step, QImage::Format_RGB888)));

			cv::resize(img, img, cv::Size(thumbnailWidth, thumbnailHeight));
			//View on thumbnail
			emit updateThumbnail(QPixmap::fromImage(QImage(img.data, thumbnailWidth, thumbnailHeight, img.step, QImage::Format_RGB888)), cameraID);


		}
	}
}

