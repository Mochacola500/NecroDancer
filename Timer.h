#pragma once
#ifndef TIMER_H
#define TIMER_H
#include "SingletonBase.h"
class Timer : public SingletonBase <Timer>
{
private:
	IDWriteTextLayout* mWorldTime;
	IDWriteTextLayout* mDeltaTime;
	IDWriteTextLayout* mFps;

	bool _isHardware;				//���� Ÿ�̸Ӹ� �����ϳ�?
	float _timeScale;				//�ð� �����
	float _timeElapsed;				//�������Ӵ� �����
	__int64 _curTime;				//����ð�
	__int64 _lastTime;				//�������ð�
	__int64 _periodFrequency;		//�ð��ֱ� (1�ʿ� ����̳� ī��Ʈ�Ǵ���)

	unsigned long _frameRate;		//FPS
	unsigned long _FPSFrameCount;	//FPS ī��Ʈ
	float _FPSTimeElapsed;			//FPS �����
	float _worldTime;				//��ü ����ð�

public:
	void Init();
	void Update(float lockFPS = 60.f);
	void Render();

	//�������Ӵ� ����ð� ��������
	float getElapedTime(void) { return _timeElapsed; }
	//��ü ����ð� ��������
	float getWorldTime(void) { return _worldTime; }

private:
	friend class SingletonBase <Timer>;
	Timer();
	~Timer();
public:
	Timer(const Timer&) = delete;
	const Timer& operator=(const Timer&) = delete;
};
#endif // !TIME_H

