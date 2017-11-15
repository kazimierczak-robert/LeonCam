#pragma once
#include "opencv2/objdetect.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <qfile.h>
#include <qtextstream.h>
#include <qdiriterator.h>
#include "Utilities.h"
#include <qsqlquery.h>
#include <iterator>
#define trainedFaceRecognizerFilePath "TrainedFaceRecognizer.xml"
#define corpFilePath "corp.csv"
//".\\opencv\\data\\haarcascades\\haarcascade_frontalface_alt.xml"
#define faceCascadeFilePath ".\\opencv\\data\\lbpcascades\\lbpcascade_frontalface.xml"

class ImgProc
{
public:
	struct GreenAlert
	{
		int faceID;
		int cameraID;
		QString startDate;
		QString stopDate;
		int greenAlertID;
	};
	struct RedAlert
	{
		QString startDate;
		QString stopDate;
		int redAlertID;
	};
	ImgProc(int loggedID);
	ImgProc(const ImgProc &imProc, int cameraID);
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
	int GetLoggedID() { return loggedID; }
	std::list<GreenAlert> *GetGreenAlertList() { return greenAlertList; }
	RedAlert *GetRedAlert() { return redAlert; }
	void SetRedAlertID(int redAlertID) { redAlert->redAlertID = redAlertID; }
private:
	int cameraID;
	int loggedID;
	bool isModelTrained;
	bool loadedFaceCascade;
	std::string faceCascadeName = "";
	std::list<GreenAlert> *greenAlertList;
	RedAlert *redAlert=nullptr;
	std::vector<cv::Mat> images;
	std::vector<int> labels;
	cv::CascadeClassifier faceCascade;
	cv::Ptr<cv::FaceRecognizer> model;
	//std::map <int, QString> peopleBase; //Label, dir name
	void FillLabelsAndImagesVectors();
	//bool ReadCSV(QString filename, std::vector<cv::Mat> &images, std::vector<int> &labels);
};

