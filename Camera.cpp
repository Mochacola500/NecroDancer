#include "stdafx.h"
#include "Camera.h"

/*********************************
@ 카메라 초기화
**********************************/
void Camera::Init()
{
	// 상태 및 추적 대상
	this->mState = CAMERA_STATE::FREE;
	this->mTarget = nullptr;

	// 시점 위치, 영역 및 속도
	this->mLocation = { 0,0 };
	this->mWindow.RectMakeCenter(mLocation, WINSIZE_X, WINSIZE_Y);
	this->mLocationSpeed = 10.0f;

	// 시점 위치 저장
	this->mLocationSave.reserve(LOCATION_SAVE_MAX);
	this->holdPosition = { 0,0 };
	mLocationSavedCount = 0;
	mMaxShootingLocation = { 5000,5000 };

	// 줌 
	this->mZoom.value = 1.0f;
	this->mZoom.Max = 3.0f;
	this->mZoom.Min = 0.5f;
	this->mZoom.Rate = 0.05f;

	Shake(0, 0);
}

/*********************************
@ 카메라 업데이트
**********************************/
void Camera::Update()
{
	switch (mState)
	{
	case CAMERA_STATE::FREE:
		this->CameraControl();
		break;
	case CAMERA_STATE::TARGETE:
		this->SetLocationFromTarget();
		break;
	}
	this->TransLocationSaved();
	this->Shaking();
	this->FixedCameraLocation();
}

/*********************************
@ 촬영 영역 설정
**********************************/
void Camera::SetShootingLocation(float x, float y)
{
	this->mMaxShootingLocation.x = x;
	this->mMaxShootingLocation.y = y;
}

/*********************************
@ 카메라 위치를 윈도우 안으로 고정
**********************************/
inline void Camera::FixedCameraLocation()
{
	//if (mLocation.x * mZoom.value < 0)
	//{
	//	mLocation.x -= mLocation.x * mZoom.value;
	//}
	//if (mLocation.y * mZoom.value < 0)
	//{
	//	mLocation.y -= mLocation.y * mZoom.value;
	//}
	//if (mLocation.x + WINSIZE_X > mMaxShootingLocation.x)
	//{
	//	mLocation.x -= (mLocation.x + WINSIZE_X) - mMaxShootingLocation.x;
	//}
	//if (mLocation.y + WINSIZE_Y> mMaxShootingLocation.y)
	//{
	//	mLocation.y -= (mLocation.y + WINSIZE_Y) - mMaxShootingLocation.y;
	//}
}

/*********************************
@ 카메라 추적 대상의 위치로 카메라 시점 변경
**********************************/
inline void Camera::SetLocationFromTarget()
{
	this->mLocation.x = mTarget->CameraLocation.x - WINSIZE_X / 2;
	this->mLocation.y = mTarget->CameraLocation.y - WINSIZE_Y / 2;
}

/*********************************
@ 카메라 조작
**********************************/
void Camera::CameraControl()
{
	if (KEY->IsStayKeyDown('W'))
	{
		this->mLocation.y -= mLocationSpeed;
	}
	if (KEY->IsStayKeyDown('S'))
	{
		this->mLocation.y += mLocationSpeed;
	}
	if (KEY->IsStayKeyDown('A'))
	{
		this->mLocation.x -= mLocationSpeed;
	}
	if (KEY->IsStayKeyDown('D'))
	{
		this->mLocation.x += mLocationSpeed;
	}
}
/*********************************
@ 카메라를 저장된 시점으로 이동
**********************************/
void Camera::TransLocationSaved()
{
	
}
/*********************************
@ 카메라 보정된 벡터 반환
**********************************/
Vector2 Camera::CorrecteLocation(Vector2 * lhs)
{
	Vector2 calibrated = (*lhs);
	calibrated -= this->mLocation;
	return calibrated;
}

/*********************************
@ 카메라 보정된 F 렉트 반환
**********************************/
FloatRect Camera::CorrecteLocation(FloatRect * lhs)
{
	FloatRect calibrated = (*lhs);
	calibrated -= this->mLocation;
	return calibrated;
}
Vector2 Camera::CorrecteMouse()
{
	Vector2 calibrated = _ptMouse;
	calibrated += this->mLocation;
	int x =  static_cast<int>(calibrated.x / TILESIZE_X);
	int y =  static_cast<int>(calibrated.y / TILESIZE_Y);
	return Vector2(x,y);
}
void Camera::Shake(float power, float amount)
{
	this->shakePower = power;
	this->shakeTime = amount;
	this->shakeDirectionTop = true;
	shakeCount = 0;
}
void Camera::Shaking()
{
	if (this->shakeTime) {
		if (shakeDirectionTop) {
			if (shakeCount < 4) {
				this->mLocation.x -= (shakePower + shakeCount);
				shakeCount++;
			}
			else {
				shakeCount = 0;
				shakeDirectionTop = false;
				shakeTime--;
			}
		}
		else
		{
			if (shakeCount < 4) {
				this->mLocation.x += (shakePower + shakeCount);
				shakeCount++;
			}
			else {
				shakeCount = 0;
				shakeDirectionTop = false;
				shakeTime--;
			}
		}
	}
}
/*********************************
@ 줌 값 변경
**********************************/
void Camera::InputZoom(short inputZoom)
{
	if (inputZoom > 0)
	{
		if (mZoom.value < mZoom.Max) {
			mZoom.value += mZoom.Rate;
			//mLocation += Vector2(700, 400) * mZoom.Rate;
		}
	}
	else
	{
		if (mZoom.value > mZoom.Min) {
			mZoom.value -= mZoom.Rate;
			//mLocation -= Vector2(700, 400) * mZoom.Rate;
		}
	}
}
