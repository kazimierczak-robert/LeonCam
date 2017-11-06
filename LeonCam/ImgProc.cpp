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