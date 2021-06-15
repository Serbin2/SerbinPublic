#pragma once
#include <windows.h>
#include <xaudio2.h>
#include <vector>
#include <string>


#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'

// Windows Media Foundation
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid")


class RSAudio
{
public:
	~RSAudio();
	RSAudio();

public:

	HRESULT Initialize();
	HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);

	HRESULT RIFFtoXAudio2();

	HRESULT PlaySound();


	HRESULT loadFile(const std::wstring& filename, std::vector<BYTE>& audioData, WAVEFORMATEX** waveFormatEx, unsigned int& waveFormatLength);	// load audio file from disk

	IXAudio2* GetEngine() { return pXAudio2; };

private:

	IXAudio2* pXAudio2;						// the main XAudio2 engine
	IXAudio2MasteringVoice* pMasterVoice;	// a mastering voice

	IMFAttributes* sourceReaderConfiguration; // Windows Media Foundation Source Reader Configuration



	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

};
