#include "RSAudio.h"
#include <tchar.h>


RSAudio::RSAudio() :
	pXAudio2(NULL), pMasterVoice(NULL), wfx({ 0 }), buffer({ 0 })
{
	Initialize();
}

RSAudio::~RSAudio()
{
	// shut down the media foundation
	MFShutdown();

	// destroy the master voice
	pMasterVoice->DestroyVoice();

	// stop the engine
	pXAudio2->StopEngine();


}


HRESULT RSAudio::Initialize()
{
	HRESULT hr = S_OK;
	
	// initialize media foundation
	hr = MFStartup(MF_VERSION);
	   
	// set media foundation reader to low latency
	hr = MFCreateAttributes(&sourceReaderConfiguration, 1);
	if (FAILED(hr))
		return hr;

	hr = sourceReaderConfiguration->SetUINT32(MF_LOW_LATENCY, true);
	if (FAILED(hr))
		return hr;

	// get an interface to the main XAudio2 device
	hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);

	if (SUCCEEDED(hr))
	{
		hr = pXAudio2->CreateMasteringVoice(&pMasterVoice);
	}


	return hr;
}

HRESULT RSAudio::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}
		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
		{
			hr = HRESULT_FROM_WIN32(GetLastError());
		}
		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
			{
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
			{
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize) return S_FALSE;

	}

	return S_OK;
}

HRESULT RSAudio::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
	{
		hr = HRESULT_FROM_WIN32(GetLastError());
	}
	return hr;
}

HRESULT RSAudio::RIFFtoXAudio2()
{
	HRESULT hr;


	char czStr[] = "../RimEngine/MusicMono.wav";
	TCHAR strFileName[100] = { 0, };
#ifdef _UNICODE
	MultiByteToWideChar(CP_ACP, 0, czStr, -1, strFileName, _countof(strFileName));
#else
	strcpy_s(strFileName, czStr);
#endif

	// Open the file
	HANDLE hFile = CreateFile(
		strFileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);

	if (INVALID_HANDLE_VALUE == hFile)
		return hr = HRESULT_FROM_WIN32(GetLastError());

	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return hr = HRESULT_FROM_WIN32(GetLastError());

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	//check the file type, should be fourccWAVE or 'XWMA'
	FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
	DWORD filetype;
	ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
	if (filetype != fourccWAVE)
		return S_FALSE;


	FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
	ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);

	//fill out the audio data buffer with the contents of the fourccDATA chunk
	FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
	BYTE* pDataBuffer = new BYTE[dwChunkSize];
	ReadChunkData(hFile, pDataBuffer, dwChunkSize, dwChunkPosition);


	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer


	return S_OK;

}

HRESULT RSAudio::PlaySound()
{
	HRESULT hr;


	IXAudio2SourceVoice* pSourceVoice;
	if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)& wfx))) return hr;

	if (FAILED(hr = pSourceVoice->SubmitSourceBuffer(&buffer)))
		return hr;

	if (FAILED(hr = pSourceVoice->Start(0)))
		return hr;

	return hr;
}

HRESULT RSAudio::loadFile(const std::wstring& filename, std::vector<BYTE>& audioData, WAVEFORMATEX** waveFormatEx, unsigned int& waveFormatLength)
{

	audioData.clear();

	// stream index
	DWORD streamIndex = (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM;

	// handle errors
	HRESULT hr = S_OK;

	// create the source reader
	IMFSourceReader* sourceReader;
	hr = MFCreateSourceReaderFromURL(filename.c_str(), sourceReaderConfiguration, &sourceReader);

	// select the first audio stream, and deselect all other streams
	if (SUCCEEDED(hr))
	{
		hr = sourceReader->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, false);
	}

	if (SUCCEEDED(hr))
	{
		hr = sourceReader->SetStreamSelection(streamIndex, true);
	}

	// query information about the media file
	IMFMediaType* nativeMediaType;
	hr = sourceReader->GetNativeMediaType(streamIndex, 0, &nativeMediaType);
	if (FAILED(hr))
		return hr;

	// make sure that this is really an audio file
	GUID majorType{};
	hr = nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType);
	if (majorType != MFMediaType_Audio)
		return S_FALSE; // not an audio file

	// check whether the audio file is compressed or uncompressed
	GUID subType{};
	hr = nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &subType);
	if (subType == MFAudioFormat_Float || subType == MFAudioFormat_PCM)
	{
		// the audio file is uncompressed
	}
	else
	{
		// the audio file is compressed; we have to decompress it first


		IMFMediaType* partialType = nullptr;
		hr = MFCreateMediaType(&partialType);
		if (FAILED(hr))
			return hr;

		// set the media type to "audio"
		hr = partialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		if (FAILED(hr))
			return hr;

		// request uncompressed data
		hr = partialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
		if (FAILED(hr))
			return hr;

		hr = sourceReader->SetCurrentMediaType(streamIndex, NULL, partialType);
		if (FAILED(hr))
			return hr;

	}

	// uncompress the data and load it into an XAudio2 Buffer
	IMFMediaType* uncompressedAudioType = nullptr;
	hr = sourceReader->GetCurrentMediaType(streamIndex, &uncompressedAudioType);
	if (FAILED(hr))
		return hr;

	hr = MFCreateWaveFormatExFromMFMediaType(uncompressedAudioType, waveFormatEx, &waveFormatLength);
	if (FAILED(hr))
		return hr;

	// ensure the stream is selected
	hr = sourceReader->SetStreamSelection(streamIndex, true);
	if (FAILED(hr))
		return hr; //"Critical error: Unable to select audio stream!"

	// copy data into byte vector
	IMFSample* sample = nullptr;
	IMFMediaBuffer* buffer = nullptr;
	BYTE* localAudioData = NULL;
	DWORD localAudioDataLength = 0;

	while (true)
	{
		DWORD flags = 0;
		hr = sourceReader->ReadSample(streamIndex, 0, nullptr, &flags, nullptr, &sample);
		if (FAILED(hr))
			return hr; //"Critical error: Unable to read audio sample!"

		// check whether the data is still valid
		if (flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
			break;

		// check for eof
		if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
			break;

		if (sample == nullptr)
			continue;

		// convert data to contiguous buffer
		hr = sample->ConvertToContiguousBuffer(&buffer);
		if (FAILED(hr))
			return hr; //"Critical error: Unable to convert audio sample to contiguous buffer!"

		// lock buffer and copy data to local memory
		hr = buffer->Lock(&localAudioData, nullptr, &localAudioDataLength);
		if (FAILED(hr))
			return hr; //"Critical error: Unable to lock the audio buffer!"

		for (size_t i = 0; i < localAudioDataLength; i++)
			audioData.push_back(localAudioData[i]);

		// unlock the buffer
		hr = buffer->Unlock();
		localAudioData = nullptr;

		if (FAILED(hr))
			return hr; // "Critical error while unlocking the audio buffer!"
	}

	return hr;
}
