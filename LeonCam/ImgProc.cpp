#include "ImgProc.h"

ImgProc::ImgProc()
{
	//face_cascade_name = ".\\opencv\\data\\haarcascades\\haarcascade_frontalface_alt.xml";
	face_cascade_name = ".\\opencv\\data\\lbpcascades\\lbpcascade_frontalface.xml";
}
ImgProc::~ImgProc()
{
}

void ImgProc::LoadFaceCascade()
{
	if (!face_cascade.load(face_cascade_name))
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
	QFile corpFile(QString(CorpFilePath));
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
	//bool result = false;
	//if (Utilities::NotEmptyFileExists(TrainedFaceRecognizerPathFile) == true)
	//{
	//	result = Utilities::MBQuestion("Do you want to load training data from " + QString(TrainedFaceRecognizerPathFile) + " file?");
	//	if (result == true)
	//	{
	//		model->load(TrainedFaceRecognizerPathFile);
	//		CreateCSV();
	//		isModelTrained = true;
	//		return;
	//	}
	//}
	//CreateCSV();
	//Read_csv("corp.csv", images, labels);
	//model->train(images, labels);
	//isModelTrained = true;
	//result = Utilities::MBQuestion("Do you want to save training data in "+ QString(TrainedFaceRecognizerPathFile) +" file?");
	//if (result == true)
	//{
	//	model->save(TrainedFaceRecognizerPathFile);
	//}
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
	face_cascade.detectMultiScale(img_gray, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(20, 20));
	
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