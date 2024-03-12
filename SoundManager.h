#pragma once

#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H
#include "singletonBase.h"
// 최대 사운드 버퍼 수
#define SOUNDBUFFER 30
class SoundManager : public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**> arrSound;
	typedef map<string, Sound**>::iterator arrSoundIter;

	System* _system;		
	Sound** _sound;			
	Channel** _channel;		

	arrSound _mTotalSound;	

public:
	void Init();
	void Release();
	void Update();

	// 사운드 추가
	void AddSound(string keyName, string soundName, bool bgm = false, bool loop = false);

	// 사운드 실행 처리
	void Play(string keyName, float volume = 1.0f);
	void Stop(string keyName);
	void Pause(string keyName);
	void Resume(string keyName);

	// 상태 확인
	bool IsPlaySound(string keyName);
	bool IsPauseSound(string keyName);


private:
	friend class SingletonBase<SoundManager>;
	SoundManager();
	~SoundManager();
public:
	SoundManager(const SoundManager&) = delete;
	const SoundManager& operator=(const SoundManager&) = delete;

};
#endif // !SOUND_MANAGER_H

