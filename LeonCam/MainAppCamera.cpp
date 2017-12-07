#include "MainAppCamera.h"

MainAppCamera::MainAppCamera(ImgProc *imgProc, int cameraID, QObject *parent)
	: QThread(parent)
{
	this->imgProc = new ImgProc(*imgProc, cameraID);
	this->cameraID = cameraID;
	this->greenAlertList = new std::list<GreenAlert>();
	redAlert = new RedAlert();
	redAlert->redAlertID = -1;
	cameraFPS = 25;
	connect(this, SIGNAL(insertGreenAlert(int, int, int, QString)), parent, SLOT(InsertGreenAlert(int, int, int, QString)));
	connect(this, SIGNAL(insertRedAlert(int, int, QString)), parent, SLOT(InsertRedAlert(int, int, QString)));
	connect(this, SIGNAL(updateGreenAlert(int, QString)), parent, SLOT(UpdateGreenAlert(int, QString)));
	connect(this, SIGNAL(updateRedAlert(int, QString)), parent, SLOT(UpdateRedAlert(int, QString)));
}
MainAppCamera::~MainAppCamera()
{
	if (greenAlertList != nullptr)
	{
		delete greenAlertList;
	}
	if (redAlert != nullptr)
	{
		delete redAlert;
	}
}
void MainAppCamera::SetStreamURI(std::string streamURI)
{
	this->streamURI = streamURI;
}
void MainAppCamera::SetSendBigPicture(bool setting)
{
	this->sendBigPicture = setting;
}
void MainAppCamera::SetSendThumbnail(bool setting)
{
	this->sendThumbnail = setting;
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
		//Check if 0.5 minute has passed : 1 * 30 * 1000
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
			QString filePath = ".\\RedAlerts\\" + QString::number(cameraID);
			//Start movie
			Utilities::CreateFolderIfNotExists(filePath);
			filePath = filePath + "\\" + QVariant(query.value(0).toInt()).toString() + ".avi";
			//the last parameter: color or not video
			//CV_FOURCC('M', 'J', 'P', 'G')
			videowriter.open(filePath.toStdString(), CV_FOURCC('X','2','6','4') , (double)cameraFPS/2, cv::Size(640, 360), true);
		}
		else
		{
			dateTimeNow = Utilities::GetCurrentDateTime();
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
			query.exec("COMMIT");
			if (result == true)
			{
				//Get inserted greenAlertID
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
		}
	}
}
void MainAppCamera::run()
{
	isRedAlertStop = false;
	this->isWorking = true;
	greenAlertList->clear();
	redAlert->redAlertID = -1;
	sendThumbnail = true;
	sendBigPicture = false;
	//Image from camera
	if (vcap.open(streamURI))
	{
		int frameID = -1;
		QTimer greenTimer, redTimer;
		//conects
		connect(&greenTimer, SIGNAL(timeout()), this, SLOT(UpdateGreenAlerts()), Qt::DirectConnection);
		connect(&redTimer, SIGNAL(timeout()), this, SLOT(UpdateRedAlerts()), Qt::DirectConnection);
		//set intervals
		greenTimer.setInterval(5*60*1000); //5 minutes
		redTimer.setInterval(1*30*1000); //0.5 minutes

		//start timers
		greenTimer.start();
		redTimer.start();

		//start processing frames
		connect(this, SIGNAL(startWorking()), this, SLOT(Process()), Qt::DirectConnection);
		emit startWorking();

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
					emit updateGreenAlert(iter->greenAlertID, iter->stopDate);
				}
			}
			query.exec("COMMIT");
		}

		//update red alerts
		if (redAlert->redAlertID > 0)
		{
			//Stop movie
			videowriter.release();
			//update BD
			result = false;
			query.exec("BEGIN IMMEDIATE TRANSACTION");
			query.prepare("UPDATE RedAlerts SET StopDate = ? WHERE RedAlertID = ?");
			query.bindValue(0, redAlert->stopDate);
			query.bindValue(1, redAlert->redAlertID);
			result = query.exec();
			query.exec("COMMIT");
			emit updateRedAlert(redAlert->redAlertID, redAlert->stopDate);
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
	for (std::list<GreenAlert>::iterator iter = greenAlertList->begin(); iter != greenAlertList->end();)
	{
		query.prepare("UPDATE GreenAlerts SET StopDate = ? WHERE GreenAlertID = ?");
		query.bindValue(0, iter->stopDate);
		query.bindValue(1, iter->greenAlertID);
		result = query.exec();
		if (result == true)
		{
			emit updateGreenAlert(iter->greenAlertID, iter->stopDate);
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
		else
		{
			iter++;
		}
	}
	query.exec("COMMIT");		
}
void MainAppCamera::UpdateRedAlerts()
{
	if (redAlert->redAlertID < 0) return;

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
	emit updateRedAlert(redAlert->redAlertID, redAlert->stopDate);
	//if 1 minute has passed set RedAlert to -1
	int msDifferece = -1;
	QDateTime dTNow = QDateTime::fromString(dateTimeNow, "yyyy-MM-dd HH:mm:ss");
	QDateTime dtStop = QDateTime::fromString(redAlert->stopDate, "yyyy-MM-dd HH:mm:ss");
	msDifferece = dtStop.msecsTo(dTNow);
	if (msDifferece > (1 * 30 * 1000))
	{
		StopRedAlert();
	}
}
void MainAppCamera::CheckGreenAlertInList(int greenAlertID)
{
	for (std::list<GreenAlert>::iterator it = greenAlertList->begin(); it != greenAlertList->end(); ++it)
	{
		if (it->greenAlertID == greenAlertID)
		{
			it = greenAlertList->erase(it);
			break;
		}
	}
}
void MainAppCamera::CheckRedAlertID(int redAlertID)
{
	if (redAlert != nullptr)
	{
		if (redAlert->redAlertID == redAlertID)
		{
			isRedAlertStop = true;
		}
	}
}
void MainAppCamera::Process()
{
	//Frame number
	int frameID;
	cv::Mat imgGray;
	cv::Mat imgCropped;
	std::vector<cv::Rect> faces;
	QPixmap pixmapWithRedBorder;
	QPainter qPainter;
	QPen pen(Qt::red);
	pen.setWidth(2);
	while (isWorking)
	{
		if (vcap.read(img))
		{
			frameID = vcap.get(CV_CAP_PROP_POS_FRAMES);//current frame number
			if (frameID % 2 == 0)
			{
				cvtColor(img, imgGray, CV_BGR2GRAY);
				cv::equalizeHist(imgGray, imgGray);
				cv::resize(imgGray, imgGray, cv::Size(640, 360));
			}
			if (faceRecognitionState == true) //OK
			{
				if (imgProc->CheckIfFaceCascadeLoaded() == false)
				{
					Utilities::MBAlarm("CascadeClassifier hasn't been loaded, recognition is disabled", false);
				}
				else
				{
					//If move isn't being recorded
					if (frameID % 10 == 0 /*&& videowriter.isOpened()==false*/)
					{
						//Get gray picture 20x20
						faces.clear();
						//cv::resize(imgGray, imgGray, cv::Size(380, 213));
						//rectangle
						
						imgProc->GetFaceCascade().detectMultiScale(imgGray, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));
						for (int i = 0; i < faces.size(); i++)
						{
							//Get rect to crop
							//cv::Rect myROI(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
							//Crop the full image to that image contained by the rectangle myROI
							imgCropped = imgGray(faces[i]);
							//cvtColor(imgCropped, imgCropped, CV_BGR2GRAY);
							cv::resize(imgCropped, imgCropped, cv::Size(100, 100), 1.0, 1.0, cv::INTER_CUBIC);
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
			//Resize original image
			
			if (frameID % 2 == 0 && sendBigPicture)
			{
				emit updateImage(imgGray);
			}

			if (frameID % 2 == 0 && videowriter.isOpened())
			{
				if (isRedAlertStop == true)
				{
					QFile file;
					QString fileName = ".\\RedAlerts\\" + QVariant(cameraID).toString() + "\\" + QVariant(redAlert->redAlertID).toString() + ".avi";
					StopRedAlert();		
					file.remove(fileName);
					isRedAlertStop = false;
				}
				else
				{
					videowriter.write(imgGray);
				}
			}

			if (frameID % 2 == 0 && sendThumbnail)
			{
				cv::resize(imgGray, imgGray, cv::Size(thumbnailWidth, thumbnailHeight));
				pixmapWithRedBorder = QPixmap::fromImage(QImage(imgGray.data, thumbnailWidth, thumbnailHeight, imgGray.step, QImage::Format_Grayscale8));
				//There is an alert add red border
				if (redAlert->redAlertID != -1)
				{
					qPainter.begin(&pixmapWithRedBorder);
					qPainter.setBrush(Qt::NoBrush);
					qPainter.setPen(pen);
					qPainter.drawRect(1, 1, thumbnailWidth - 2, thumbnailHeight - 2);
					qPainter.end();
				}
				//View on thumbnail
				emit updateThumbnail(pixmapWithRedBorder, cameraID);
			}
			if (frameID % 2 == 0)
			{
				QCoreApplication::processEvents();
			}
		}
	}
}
void MainAppCamera::SaveMat()
{
	QString filePath = ".\\PhotoFromCameras\\" + QVariant(cameraID).toString();
	Utilities::CreateFolderIfNotExists(filePath);
	QString fileName= Utilities::GetCurrentDateTime() + ".jpg";
	std::replace(fileName.begin(), fileName.end(), ':', '-');
	filePath = filePath + "\\" + fileName;
	cv::imwrite(filePath.toStdString(), img);
	Utilities::MBAlarm("Picture has been taken", true);
}
void MainAppCamera::StopRedAlert()
{
	redAlert->redAlertID = -1;
	videowriter.release();
}