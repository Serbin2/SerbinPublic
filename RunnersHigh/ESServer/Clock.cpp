#include "Clock.h"

Clock* Clock::instance = nullptr;

Clock::Clock()
{

}

Clock::~Clock()
{

}

Clock* Clock::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Clock;
	}
	return instance;
}

std::wstring Clock::Now(const TCHAR* format)
{
	std::time_t now = std::chrono::system_clock::to_time_t(SystemTick());

	tm _tm;
	localtime_s(&_tm, &now);

	std::wstring result(MAX_TIME_STRING_SIZE, L'\0');
	wcsftime(&result[0], result.size(), format, &_tm);
	return result;
}

std::string Clock::Now_Mul(const char* format)
{
	std::time_t now = std::chrono::system_clock::to_time_t(SystemTick());

	tm _tm;
	localtime_s(&_tm, &now);

	std::string result(MAX_TIME_STRING_SIZE, L'\0');
	std::strftime(&result[0], result.size(), format, &_tm);
	return result;
}

std::time_t Clock::Now_Time_t()
{
	return std::chrono::system_clock::to_time_t(SystemTick());
}

void Clock::CheckTime()
{
	m_EndTime = SystemTick();
}

double Clock::DuringTime()
{
	std::chrono::duration<double> DefaultSec = m_EndTime - m_StartTime;
	return DefaultSec.count();
}

__int64 Clock::Convert_DuringTime_Nano()
{
	std::chrono::nanoseconds nano = std::chrono::duration_cast<std::chrono::nanoseconds>(m_EndTime - m_StartTime);
	return nano.count();
}

__int64 Clock::Convert_DuringTime_Micro()
{
	std::chrono::microseconds micro = std::chrono::duration_cast<std::chrono::microseconds>(m_EndTime - m_StartTime);
	return micro.count();
}

__int64 Clock::Convert_DuringTime_Milli()
{
	std::chrono::milliseconds milli = std::chrono::duration_cast<std::chrono::milliseconds>(m_EndTime - m_StartTime);
	return milli.count();
}

__int64 Clock::Convert_DuringTime_Sec()
{
	std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(m_EndTime - m_StartTime);
	return sec.count();
}

int Clock::Convert_DuringTime_Min()
{
	std::chrono::minutes min = std::chrono::duration_cast<std::chrono::minutes>(m_EndTime - m_StartTime);
	return min.count();
}

int Clock::Convert_DuringTime_Hour()
{
	std::chrono::hours hour = std::chrono::duration_cast<std::chrono::hours>(m_EndTime - m_StartTime);
	return hour.count();
}

std::chrono::system_clock::time_point Clock::SystemTick()
{
	return std::chrono::system_clock::now();
}

void Clock::Start()
{
	m_StartTime = SystemTick();
}

void Clock::Reset()
{
	m_StartTime = SystemTick();
}
