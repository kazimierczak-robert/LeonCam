#include "CameraControl.h"

CameraControl::CameraControl(OnvifClientPTZ *ptz, std::string profileToken)
{
	this->ptz = ptz;
	this->profileToken = profileToken;
}
CameraControl::~CameraControl()
{
}
void CameraControl::MoveCamera(float panSpeed, float tiltSpeed)
{
	if (ptz != nullptr) 
	{
		_tptz__ContinuousMoveResponse res;
		LONG64 timeout = 1;

		tt__PTZSpeed ptzSpeed;
		ptzSpeed.PanTilt = new tt__Vector2D();
		ptzSpeed.PanTilt->x = panSpeed;
		ptzSpeed.PanTilt->y = tiltSpeed;

		ptzSpeed.Zoom = new tt__Vector1D();
		ptzSpeed.Zoom->x = 0.0;

		for (int i = 0; i < MAXCONNECTIONTRIES; i++)
		{
			ptz->ContinuousMove(res, ptzSpeed, timeout, profileToken);
			if (res.soap != nullptr)
			{
				if (res.soap->status == 200)
				{
					break;
				}
			}
		}
		delete ptzSpeed.PanTilt;
		delete ptzSpeed.Zoom;
	}
}
void CameraControl::StopCamera()
{
	if (ptz != nullptr)
	{
		_tptz__StopResponse res;
		for (int i = 0; i < MAXCONNECTIONTRIES; i++)
		{
			ptz->Stop(res, 1, 1, profileToken);
			if (res.soap != nullptr)
			{
				if (res.soap->status == 200)
				{
					break;
				}
			}
		}
	}
}
void CameraControl::GoHomeCamera()
{
	if (ptz != nullptr)
	{
		_tptz__GotoHomePositionResponse res;
		for (int i = 0; i < MAXCONNECTIONTRIES; i++)
		{
			ptz->GoToHomePosition(res, profileToken);
			if (res.soap != nullptr)
			{
				if (res.soap->status == 200)
				{
					break;
				}
			}
		}
	}
}