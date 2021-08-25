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

	
	// ���� �ý��� �ð� ����
	std::wstring Now(const TCHAR* format = _T("D%Y-%m-%dT%H:%M:%S"));
	std::string Now_Mul(const char* format = "D%Y-%m-%dT%H:%M:%S");
	std::time_t Now_Time_t();

	// ����ð� - ó���ð� üũ
	void CheckTime();

	std::chrono::system_clock::time_point	SystemTick();

	// During Time�� ī��Ʈ�� �������Ͽ� ����մϴ�.
	double DuringTime(); // base time
	__int64	Convert_DuringTime_Nano();	// to nano
	__int64 Convert_DuringTime_Micro();	// to micro
	__int64	Convert_DuringTime_Milli();	// to milli
	__int64 Convert_DuringTime_Sec();	// to sec

	int Convert_DuringTime_Min();		// to min
	int Convert_DuringTime_Hour();		// to hour

	// �ð��� ���������� �����մϴ�.
	void Start();

	/// �ʿ����� �ǹ��̶� ������. ���۰� ���� �����͸� �˸� �ð��� ������ �� �ִ�.
	// �ð��� ���������� �ٽ� �����մϴ�.
	void Reset();
};

