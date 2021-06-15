#pragma once
#include <xaudio2.h>
#include <vector>

// sound event class to store data that can't be stored in RIFF files
class SoundEvent
{
public:
	IXAudio2SourceVoice* sourceVoice;	// the XAudio2 source voice
	WAVEFORMATEX waveFormat;			// the format of the audio file
	unsigned int waveLength;			// the length of the wave
	std::vector<BYTE> audioData;		// the audio data
	XAUDIO2_BUFFER audioBuffer;			// the actual buffer with the audio data

	float fallof;						// falloff distance
	unsigned int tag;				// music tag

	unsigned int index;					// the index of the actual sound to play

public:
	SoundEvent();
	SoundEvent(unsigned int tg);
	~SoundEvent();


};

