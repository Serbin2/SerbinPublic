#pragma once
#include <iostream>
#include <tchar.h>
#include <chrono>
#include <iomanip>


const int MAX_TIME_STRING_SIZE = 128;


class Clock
{
protected:

	std::chrono::system_clock::time_point		m_StartTime;
	std::chrono::system_clock::time_point		m_EndTime;
	std::chrono::system_clock::time_point		m_StopTime;

	static Clock* instance;

	Clock();
	~Clock();

public:
	static Clock* GetInstance();

	
	// 현재 시스템 시간 리턴
	std::wstring Now(const TCHAR* format = _T("D%Y-%m-%dT%H:%M:%S"));
	std::string Now_Mul(const char* format = "D%Y-%m-%dT%H:%M:%S");
	std::time_t Now_Time_t();

	// 현재시간 - 처음시간 체크
	void CheckTime();

	std::chrono::system_clock::time_point	SystemTick();

	// During Time을 카운트로 컨버팅하여 출력합니다.
	double DuringTime(); // base time
	__int64	Convert_DuringTime_Nano();	// to nano
	__int64 Convert_DuringTime_Micro();	// to micro
	__int64	Convert_DuringTime_Milli();	// to milli
	__int64 Convert_DuringTime_Sec();	// to sec

	int Convert_DuringTime_Min();		// to min
	int Convert_DuringTime_Hour();		// to hour

	// 시계의 시작지점을 설정합니다.
	void Start();

	/// 필요할지 의문이라 빼놨다. 시작과 끝의 포인터만 알면 시간을 조절할 수 있다.
	// 시계의 시작지점을 다시 설정합니다.
	void Reset();
};

