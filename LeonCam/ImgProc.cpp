#include "ImgProc.h"

ImgProc::ImgProc(int loggedID)
{
	faceCascadeName = faceCascadeFilePath;
	model = cv::createLBPHFaceRecognizer();//cv::createFisherFaceRecognizer();
	loadedFaceCascade = false;
	model->set("threshold", 100.0);
	isModelTrained = false;
	TrainFaceRecognizer();
	this->loggedID = loggedID;
	this->cameraID = -1;
}
ImgProc::ImgProc(const ImgProc &imProc, int cameraID)
{
	this->greenAlertList = new std::list<GreenAlert>();
	redAlert = new RedAlert();
	redAlert->redAlertID = -1;
	this->loadedFaceCascade = imProc.loadedFaceCascade;
	this->faceCascadeName= imProc.faceCascadeName;
	this->faceCascade=imProc.faceCascade;
	this->model=imProc.model;
	this->images=imProc.images;
	this->labels=imProc.labels;
	this->isModelTrained=imProc.isModelTrained;
	this->loggedID = imProc.loggedID;
	this->cameraID = cameraID;
	//this->peopleBase=imProc.peopleBase; //Label, dir name
}
ImgProc::~ImgProc()
{
}

void ImgProc::LoadFaceCascade()
{
	if (!faceCascade.load(faceCascadeName))
	{
		loadedFaceCascade = false;
	}
	else
	{
		loadedFaceCascade = true;
	}
}
void ImgProc::FillLabelsAndImagesVectors()
{
	//<FilePath;label>
	//QFile corpFile(QString(corpFilePath));
	//if (corpFile.open(QIODevice::WriteOnly))
	//{
	//	//https://stackoverflow.com/a/8057236
		QString dirPath = ".\\FaceBase\\";
	//	QTextStream stream(&corpFile);
		QFileInfo filInfo;
		int label = -1;
		QDirIterator iter(dirPath, QStringList() << "*.jpg", QDir::Files|QDir::AllDirs | QDir::NoDot | QDir::NoDotDot, QDirIterator::Subdirectories );
		while (iter.hasNext())
		{
			iter.next();
			filInfo = iter.fileInfo();
			if (filInfo.isDir())
			{
				labels.push_back((filInfo.fileName()).toInt());
				//label = QString(filInfo.fileName()).toInt();
				//peopleBase[label] = filInfo.fileName();
			}
			else if (filInfo.isFile())
			{
				images.push_back(cv::imread(iter.filePath().toStdString(), 0));
				//stream << iter.filePath() << ";" << label << "\n";
			}
		}
		//corpFile.close();
	//}
}
//bool ImgProc::ReadCSV(QString filename, std::vector<cv::Mat> &images, std::vector<int> &labels)
//{
//	CreateCSV();
//	QFile file(filename);
//	QString readLine = "";
//	if (file.open(QIODevice::ReadOnly))
//	{
//		QTextStream stream(&file);
//		QStringList csvParts;
//		QString path = "";
//		QString label = "";
//		while (stream.atEnd() == false)
//		{
//			readLine = stream.readLine();
//			csvParts = readLine.split(";");
//			path = csvParts.at(0);
//			label = csvParts.at(1);
//			if (!path.isEmpty() && !label.isEmpty())
//			{
//				images.push_back(cv::imread(path.toStdString(), 0));
//				labels.push_back(atoi(label.toStdString().c_str()));
//			}
//		}
//		file.close();
//		return true;
//	}
//	else
//	{
//		file.close();
//		return false;
//	}
//}
void ImgProc::TrainFaceRecognizer()
{
	//ReadCSV(QString(CorpFilePath), images, labels);
	//bool result = false;
	if (Utilities::NotEmptyFileExists(QString(trainedFaceRecognizerFilePath)) == true)
	{
		//result = Utilities::MBQuestion("Do you want to load training data from " + QString(trainedFaceRecognizerFilePath) + " file?");
		//if (result == true)
		//{
			model->load(trainedFaceRecognizerFilePath);
			isModelTrained = true;
			return;
		//}
	}
	FillLabelsAndImagesVectors();
	if (images.size() > 0 && labels.size() > 0)
	{
		model->train(images, labels);
		images.clear();
		labels.clear();
		isModelTrained = true;
		//result = Utilities::MBQuestion("Do you want to save training data in "+ QString(trainedFaceRecognizerFilePath) +" file?");
		//if (result == true)
		//{
		model->save(trainedFaceRecognizerFilePath);
		//}
	}
}
bool ImgProc::CheckIfFaceCascadeLoaded()
{
	return loadedFaceCascade;
}
std::vector<cv::Rect> ImgProc::DetectFace(cv::Mat &img)
{
	std::vector<cv::Rect> faces;
	cv::Mat img_gray;

	cvtColor(img, img_gray, CV_BGR2GRAY);
	cv::equalizeHist(img_gray, img_gray);
	
	cv::resize(img_gray, img_gray, cv::Size(380, 213));
	faceCascade.detectMultiScale(img_gray, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(20, 20));
	
	int x = 0;
	int y = 0;
	int h = 0;
	int w = 0;
	
	for (int i = 0; i < faces.size(); i++)
	{
		//10% https://stackoverflow.com/a/30842913
		cv::Size deltaSize( faces[i].width * 0.1f, faces[i].height * 0.1f ); // 0.1f = 10/100
		cv::Point offset( deltaSize.width/2, deltaSize.height/2);
		faces[i] += deltaSize;
		faces[i] -= offset;

		x = faces[i].x*2;
		y = faces[i].y*2;
		h = faces[i].height*2;
		w = faces[i].width*2;
		cv::rectangle(img, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(255, 0, 0), 1, 8, 0);
	}
	return faces;
}
bool ImgProc::PredictPerson(cv::Mat matImg)
{
	cv::VideoCapture vcap;
	cv::Mat image;
	if (CheckIfFaceCascadeLoaded() == false)
	{
		LoadFaceCascade();
		if (loadedFaceCascade == false)
		{
			Utilities::MBAlarm("CascadeClassifier hasn't been loaded, person prediction is disabled", false);
			return false;
		}
	}
	int predictionLabel = -1;
	double predicted_confidence = 0.0;
	int unrecogizedPeople = 0;
	model->predict(matImg, predictionLabel, predicted_confidence);
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
			query.bindValue(":UserID", loggedID);
			result = query.exec() == true ? true : false;

			//Get inserted redAlertID
			query.exec("COMMIT");
			query.prepare("SELECT RedAlertID FROM RedAlerts WHERE CameraID = ? AND StartDate = ?");
			query.bindValue(0, cameraID);
			query.bindValue(1, dateTimeNow);
			result = query.exec() == true ? true : false;
			//Add to object
			if (result == true)
			{
				query.next();
				redAlert->redAlertID = query.value(0).toInt();
				redAlert->startDate = dateTimeNow;
				redAlert->stopDate = dateTimeNow;
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
			query.bindValue(":UserID", loggedID);
			result = query.exec() == true ? true : false;
			if (result == true)
			{
				//Get inserted greenAlertID
				query.exec("COMMIT");
				query.prepare("SELECT GreenAlertID FROM GreenAlerts WHERE CameraID = ? AND StartDate = ?");
				query.bindValue(0, cameraID);
				query.bindValue(1, dateTimeNow);
				result = query.exec() == true ? true : false;
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
				}
			}
			else 
			{
				//TODO
			}
		}	
	}
	return true;

}