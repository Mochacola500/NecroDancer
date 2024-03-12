#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "SingletonBase.h"
enum class CAMERA_STATE { FREE, TARGETE, FIXED };

class Camera : public SingletonBase<Camera>
{
private:
    // 카메라 시점 및 상태 
    /////////////////////////////////////
						         
	Object* mTarget;              // 카메라 추적 대상
	CAMERA_STATE mState;          // 카메라 상태
						         
	Vector2 mLocation;            // 카메라 시점 위치
	Vector2 holdPosition;         // 마우스가 한번 눌렀을 때 카메라 시점
	FloatRect mWindow;            // 카메라 촬영 영역
	float mLocationSpeed;         // 카메라 이동 속도
	
	vector<Vector2>mLocationSave; // 카메라 시점 저장
	int mLocationSavedCount;      // 카메라 저장된 개수
#define LOCATION_SAVE_MAX 4       // 최대 저장 가능 시점 개수

	/////////////////////////////////////

	// 줌
	/////////////////////////////////////
	struct Zoom
	{
		float value;    // 줌 상수
		float Rate;     // 줌 변위량
		float Max;      // 줌 최대량
		float Min;      // 줌 최저량
	} mZoom;
	/////////////////////////////////////

	float shakeTime;
	float shakePower;
	bool shakeDirectionTop;
	int shakeCount;

	// 촬영 영역
	/////////////////////////////////////
	Vector2 mMaxShootingLocation;
	/////////////////////////////////////

public:
	void CameraControl();                // 카메라 시점 위치 이동
	void TransLocationSaved();           // 카메라를 저장된 시점 위치로 이동
	void InputZoom(short inputZoom);     // 휠 입력 받음
	inline void FixedCameraLocation();   // 카메라 위치 조정
	inline void SetLocationFromTarget(); // 추적 대상 위치로 변경
	

	// 카메라 대상 보정 값 반환
	Vector2 CorrecteLocation(Vector2* lhs);
	FloatRect CorrecteLocation(FloatRect* lhs);
	Vector2 CorrecteMouse();

	void Shake(float power, float amount);
	void Shaking();

	// 카메라 시점 및 영역 반환
	const Vector2& GetCameraLocation() const { return mLocation; }
	void SetCameraLocation(Vector2 location) { mLocation = location; }
	void SetTarget(Object* object) { mTarget = object; }
	void SetState(CAMERA_STATE state) { mState = state; }
	const FloatRect& GetCameraWindow() const { return mWindow; }

	void Init();
	void Update();

	// 카메라 영역 변경
	void SetShootingLocation(float x, float y);
	const Zoom& GetZoom() const { return mZoom; }

	// 싱글톤 기본형 정의
	SINGLETON_MAKE(Camera)
};
#endif // !CAMERA_H

