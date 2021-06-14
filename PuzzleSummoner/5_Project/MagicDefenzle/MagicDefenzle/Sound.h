//#ifndef _SOUND_H
//#define _SOUND_H

#pragma once

//필요한 헤더들
//윈도우 헤더
//Windows MultiMedia 라이브러리
//#pragma comment(lib,"winmm")
//Windows MultiMedia DigitalVideo Command set 헤더
//#include <Digitalv.h>



//사운드 정보를 저장할 구조체
//구조체의 값을 직접 변경하면 안됩니다.
typedef struct _SoundInfo
{
	UINT DeviceID;
	BOOL isPause;
}SoundInfo;

//사운드 파일을 엽니다.
//성공할 경우 TRUE를 리턴합니다.
BOOL soundOpen(SoundInfo* sound, LPSTR FileName);
//사운드 파일을 닫습니다. 
//성공할 경우 TRUE를 리턴합니다.
BOOL soundClose(SoundInfo* sound);
//열려있는 모든 사운드 파일을 닫습니다.
//성공할 경우 TRUE를 리턴합니다.
BOOL soundCloseAll();
//사운드를 재생합니다.
//사운드 재생을 실패하면 FALSE를 리턴합니다.
BOOL soundPlay(SoundInfo* sound);
//사운드를 반복재생합니다.(wav파일은 반복되지 않고 한번만 재생합니다.) 
//사운드 재생을 실패하면 FALSE를 리턴합니다.
BOOL soundPlayLooping(SoundInfo* sound);
//사운드 재생을 일시정지합니다.
//사운드가 재생중이 아닌경우 FALSE를 리턴합니다.
BOOL soundPause(SoundInfo* sound);
//사운드 재생을 재개합니다.
//사운드가 재생중일 경우 FALSE를 리턴합니다.
BOOL soundResume(SoundInfo* sound);
//사운드의 볼륨을 가져옵니다.
//성공할경우 볼륨을 리턴하고 실패하면 -1을 반환합니다.
DWORD soundGetVolume(SoundInfo* sound);
//사운드의 볼륨을 설정합니다. 볼륨은 0 ~ 1000 사이의 값을 가질 수 있습니다.
//볼륨설정에 성공한 경우 TRUE를 리턴합니다.
BOOL soundSetVolume(SoundInfo* sound, DWORD volume);

BOOL soundSeek(SoundInfo* sound, DWORD seekTo);
BOOL soundPlayLoopingWav(SoundInfo* sound);
//#endif // !_SOUND_H