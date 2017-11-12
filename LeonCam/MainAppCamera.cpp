#include "MainAppCamera.h"

MainAppCamera::MainAppCamera(ImgProc *imgProc, int cameraID, QObject *parent)
	: QThread(parent)
{
	this->imgProc = new ImgProc(*imgProc);
	this->cameraID = cameraID;
}

MainAppCamera::~MainAppCamera()
{


}

void MainAppCamera::SetStreamURI(std::string streamURI) //OK
{
	this->streamURI = streamURI;
}

void MainAppCamera::run()
{
	this->isWorking = true;
	cv::VideoCapture vcap;
	//Image from camera
	cv::Mat img;
	if (vcap.open(streamURI)) //OK
	{
		int frameID = -1;
		while (isWorking)
		{
			if (vcap.read(img))
			{
				if (faceRecognitionState == true) //OK
				{
					if (imgProc->CheckIfFaceCascadeLoaded() == false)
					{
						Utilities::MBAlarm("CascadeClassifier hasn't been loaded, recognition is disabled", false);
					}
					else
					{
						frameID = vcap.get(CV_CAP_PROP_POS_FRAMES);//current frame number
						if (frameID % 10 == 0 && frameID != 0)
						{
							//Get gray picture 20x20
							std::vector<cv::Rect> faces;
							cv::Mat imgGray;

							cvtColor(img, imgGray, CV_BGR2GRAY);
							cv::equalizeHist(imgGray, imgGray);

							//cv::resize(imgGray, imgGray, cv::Size(380, 213));
							cv::Mat imgCropped;
							//rectangle
							imgProc->getFaceCascade().detectMultiScale(imgGray, faces, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(20, 20));
							for (size_t i = 0; i < faces.size(); i++)
							{
								//Get rect to crop
								cv::Rect myROI(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
								//Crop the full image to that image contained by the rectangle myROI
								imgCropped = imgGray(myROI);
								//cvtColor(imgCropped, imgCropped, CV_BGR2GRAY);
								cv::resize(imgCropped, imgCropped, cv::Size(200, 200), 1.0, 1.0, cv::INTER_CUBIC);
								//save to debug
								//cv::imwrite(".\\x.jpg", imgCropped);
								//Predict person
								imgProc->PredictPerson(imgCropped);
							}
						}
					}
					
				}
				
				//Resize oroginal image
				cvtColor(img, img, CV_BGR2RGB);
				cv::resize(img, img, cv::Size(thumbnailWidth, thumbnailHeight));
				//View on thumbnail
				emit updateThumbnail(QPixmap::fromImage(QImage(img.data, thumbnailWidth, thumbnailHeight, img.step, QImage::Format_RGB888)), cameraID);
			}
		}
		vcap.release();
		img.release();
	}
}

void MainAppCamera::StopThread()
{
	this->isWorking = false;
}
void MainAppCamera::ChangeFaceRecoState(bool state)
{
	faceRecognitionState = state;
}