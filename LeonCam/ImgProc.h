#pragma once
#include "opencv2/objdetect.hpp"
/*#include "opencv2/videoio.hpp"*/
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class ImgProc
{
public:
	ImgProc();
	~ImgProc();
	std::vector<cv::Rect> DetectFace(cv::Mat &img);
	bool CheckIfFaceCascadeLoaded();
	void LoadFaceCascade();
private:
	bool loadedFaceCascade = false;
	std::string face_cascade_name="";
	cv::CascadeClassifier face_cascade;

};

