#include "stdafx.h"
#include "TimeControler.h"


///QueryPerformanceCounter			// �� �� �ػ� ���� �Լ�
///GetTickCount						// �ػ� ����

DWORD _Game_OpenTime = 0;
DWORD _Game_ElapsedTime = 0;

DWORD _time_OpenTime = 0;
DWORD _time_TotalTime = 0;
float _zzFPS = 0;
int zztick = 0;

DWORD _time_TimeGetTime = 0;
DWORD _time_StartTime = 0;			// (�� ��������) �ð� ����� ������ ����� ����
DWORD _time_EndTime = 0;			// (�� ��������) �ð� ����� ������ ����� ����
DWORD _time_ElapsedTime = 0;		// (�� ��������) ���� �ð�. deltaTime. ������ ms(�и�������)
float _FPS = 0;						// Frame Per Second (1�ʿ� �� ���� �������� �׷����°�?) = 1000 / elasped time
float _FPS_toSet = 0;				// ���õǱ⸦ ���ϴ� FPS
float _time_for_one_frame = 0;

// �ð� ����� �ʱ�ȭ�Ѵ�. ���ϴ� FPS�� �����Ѵ�.
void zzInitializeTime(float FPStoSet)
{
	_FPS_toSet = FPStoSet;

	// �ʱ� �ð��� ���������� ������, ù ��° ������ ������ ���� �� �ִ�.
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