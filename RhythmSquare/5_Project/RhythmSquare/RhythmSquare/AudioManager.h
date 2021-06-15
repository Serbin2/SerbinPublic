#pragma once
#include <map>
#include "Object/ObjectDef.h"

/// ����� ������Ʈ�� �̱������� ����ϱ� ���� Ŭ�����Դϴ�.
/// ���� �ʱ�ȭ�� �Բ� �ʱ�ȭ�� ȣ���ؾ� �մϴ�.
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

