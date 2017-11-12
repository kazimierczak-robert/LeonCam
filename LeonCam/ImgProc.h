#pragma once
#include "opencv2/objdetect.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <qfile.h>
#include <qtextstream.h>
#include <qdiriterator.h>
#include "Utilities.h"

#define trainedFaceRecognizerFilePath "TrainedFaceRecognizer.xml"
#define corpFilePath "corp.csv"
//".\\opencv\\data\\haarcascades\\haarcascade_frontalface_alt.xml"
#define faceCascadeFilePath ".\\opencv\\data\\lbpcascades\\lbpcascade_frontalface.xml"

class ImgProc
{
public:
	ImgProc();
	ImgProc(const ImgProc &imProc);
	~ImgProc();
	std::vector<cv::Rect> DetectFace(cv::Mat &img);
	bool CheckIfFaceCascadeLoaded();
	void LoadFaceCascade();
	void TrainFaceRecognizer();
	cv::CascadeClassifier getFaceCascade() { return faceCascade; }
	bool PredictPerson(cv::Mat matImg);
	bool CheckIfModelTrained() {return isModelTrained;}
	std::vector<cv::Mat> GetImages() { return images; }
	std::vector<int> GetLabels() { return labels; }
	cv::Ptr<cv::FaceRecognizer> GetModel() { return model; }
	void PushBackImage(cv::Mat mat)
	{
		images.push_back(mat);	
	}
	void PushBackLabel(int label)
	{
		labels.push_back(label);
	}
	void ClearImagesVector()
	{
		images.clear();
	}
	void ClearLabelsVector()
	{
		labels.clear();
	}
private:
	int cameraID;
	struct GreenAlert
	{
		int FaceID;
		int CameraID;
		QString StartDate;
		QString StopDate;
		int GreenAlertID;
	};
	struct RedAlert
	{
		QString StartDate;
		QString StopDate;
		int RedAlertID;

	};
	std::vector<GreenAlert> *greenAlertVector;
	std::vector<RedAlert> *redAlertVector;
	bool loadedFaceCascade;
	std::string faceCascadeName="";
	cv::CascadeClassifier faceCascade;
	cv::Ptr<cv::FaceRecognizer> model;
	std::vector<cv::Mat> images;
	std::vector<int> labels;
	bool isModelTrained;
	//std::map <int, QString> peopleBase; //Label, dir name
	void FillLabelsAndImagesVectors();
	//bool ReadCSV(QString filename, std::vector<cv::Mat> &images, std::vector<int> &labels);
};

