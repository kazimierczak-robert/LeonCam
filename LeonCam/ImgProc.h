#pragma once
#include "opencv2/objdetect.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <qfile.h>
#include <qtextstream.h>
#include <qdiriterator.h>
#include "Utilities.h"

#define TrainedFaceRecognizerFilePath "TrainedFaceRecognizer.xml"
#define CorpFilePath "corp.csv"

class ImgProc
{
public:
	ImgProc();
	~ImgProc();
	std::vector<cv::Rect> DetectFace(cv::Mat &img);
	bool CheckIfFaceCascadeLoaded();
	void LoadFaceCascade();
	void TrainFaceRecognizer();
private:
	bool loadedFaceCascade = false;
	std::string face_cascade_name="";
	cv::CascadeClassifier face_cascade;
	cv::Ptr<cv::FaceRecognizer> model;
	std::vector<cv::Mat> images;
	std::vector<int> labels;
	bool isModelTrained;
	std::map <int, QString> peopleBase; //Label, dir name
	bool CreateCSV();
	bool ReadCSV(QString filename, std::vector<cv::Mat> &images, std::vector<int> &labels);
};

