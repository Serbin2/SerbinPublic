#include "pchApp.h"
#include "AudioManager.h"

AudioManager::AudioManager()
{
	SoundPool.clear();
}

AudioManager::~AudioManager()
{
	if (SoundPool.size() > 0)
	{
		std::map<unsigned int, SoundEvent*>::iterator it;
		for (it = SoundPool.begin(); it != SoundPool.end(); it++)
		{
			delete it->second;
		}
	}
	SoundPool.clear();
}

void AudioManager::Initialize()
{
	AudioEngine = new AudioComponent();
	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::INTROSPECT_PRE_WAVE), new SoundEvent(1)));
	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::PLOT_TWIST_PRE_WAVE), new SoundEvent(1)));
	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::PRECISION_STRIKE_PRE_WAVE), new SoundEvent(1)));

	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::PLAYER_ATTACK_FIRE), new SoundEvent(3)));
	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::PLAYER_ATTACK_WATER), new SoundEvent(3)));
	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::PLAYER_ATTACK_GRASS), new SoundEvent(3)));

	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::MONSTER_ATTACK_FIRE), new SoundEvent(3)));
	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::MONSTER_ATTACK_WATER), new SoundEvent(3)));
	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::MONSTER_ATTACK_GRASS), new SoundEvent(3)));

	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::LOBBY_BACKGROUND), new SoundEvent(2)));
	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::START_BACKGROUND), new SoundEvent(2)));

	SoundPool.insert(std::make_pair(static_cast<unsigned int>(SoundID::SFX_BUTTON), new SoundEvent(3)));


	/////////////////////////////////////////////////////////////////////////////////////////////
	AudioEngine->loadFile(L"../Data/SFX/Music_Pre/Highlight_Introspect.wav", *SoundPool.find(static_cast<unsigned int>(SoundID::INTROSPECT_PRE_WAVE))->second);
	AudioEngine->loadFile(L"../Data/SFX/Music_Pre/Highlight_Plot_Twist.wav", *SoundPool.find(static_cast<unsigned int>(SoundID::PLOT_TWIST_PRE_WAVE))->second);
	AudioEngine->loadFile(L"../Data/SFX/Music_Pre/Highlight_Precision_Strike.wav", *SoundPool.find(static_cast<unsigned int>(SoundID::PRECISION_STRIKE_PRE_WAVE))->second);

	AudioEngine->loadFile(L"../Data/SFX/SE/Player_attack_fire.wav", *SoundPool.find(static_cast<unsigned int>(SoundID::PLAYER_ATTACK_FIRE))->second);
	AudioEngine->loadFile(L"../Data/SFX/SE/Player_attack_water.aac", *SoundPool.find(static_cast<unsigned int>(SoundID::PLAYER_ATTACK_WATER))->second);
	AudioEngine->loadFile(L"../Data/SFX/SE/Player_attack_grass.aac", *SoundPool.find(static_cast<unsigned int>(SoundID::PLAYER_ATTACK_GRASS))->second);

	AudioEngine->loadFile(L"../Data/SFX/SE/Monster_attack_slime.aac", *SoundPool.find(static_cast<unsigned int>(SoundID::MONSTER_ATTACK_FIRE))->second);
	AudioEngine->loadFile(L"../Data/SFX/SE/Monster_attack_slime.aac", *SoundPool.find(static_cast<unsigned int>(SoundID::MONSTER_ATTACK_WATER))->second);
	AudioEngine->loadFile(L"../Data/SFX/SE/Monster_attack_slime.aac", *SoundPool.find(static_cast<unsigned int>(SoundID::MONSTER_ATTACK_GRASS))->second);

	AudioEngine->loadFile(L"../Data/SFX/SE/Lobby_bg.mp3", *SoundPool.find(static_cast<unsigned int>(SoundID::LOBBY_BACKGROUND))->second);
	AudioEngine->loadFile(L"../Data/SFX/SE/Start_bg_Mizuki.mp3", *SoundPool.find(static_cast<unsigned int>(SoundID::START_BACKGROUND))->second);

	AudioEngine->loadFile(L"../Data/SFX/SE/Use_Button.wav", *SoundPool.find(static_cast<unsigned int>(SoundID::SFX_BUTTON))->second);







}

void AudioManager::PlaySound(SoundID id)
{
	if (SoundPool.find(static_cast<unsigned int>(id)) == SoundPool.end())
	{
		return;
	}
	else
	{
		SoundEvent* snd = SoundPool.find(static_cast<unsigned int>(id))->second;
		AudioEngine->stopSoundEvent(*snd);
		snd->sourceVoice->FlushSourceBuffers();
		AudioEngine->SubmitSourceVoice(*snd);
		AudioEngine->playSoundEvent(*snd);
	}
}

void AudioManager::StopSound(SoundID id)
{
	if (SoundPool.find(static_cast<unsigned int>(id)) == SoundPool.end())
	{
		return;
	}
	else
	{
		SoundEvent* snd = SoundPool.find(static_cast<unsigned int>(id))->second;
		AudioEngine->stopSoundEvent(*snd);
	}
}

void AudioManager::AllSoundStop()
{
	if (SoundPool.size() > 0)
	{
		std::map<unsigned int, SoundEvent*>::iterator it;
		for (it = SoundPool.begin(); it != SoundPool.end(); it++)
		{
			SoundEvent* pt = it->second;
			it->second->sourceVoice->Stop();
		}
	}
}

void AudioManager::SetVolume(unsigned int tag, float vol)
{
	if (SoundPool.size() > 0)
	{
		std::map<unsigned int, SoundEvent*>::iterator it;
		for (it = SoundPool.begin(); it != SoundPool.end(); it++)
		{
			if (it->second->tag == tag)
			{
				it->second->sourceVoice->SetVolume(vol);
			}
		}
	}
}

