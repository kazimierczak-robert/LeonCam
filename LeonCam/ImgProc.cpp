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
				label = filInfo.fileName().toInt();
				//labels.push_back(label);
				//label = QString(filInfo.fileName()).toInt();
				//peopleBase[label] = filInfo.fileName();
			}
			else if (filInfo.isFile())
			{
				images.push_back(cv::imread(iter.filePath().toStdString(), 0));
				labels.push_back(label);
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
	
	//Coordinates of the top left corner
	int x = 0;
	int y = 0;

	int h = 0; //Height
	int w = 0; //Width
	
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
int ImgProc::PredictPerson(cv::Mat matImg)
{
	cv::VideoCapture vcap;
	cv::Mat image;
	if (CheckIfFaceCascadeLoaded() == false)
	{
		LoadFaceCascade();
		if (loadedFaceCascade == false)
		{
			Utilities::MBAlarm("CascadeClassifier hasn't been loaded, person prediction is disabled", false);
			return -2;
		}
	}
	int predictionLabel = -1;
	double predicted_confidence = 0.0;
	int unrecogizedPeople = 0;
	model->predict(matImg, predictionLabel, predicted_confidence);
	return predictionLabel;
}