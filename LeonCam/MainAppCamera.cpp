#include "MainAppCamera.h"

MainAppCamera::MainAppCamera(ImgProc *imgProc, int cameraID, QObject *parent)
	: QThread(parent)
{
	this->imgProc = new ImgProc(*imgProc, cameraID);
	this->cameraID = cameraID;
	this->greenAlertList = new std::list<GreenAlert>();
	redAlert = new RedAlert();
	redAlert->redAlertID = -1;
	connect(this, SIGNAL(insertGreenAlert(int, int, int, QString)), parent, SLOT(InsertGreenAlert(int, int, int, QString)));
	connect(this, SIGNAL(insertRedAlert(int, int, QString)), parent, SLOT(InsertRedAlert(int, int, QString)));
}

MainAppCamera::~MainAppCamera()
{


}

void MainAppCamera::SetStreamURI(std::string streamURI) //OK
{
	this->streamURI = streamURI;
}

void MainAppCamera::SetSendBigPicture(bool setting)
{
	this->sendBigPicture = setting;
}
void MainAppCamera::UpdateDBAfterPrediction(int predictionLabel)
{
	QString dateTimeNow;
	QSqlQuery query;
	bool result = false;
	/*	 RED SECTION	*/
	if (predictionLabel < 0)
	{
		//Person hasn't been recognized
		//Check if 1 minute has passed : 1 * 60 * 1000
		result = redAlert->redAlertID < 0 ? true : false;
		//YES
		if (result == true)
		{
			dateTimeNow = Utilities::GetCurrentDateTime();
			query.exec("BEGIN IMMEDIATE TRANSACTION");
			query.prepare("INSERT INTO RedAlerts (CameraID, StartDate, StopDate, UserID) "
				"VALUES (:CameraID, :StartDate, :StopDate, :UserID)");
			query.bindValue(":CameraID", cameraID);
			query.bindValue(":StartDate", dateTimeNow);
			query.bindValue(":StopDate", dateTimeNow);
			query.bindValue(":UserID", imgProc->GetLoggedID());
			result = query.exec();

			//Get inserted redAlertID
			query.exec("COMMIT");
			query.prepare("SELECT RedAlertID FROM RedAlerts WHERE CameraID = ? AND StartDate = ?");
			query.bindValue(0, cameraID);
			query.bindValue(1, dateTimeNow);
			result = query.exec();
			//Add to object
			if (result == true)
			{
				query.next();
				redAlert->redAlertID = query.value(0).toInt();
				redAlert->startDate = dateTimeNow;
				redAlert->stopDate = dateTimeNow;
				emit insertRedAlert(query.value(0).toInt(), cameraID, dateTimeNow);
			}
			//TODO: start movie
		}
		else
		{
			dateTimeNow = Utilities::GetCurrentDateTime();
			//NO
			//Update stopDate in redAlert object
			redAlert->stopDate = dateTimeNow;
		}
	}
	/*	 GREEN SECTION	*/
	else //Person has been recognized
	{
		int faceID = predictionLabel;
		int camID = cameraID;
		bool contains = false;
		for (std::list<GreenAlert>::iterator iter = greenAlertList->begin(); iter != greenAlertList->end(); iter++)
		{
			if (iter->faceID == faceID)
			{
				contains = true;
				dateTimeNow = Utilities::GetCurrentDateTime();
				//Update stopDate in greenAlertVector
				iter->stopDate = dateTimeNow;
				break;
			}
		}
		if (contains == false)
		{
			dateTimeNow = Utilities::GetCurrentDateTime();

			//Add tuple to BD
			query.exec("BEGIN IMMEDIATE TRANSACTION");
			query.prepare("INSERT INTO GreenAlerts (FaceID, CameraID, StartDate, StopDate, UserID) "
				"VALUES (:FaceID, :CameraID, :StartDate, :StopDate, :UserID)");
			query.bindValue(":FaceID", faceID);
			query.bindValue(":CameraID", cameraID);
			query.bindValue(":StartDate", dateTimeNow);
			query.bindValue(":StopDate", dateTimeNow);
			query.bindValue(":UserID", imgProc->GetLoggedID());
			result = query.exec();
			if (result == true)
			{
				//Get inserted greenAlertID
				query.exec("COMMIT");
				query.prepare("SELECT GreenAlertID FROM GreenAlerts WHERE CameraID = ? AND StartDate = ?");
				query.bindValue(0, cameraID);
				query.bindValue(1, dateTimeNow);
				result = query.exec();
				if (result == true)
				{
					query.next();
					//Add to greenAlertVector vector
					struct GreenAlert greenAlert;
					greenAlert.faceID = faceID;
					greenAlert.cameraID = cameraID;
					greenAlert.greenAlertID = query.value(0).toInt();
					greenAlert.startDate = dateTimeNow;
					greenAlert.stopDate = dateTimeNow;
					greenAlertList->push_back(greenAlert);
					emit insertGreenAlert(query.value(0).toInt(), faceID, cameraID, dateTimeNow);
				}
			}
			else
			{
				//TODO
			}
		}
	}
}
void MainAppCamera::run()
{
	this->isWorking = true;

	sendBigPicture = false;
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

		while (isWorking);

		QSqlQuery query;
		bool result = false;
		//update green alerts
		if (greenAlertList->size() > 0)
		{
			query.exec("BEGIN IMMEDIATE TRANSACTION");
			//Go through GreenAlertVector
			for (std::list<GreenAlert>::iterator iter = greenAlertList->begin(); iter != greenAlertList->end(); iter++)
			{
				query.prepare("UPDATE GreenAlerts SET StopDate = ? WHERE GreenAlertID = ?");
				query.bindValue(0, iter->stopDate);
				query.bindValue(1, iter->greenAlertID);
				result = query.exec();
				if (result == true)
				{
					//TODO
				}
			}
			query.exec("COMMIT");
		}

		//update red alerts
		if (redAlert->redAlertID > 0)
		{
			//TODO: Stop movie
			//update BD
			result = false;
			query.exec("BEGIN IMMEDIATE TRANSACTION");
			query.prepare("UPDATE RedAlerts SET StopDate = ? WHERE RedAlertID = ?");
			query.bindValue(0, redAlert->stopDate);
			query.bindValue(1, redAlert->redAlertID);
			result = query.exec();
			query.exec("COMMIT");
		}
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
	if (greenAlertList->size() == 0) return;
	QSqlQuery query;
	bool result = false;
	query.exec("BEGIN IMMEDIATE TRANSACTION");
	QString dateTimeNow = Utilities::GetCurrentDateTime();
	int msDifferece = -1;
	QDateTime dTNow;
	QDateTime dtStop;
	//Go through GreenAlertVector
	for (std::list<GreenAlert>::iterator iter = greenAlertList->begin(); iter != greenAlertList->end(); iter++)
	{
		query.prepare("UPDATE GreenAlerts SET StopDate = ? WHERE GreenAlertID = ?");
		query.bindValue(0, iter->stopDate);
		query.bindValue(1, iter->greenAlertID);
		result = query.exec();
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
			iter = greenAlertList->erase(iter);
		}
	}
	query.exec("COMMIT");		
}
void MainAppCamera::UpdateRedAlerts()
{
	if (redAlert->redAlertID < 0) return;
	//TODO: Stop movie
	//update BD
	QSqlQuery query;
	bool result = false;
	query.exec("BEGIN IMMEDIATE TRANSACTION");
	QString dateTimeNow = Utilities::GetCurrentDateTime();

	query.prepare("UPDATE RedAlerts SET StopDate = ? WHERE RedAlertID = ?");
	query.bindValue(0, redAlert->stopDate);
	query.bindValue(1, redAlert->redAlertID);
	result = query.exec();

	query.exec("COMMIT");
	//if 1 minute has passed set RedAlert to -1
	int msDifferece = -1;
	QDateTime dTNow = QDateTime::fromString(dateTimeNow, "yyyy-MM-dd HH:mm:ss");
	QDateTime dtStop = QDateTime::fromString(redAlert->stopDate, "yyyy-MM-dd HH:mm:ss");
	msDifferece = dtStop.msecsTo(dTNow);
	if (msDifferece > (1 * 60 * 1000))
	{
		redAlert->redAlertID = -1;
	}
}
void MainAppCamera::Process()
{
	//Frame number
	int frameID;

	while (isWorking)
	{
		QCoreApplication::processEvents();
		if (vcap.read(img))
		{
			frameID = vcap.get(CV_CAP_PROP_POS_FRAMES);//current frame number
			if (faceRecognitionState == true) //OK
			{
				if (imgProc->CheckIfFaceCascadeLoaded() == false)
				{
					Utilities::MBAlarm("CascadeClassifier hasn't been loaded, recognition is disabled", false);
				}
				else
				{
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
						for (int i = 0; i < faces.size(); i++)
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
							int predictionLabel = imgProc->PredictPerson(imgCropped);
							if (predictionLabel > -2)
							{
								UpdateDBAfterPrediction(predictionLabel);
							}
						}
					}
				}

			}

			//Resize oroginal image
			cvtColor(img, img, CV_BGR2RGB);

			if (frameID % 2 == 0 && sendBigPicture)
			{
				cv::resize(img, img, cv::Size(760, 427));
				emit updatePixmap(QPixmap::fromImage(QImage(img.data, 760, 427, img.step, QImage::Format_RGB888)));
			}

			cv::resize(img, img, cv::Size(thumbnailWidth, thumbnailHeight));
			//View on thumbnail
			emit updateThumbnail(QPixmap::fromImage(QImage(img.data, thumbnailWidth, thumbnailHeight, img.step, QImage::Format_RGB888)), cameraID);
		}
	}
}

