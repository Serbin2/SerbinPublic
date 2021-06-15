#pragma once
#include "RSAudio.h"
#include "SoundEvent.h"

class AudioComponent
{
private:
	// the main audio engine
	RSAudio* engine;				// the main audio engine: XAudio2 with Windows Media Component

	// handle message
	//util::Expected<void> onMessage(const core::Depesche& depesche);
public:
	// constructor and destructor
	AudioComponent();
	~AudioComponent();

	// load files from disk
	HRESULT loadFile(const std::wstring fileName, SoundEvent& soundEvent);
	// ������ �ҷ����� ���� ���� �̺�Ʈ�� ������������ �׻� Ȯ���Ͻʽÿ�.

	HRESULT SubmitSourceVoice(const SoundEvent& soundEvent);

	// play sound
	HRESULT playSoundEvent(const SoundEvent& soundEvent);
	HRESULT stopSoundEvent(const SoundEvent& soundEvent);
};