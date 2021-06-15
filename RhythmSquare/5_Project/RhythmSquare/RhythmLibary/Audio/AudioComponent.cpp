#include "pchLib.h"
#include "AudioComponent.h"

AudioComponent::AudioComponent()
{
	engine = new RSAudio;
}

AudioComponent::~AudioComponent()
{

}

HRESULT AudioComponent::loadFile(const std::wstring fileName, SoundEvent& soundEvent)
{
	// handle errors
	HRESULT hr = S_OK;

	// load file into wave
	WAVEFORMATEX* waveFormatEx;
	hr = engine->loadFile(fileName, soundEvent.audioData, &waveFormatEx, soundEvent.waveLength);
	if (FAILED(hr))
		return hr;
	soundEvent.waveFormat = *waveFormatEx;

	// create source voice
	hr = engine->GetEngine()->CreateSourceVoice(&soundEvent.sourceVoice, &soundEvent.waveFormat);
	if (FAILED(hr))
		return hr; // "Critical error: Unable to create source voice!"

	ZeroMemory(&soundEvent.audioBuffer, sizeof(XAUDIO2_BUFFER));
	soundEvent.audioBuffer.AudioBytes = (UINT32)soundEvent.audioData.size();
	soundEvent.audioBuffer.pAudioData = (BYTE * const)& soundEvent.audioData[0];
	soundEvent.audioBuffer.pContext = nullptr;

	// return success
	return S_OK;
}

HRESULT AudioComponent::SubmitSourceVoice(const SoundEvent& soundEvent)
{
	// handle errors
	HRESULT hr = S_OK;

	// submit the audio buffer to the source voice
	hr = soundEvent.sourceVoice->SubmitSourceBuffer(&soundEvent.audioBuffer);
	if (FAILED(hr))
		return hr; //"Critical error: Unable to submit source buffer!"

	return S_OK;
}

HRESULT AudioComponent::playSoundEvent(const SoundEvent& soundEvent)
{
	//// handle errors
	//HRESULT hr = S_OK;

	//// submit the audio buffer to the source voice
	//hr = soundEvent.sourceVoice->SubmitSourceBuffer(&soundEvent.audioBuffer);
	//if (FAILED(hr))
	//	return hr; //"Critical error: Unable to submit source buffer!"

	// start the source voice
	soundEvent.sourceVoice->Start();

	// return success
	return S_OK;
}

HRESULT AudioComponent::stopSoundEvent(const SoundEvent& soundEvent)
{
	soundEvent.sourceVoice->Stop();



	// return success
	return S_OK;
}
