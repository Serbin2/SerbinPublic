#include "stdafx.h"
#include "Sound.h"
#include "Logger.h"

BOOL soundOpen(SoundInfo* sound, LPSTR FileName)
{
	DWORD dwReturn;
	MCI_OPEN_PARMS mciOpenParms;

	mciOpenParms.lpstrElementName = FileName;

	dwReturn = mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)(LPVOID)& mciOpenParms);
	if (dwReturn != 0)
	{
#ifdef _LOGGER_H
		logDebugMCIError(dwReturn, "soundOpen()");
#endif // _LOGGER_H
		return FALSE;
	}

	sound->DeviceID = mciOpenParms.wDeviceID;
	sound->isPause = FALSE;
	return TRUE;
}

BOOL soundClose(SoundInfo* sound)
{
	DWORD dwReturn = mciSendCommand(sound->DeviceID, MCI_CLOSE, 0, NULL);
	if (dwReturn != 0)
	{
#ifdef _LOGGER_H
		logDebugMCIError(dwReturn, "soundClose()");
#endif // _LOGGER_H
		return FALSE;
	}
	return TRUE;
}

BOOL soundCloseAll()
{
	DWORD dwReturn = mciSendCommand(MCI_ALL_DEVICE_ID, MCI_CLOSE, MCI_WAIT, NULL);
	if (dwReturn != 0)
	{
#ifdef _LOGGER_H
		logDebugMCIError(dwReturn, "soundCloseAll()");
#endif // _LOGGER_H
		return FALSE;
	}
	return TRUE;
}

BOOL soundPlay(SoundInfo* sound)
{
	DWORD dwReturn;
	MCI_PLAY_PARMS mciPlayParms;
	dwReturn = mciSendCommand(sound->DeviceID, MCI_PLAY, NULL, (DWORD)(LPVOID)& mciPlayParms);
	if (dwReturn != 0)
	{
#ifdef _LOGGER_H
		logDebugMCIError(dwReturn, "soundPlay()");
#endif // _LOGGER_H
		soundClose(sound);
		return FALSE;
	}
	sound->isPause = FALSE;
	return TRUE;
}

BOOL soundPlayLooping(SoundInfo* sound)
{
	DWORD dwReturn;
	MCI_PLAY_PARMS mciPlayParms;
	dwReturn = mciSendCommand(sound->DeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlayParms);
	if (dwReturn != 0)
	{
#ifdef _LOGGER_H
		logDebugMCIError(dwReturn, "soundPlayLooping()");
#endif // _LOGGER_H
		soundClose(sound);
		return FALSE;
	}
	sound->isPause = FALSE;
	return TRUE;
}

BOOL soundPause(SoundInfo* sound)
{
	if (!sound->isPause)
	{
		DWORD dwReturn = mciSendCommand(sound->DeviceID, MCI_PAUSE, NULL, NULL);
		if (dwReturn != 0)
		{
#ifdef _LOGGER_H
			logDebugMCIError(dwReturn, "soundPause()");
#endif // _LOGGER_H
			return FALSE;
		}
		sound->isPause = TRUE;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

BOOL soundResume(SoundInfo* sound)
{
	if (sound->isPause)
	{
		DWORD dwReturn = mciSendCommand(sound->DeviceID, MCI_RESUME, NULL, NULL);
		if (dwReturn != 0)
		{
#ifdef _LOGGER_H
			logDebugMCIError(dwReturn, "soundResume()");
#endif // _LOGGER_H
			return FALSE;
		}
		sound->isPause = FALSE;
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}

DWORD soundGetVolume(SoundInfo* sound)
{
	MCI_STATUS_PARMS mciStatusParams;
	mciStatusParams.dwItem = MCI_DGV_STATUS_VOLUME;
	DWORD dwReturn = mciSendCommand(sound->DeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID)& mciStatusParams);
	if (dwReturn != 0)
	{
#ifdef _LOGGER_H
		logDebugMCIError(dwReturn, "soundGetVolume()");
#endif // _LOGGER_H
		return -1;
	}
	return mciStatusParams.dwReturn;;
}

BOOL soundSetVolume(SoundInfo* sound, DWORD volume)
{
	MCI_DGV_SETAUDIO_PARMS mciDgvSetaudioParams;
	DWORD currectVolume = min(1000, max(0, volume));

	mciDgvSetaudioParams.dwCallback = 0;
	mciDgvSetaudioParams.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciDgvSetaudioParams.dwValue = currectVolume;
	mciDgvSetaudioParams.dwOver = 0;
	mciDgvSetaudioParams.lpstrAlgorithm = NULL;
	mciDgvSetaudioParams.lpstrQuality = NULL;

	DWORD dwReturn = mciSendCommand(sound->DeviceID, MCI_SETAUDIO, MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD)(LPVOID)& mciDgvSetaudioParams);
	if (dwReturn != 0)
	{
#ifdef _LOGGER_H
		logDebugMCIError(dwReturn, "soundSetVolume()");
#endif // _LOGGER_H
		return FALSE;
	}
	return TRUE;
}

BOOL soundSeek(SoundInfo* sound, DWORD seekTo)
{
	DWORD dwReturn;
	MCI_SEEK_PARMS mciSeekParams;
	mciSeekParams.dwTo = seekTo;

	dwReturn = mciSendCommand(sound->DeviceID, MCI_SEEK, MCI_TO, (DWORD)(LPVOID)& mciSeekParams);
	if (dwReturn != 0)
	{
#ifdef _LOGGER_H
		logDebugMCIError(dwReturn, "soundSeek()");
#endif // _LOGGER_H
		soundClose(sound);
		return FALSE;
	}

	sound->isPause = TRUE;
	return TRUE;
}

BOOL soundPlayLoopingWav(SoundInfo* sound)
{
	DWORD dwReturn;
	DWORD length;
	DWORD position;
	MCI_PLAY_PARMS mciPlayParms;
	MCI_STATUS_PARMS mciStatusParams;

	dwReturn = mciSendCommand(sound->DeviceID, MCI_STATUS, MCI_STATUS_LENGTH, (DWORD)(LPVOID)& mciStatusParams);
	if (dwReturn != 0)
	{
#ifdef _LOGGER_H
		logDebugMCIError(dwReturn, "soundPlayLooping()");
#endif // _LOGGER_H
		soundClose(sound);
		return FALSE;
	}
	length = mciStatusParams.dwReturn;

	dwReturn = mciSendCommand(sound->DeviceID, MCI_STATUS, MCI_STATUS_POSITION, (DWORD)(LPVOID)& mciStatusParams);
	if (dwReturn != 0)
	{
#ifdef _LOGGER_H
		logDebugMCIError(dwReturn, "soundPlayLooping()");
#endif // _LOGGER_H
		soundClose(sound);
		return FALSE;
	}
	position = mciStatusParams.dwReturn;

	if (length <= position)
	{
		soundSeek(sound, 0);
	}

	dwReturn = mciSendCommand(sound->DeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)& mciPlayParms);
	if (dwReturn != 0)
	{
#ifdef _LOGGER_H
		logDebugMCIError(dwReturn, "soundPlayLooping()");
#endif // _LOGGER_H
		soundClose(sound);
		return FALSE;
	}
	return TRUE;
}