#include "stdafx.h"
#include "Timer.h"

#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
void Timer::Init()
{
	mWorldTime = nullptr;
	mDeltaTime = nullptr;
	mFps = nullptr;

	//���� Ÿ�̸� �������� üũ
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		//���� Ÿ�̸Ӹ� �����ϴϱ�
		_isHardware = true;
		//�ʴ� �ð� ���(1�� ��� ī���� �ϳ�)
		_timeScale = 1.0f / _periodFrequency;
		//�ʱ�ȭ ������ �ð��� ������ �ð�����
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
	}
	else
	{
		//���� Ÿ�̸Ӹ� �������� �����ϱ�
		_isHardware = false;
		_timeScale = 1.0f / 1000.0f;
		_lastTime = timeGetTime();
	}

	//������ �ʱ�ȭ
	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0;
}

void Timer::Update(float lockFPS)
{
	if (_isHardware)
	{
		//����ð� ���
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		//���� Ÿ�̸Ӹ� �������� �ʱ⶧���� �׳� time�Լ� ����Ѵ�
		_curTime = timeGetTime();
	}

	//�������� ������ �� ���
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	//������ ��Ű��
	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < (1.0f / lockFPS))
		{
			if (_isHardware)
			{
				//����ð� ���
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			}
			else
			{
				//���� Ÿ�̸Ӹ� �������� �ʱ⶧���� �׳� time�Լ� ����Ѵ�
				_curTime = timeGetTime();
			}
			//�������� ������ �� ���
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	//���� �ð� ����
	_lastTime = _curTime;
	//������ �� ����
	_FPSTimeElapsed += _timeElapsed;
	//������ �ð� ����
	_worldTime += _timeElapsed;

	//������ �ʱ�ȭ�� 1�ʸ��� �����ϱ�
	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}

	_FPSFrameCount++;
}

void Timer::Render()
{
	//// ���̾ƿ� ����
	//D2DRENDER->LayOutMake(&mWorldTime, L"WorldTime : " + to_wstring(this->_worldTime), 18.f);
	//D2DRENDER->LayOutMake(&mDeltaTime, L"DeltaTime : " + to_wstring(this->_timeElapsed), 18.f);
	//D2DRENDER->LayOutMake(&mFps, L"FPS : " + to_wstring(this->_frameRate), 18.f);
	//
	//D2DRENDER->RenderText(Vector2(5, 20), mWorldTime, ColorF::White);
	//D2DRENDER->RenderText(Vector2(5, 40), mDeltaTime, ColorF::White);
	//D2DRENDER->RenderText(Vector2(5, 60), mFps, ColorF::White);
}

Timer::Timer()
{
	this->Init();
}

Timer::~Timer()
{
	SAFE_RELEASE(mWorldTime);
	SAFE_RELEASE(mDeltaTime);
	SAFE_RELEASE(mFps);
}
