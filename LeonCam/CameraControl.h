#pragma once
#include "onvifclientptz.hpp"
#define MAXCONNECTIONTRIES 5

class CameraControl
{
public:
	CameraControl(OnvifClientPTZ *ptz, std::string profileToken);
	~CameraControl();
private:
	OnvifClientPTZ *ptz = nullptr;
	std::string profileToken = "";
public:
	void MoveCamera(float panSpeed, float tiltSpeed);
	void StopCamera();
	void GoHomeCamera();
};

