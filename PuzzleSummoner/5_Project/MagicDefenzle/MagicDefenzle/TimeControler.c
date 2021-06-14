#include "stdafx.h"
#include "TimeControler.h"


///QueryPerformanceCounter			// 좀 더 해상도 높은 함수
///GetTickCount						// 해상도 낮음

DWORD _Game_OpenTime = 0;
DWORD _Game_ElapsedTime = 0;

DWORD _time_OpenTime = 0;
DWORD _time_TotalTime = 0;
float _zzFPS = 0;
int zztick = 0;

DWORD _time_TimeGetTime = 0;
DWORD _time_StartTime = 0;			// (한 프레임의) 시간 기록의 시점을 기록할 변수
DWORD _time_EndTime = 0;			// (한 프레임의) 시간 기록의 끝점을 기록할 변수
DWORD _time_ElapsedTime = 0;		// (한 프레임의) 지난 시간. deltaTime. 단위는 ms(밀리세컨드)
float _FPS = 0;						// Frame Per Second (1초에 몇 개의 프레임이 그려지는가?) = 1000 / elasped time
float _FPS_toSet = 0;				// 셋팅되기를 원하는 FPS
float _time_for_one_frame = 0;

// 시간 모듈을 초기화한다. 원하는 FPS를 지정한다.
void zzInitializeTime(float FPStoSet)
{
	_FPS_toSet = FPStoSet;

	// 초기 시간을 지정해주지 않으면, 첫 번째 루프에 문제가 생길 수 있다.
	_time_TimeGetTime = timeGetTime();
	_time_OpenTime = _time_TimeGetTime;
	_time_for_one_frame = 1000.f / _FPS_toSet;
	zzCheckStartTime();
}

void zzCheckNowTime()
{
	_time_TimeGetTime = timeGetTime();
}

DWORD zzGetCheckedTime()
{
	return _time_TimeGetTime;
}

DWORD zzGetElapsedTime()
{
	return _time_ElapsedTime;
}

float zzGetFPS()
{
	return _FPS;
}

int zzGetTick()
{
	return zztick;
}

float zzGetmyFPS()
{
	return _zzFPS;
}

DWORD zzGetTotalTime()
{
	return _time_TotalTime;
}

void zzCheckStartTime()
{
	_time_StartTime = timeGetTime();
	_time_TotalTime = _time_StartTime - _time_OpenTime;
	zztick++;
	_zzFPS = (float)zztick / (_time_TotalTime / (float)1000);
	if (_time_TotalTime >= 1000.f)
	{
		_time_OpenTime += _time_TotalTime;
		zztick = 0;
	}
}

DWORD zzCheckEndTime()
{
	_time_EndTime = timeGetTime();

	_time_ElapsedTime = _time_EndTime - _time_StartTime;

	_FPS = (float)1000 / (float)_time_ElapsedTime;

	return _time_ElapsedTime;
}

BOOL zzCheckTimeForNextFrame()
{
	

	if (_time_for_one_frame <= (float)_time_ElapsedTime)
	{
		return TRUE;
	}

	return FALSE;
}


void zzGetGameOpenTime()
{
	_Game_OpenTime = timeGetTime();
}

DWORD zzGetGameElapsedTime()
{
	_Game_ElapsedTime = timeGetTime();
	return _Game_ElapsedTime - _Game_OpenTime;
}