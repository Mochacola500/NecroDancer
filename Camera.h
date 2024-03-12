#pragma once
#ifndef CAMERA_H
#define CAMERA_H
#include "SingletonBase.h"
enum class CAMERA_STATE { FREE, TARGETE, FIXED };

class Camera : public SingletonBase<Camera>
{
private:
    // ī�޶� ���� �� ���� 
    /////////////////////////////////////
						         
	Object* mTarget;              // ī�޶� ���� ���
	CAMERA_STATE mState;          // ī�޶� ����
						         
	Vector2 mLocation;            // ī�޶� ���� ��ġ
	Vector2 holdPosition;         // ���콺�� �ѹ� ������ �� ī�޶� ����
	FloatRect mWindow;            // ī�޶� �Կ� ����
	float mLocationSpeed;         // ī�޶� �̵� �ӵ�
	
	vector<Vector2>mLocationSave; // ī�޶� ���� ����
	int mLocationSavedCount;      // ī�޶� ����� ����
#define LOCATION_SAVE_MAX 4       // �ִ� ���� ���� ���� ����

	/////////////////////////////////////

	// ��
	/////////////////////////////////////
	struct Zoom
	{
		float value;    // �� ���
		float Rate;     // �� ������
		float Max;      // �� �ִ뷮
		float Min;      // �� ������
	} mZoom;
	/////////////////////////////////////

	float shakeTime;
	float shakePower;
	bool shakeDirectionTop;
	int shakeCount;

	// �Կ� ����
	/////////////////////////////////////
	Vector2 mMaxShootingLocation;
	/////////////////////////////////////

public:
	void CameraControl();                // ī�޶� ���� ��ġ �̵�
	void TransLocationSaved();           // ī�޶� ����� ���� ��ġ�� �̵�
	void InputZoom(short inputZoom);     // �� �Է� ����
	inline void FixedCameraLocation();   // ī�޶� ��ġ ����
	inline void SetLocationFromTarget(); // ���� ��� ��ġ�� ����
	

	// ī�޶� ��� ���� �� ��ȯ
	Vector2 CorrecteLocation(Vector2* lhs);
	FloatRect CorrecteLocation(FloatRect* lhs);
	Vector2 CorrecteMouse();

	void Shake(float power, float amount);
	void Shaking();

	// ī�޶� ���� �� ���� ��ȯ
	const Vector2& GetCameraLocation() const { return mLocation; }
	void SetCameraLocation(Vector2 location) { mLocation = location; }
	void SetTarget(Object* object) { mTarget = object; }
	void SetState(CAMERA_STATE state) { mState = state; }
	const FloatRect& GetCameraWindow() const { return mWindow; }

	void Init();
	void Update();

	// ī�޶� ���� ����
	void SetShootingLocation(float x, float y);
	const Zoom& GetZoom() const { return mZoom; }

	// �̱��� �⺻�� ����
	SINGLETON_MAKE(Camera)
};
#endif // !CAMERA_H

