#include "ImgProc.h"

ImgProc::ImgProc(int loggedID)
{
	faceCascadeName = faceCascadeFilePath;
	model = cv::createLBPHFaceRecognizer();//cv::createFisherFaceRecognizer();
	loadedFaceCascade = false;
	model->set("threshold", 80.0);
	isModelTrained = false;
	TrainFaceRecognizer();
	this->loggedID = loggedID;
	this->cameraID = -1;
}
ImgProc::ImgProc(const ImgProc &imProc, int cameraID)
{
	this->faceCascadeName= imProc.faceCascadeName;
	this->loadedFaceCascade = false;
	this->LoadFaceCascade();
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
	//https://stackoverflow.com/a/8057236
	QString dirPath = ".\\FaceBase\\";
	QFileInfo filInfo;
	int label = -1;
	QString filename = "";
	QDirIterator iter(dirPath, QStringList() << "*.jpg", QDir::Files | QDir::AllDirs | QDir::NoDot | QDir::NoDotDot, QDirIterator::Subdirectories);
	bool isProperDir = false;
	while (iter.hasNext())
	{
		iter.next();
		filInfo = iter.fileInfo();
		if (filInfo.isDir())
		{
			QRegularExpression qRegExpr("^[1-9][0-9]*$");
			if (filInfo.fileName().contains(qRegExpr))
			{
				label = filInfo.fileName().toInt();
				isProperDir = true;
			}
			else
			{
				isProperDir = false;
			}
		}
		else if (filInfo.isFile() && isProperDir == true)
		{
			filename = iter.filePath();
			if (filename.split('/').count() == 4) //protect against files not in the folder
			{
				if (filInfo.completeSuffix().split('.').count() == 1) //protect against . in filename or extensions .pdf.jpg
				{
					cv::Mat tmpMat = cv::imread(iter.filePath().toStdString(), 0);
					if (tmpMat.rows == 100 & tmpMat.cols == 100) //image dimensions
					{
						images.push_back(tmpMat);
						labels.push_back(label);
					}
				}
			}
		}
	}
}
void ImgProc::TrainFaceRecognizer()
{
	if (Utilities::NotEmptyFileExists(QString(trainedFaceRecognizerFilePath)) == true)
	{
		model->load(trainedFaceRecognizerFilePath);
		isModelTrained = true;
		return;
	}
	FillLabelsAndImagesVectors();
	if (images.size() > 0 && labels.size() > 0)
	{
		model->train(images, labels);
		images.clear();
		labels.clear();
		model->save(trainedFaceRecognizerFilePath);
		isModelTrained = true;
	}
}
bool ImgProc::CheckIfFaceCascadeLoaded()
{
	return loadedFaceCascade;
}
std::vector<cv::Rect> ImgProc::DetectFace(cv::Mat &img)
{
	std::vector<cv::Rect> faces;

	//cv::resize(img_gray, img_gray, cv::Size(380, 213));
	faceCascade.detectMultiScale(img, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(20, 20));
	
	//Coordinates of the top left corner
	//int x = 0;
	//int y = 0;

	//int h = 0; //Height
	//int w = 0; //Width
	//
	/*if (faces.size() == 1)
	{
		//10% https://stackoverflow.com/a/30842913
		cv::Size deltaSize(faces[0].width * 0.1f, faces[0].height * 0.1f); // 0.1f = 10/100
		cv::Point offset(deltaSize.width / 2, deltaSize.height / 2);
		faces[0] += deltaSize;
		faces[0] -= offset;
	}*/

	//	x = faces[0].x/**2*/;
	//	y = faces[0].y/**2*/;
	//	h = faces[0].height/**2*/;
	//	w = faces[0].width/**2*/;
	//	cv::rectangle(img, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(255, 0, 0), 1, 8, 0);
	//}
	return faces;
}
int ImgProc::PredictPerson(cv::Mat matImg)
{
	if (loadedFaceCascade == false)
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
	model->predict(matImg, predictionLabel, predicted_confidence);
	return predictionLabel;
}
bool ImgProc::CheckIfFaceCascadeExists()
{
	QString path = faceCascadeFilePath;
	return Utilities::NotEmptyFileExists(path);
}