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

	bool _isHardware;				//고성능 타이머를 지원하냐?
	float _timeScale;				//시간 경과량
	float _timeElapsed;				//한프레임당 경과량
	__int64 _curTime;				//현재시간
	__int64 _lastTime;				//마지막시간
	__int64 _periodFrequency;		//시간주기 (1초에 몇번이나 카운트되는지)

	unsigned long _frameRate;		//FPS
	unsigned long _FPSFrameCount;	//FPS 카운트
	float _FPSTimeElapsed;			//FPS 경과량
	float _worldTime;				//전체 경과시간

public:
	void Init();
	void Update(float lockFPS = 60.f);
	void Render();

	//한프레임당 경과시간 가져오기
	float getElapedTime(void) { return _timeElapsed; }
	//전체 경과시간 가져오기
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

