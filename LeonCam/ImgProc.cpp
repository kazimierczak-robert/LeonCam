#include "ImgProc.h"

ImgProc::ImgProc()
{
	faceCascadeName = faceCascadeFilePath;
	model = cv::createLBPHFaceRecognizer();//cv::createFisherFaceRecognizer();
	loadedFaceCascade = false;
	model->set("threshold", 100.0);
	isModelTrained = false;
	TrainFaceRecognizer();
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
bool ImgProc::CreateCSV()
{
	//<FilePath;label>
	QFile corpFile(QString(corpFilePath));
	if (corpFile.open(QIODevice::WriteOnly))
	{
		//https://stackoverflow.com/a/8057236
		QString dirPath = ".\\FaceBase\\";
		QTextStream stream(&corpFile);
		QFileInfo filInfo;
		int peopleCounter = -1;
		QDirIterator iter(dirPath, QStringList() << "*.jpg", QDir::Files|QDir::AllDirs | QDir::NoDot | QDir::NoDotDot, QDirIterator::Subdirectories );
		while (iter.hasNext())
		{
			iter.next();
			filInfo = iter.fileInfo();
			if (filInfo.isDir())
			{
				peopleCounter++;
				peopleBase[peopleCounter] = filInfo.fileName();
			}
			else if (filInfo.isFile())
			{
				stream << iter.filePath() << ";" << peopleCounter << "\n";
			}
		}
		corpFile.close();
		return true;
	}
	else
	{
		return false;
	}
}
bool ImgProc::ReadCSV(QString filename, std::vector<cv::Mat> &images, std::vector<int> &labels)
{
	CreateCSV();
	QFile file(filename);
	QString readLine = "";
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream stream(&file);
		QStringList csvParts;
		QString path = "";
		QString label = "";
		while (stream.atEnd() == false)
		{
			readLine = stream.readLine();
			csvParts = readLine.split(";");
			path = csvParts.at(0);
			label = csvParts.at(1);
			if (!path.isEmpty() && !label.isEmpty())
			{
				images.push_back(cv::imread(path.toStdString(), 0));
				labels.push_back(atoi(label.toStdString().c_str()));
			}
		}
		file.close();
		return true;
	}
	else
	{
		file.close();
		return false;
	}
}
void ImgProc::TrainFaceRecognizer()
{
	//ReadCSV(QString(CorpFilePath), images, labels);
	bool result = false;
	if (Utilities::NotEmptyFileExists(QString(trainedFaceRecognizerFilePath)) == true)
	{
		result = Utilities::MBQuestion("Do you want to load training data from " + QString(trainedFaceRecognizerFilePath) + " file?");
		if (result == true)
		{
			model->load(trainedFaceRecognizerFilePath);
			CreateCSV();
			isModelTrained = true;
			return;
		}
	}
	CreateCSV();
	ReadCSV(QString(corpFilePath),images, labels);
	if (images.size() == 0 && labels.size() == 0)
	{
		return;
	}
	model->train(images, labels);
	isModelTrained = true;
	result = Utilities::MBQuestion("Do you want to save training data in "+ QString(trainedFaceRecognizerFilePath) +" file?");
	if (result == true)
	{
		model->save(trainedFaceRecognizerFilePath);
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
	
	for (size_t i = 0; i < faces.size(); i++)
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
bool ImgProc::PredictPerson(cv::Mat matImg, int cameraID)
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
	if (predictionLabel < 0)
	{
		int x = 0;
		//Nie rozpoznano osoby
	}
	else
	{
		if (peopleBase.find(predictionLabel) != peopleBase.end())
		{
			int faceID = peopleBase.at(predictionLabel).toInt();
			int camID = cameraID;
			QString dateTime = Utilities::GetCurrentDateTime();
			//TIMER!!!
			//Check if faceID is is in vector
				//Yes
					//Update STOP
				//No
					//Add tuple to BD
					//Add to vecotr
		}
		
		int y = 0;//Rozpoznano osobe peopleBase[predictionLabel]
		
	}
	return true;

}