#pragma once
#include <map>
#include "Object/ObjectDef.h"

/// 오디오 컴포넌트를 싱글턴으로 사용하기 위한 클래스입니다.
/// 게임 초기화시 함께 초기화를 호출해야 합니다.
class AudioManager : public Singleton<AudioManager>
{
public:
	AudioManager();
	~AudioManager();

public:
	AudioComponent* AudioEngine;

	void Initialize();

	void PlaySound(SoundID id);
	void StopSound(SoundID id);
	void AllSoundStop();
	void SetVolume(unsigned int tag, float vol); // 1 : song  2 : bgm  3 : sfx


private:
	std::map<unsigned int, SoundEvent*> SoundPool;
};

