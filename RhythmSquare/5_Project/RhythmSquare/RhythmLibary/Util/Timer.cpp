#include "pchLib.h"

#include<Windows.h>
#include<iostream>
#include<chrono>
#include<ctime>	
#include "Timer.h"

Timer::Timer()
	:On(false), IsPause(false), Frequency(0), BaseCount(0), StopCount(0), CurrentCount(0), PreCount(0),
	Cycle(0.0), DeltaTime(0.0f)
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	if (On == false)
	{
		__int64 count;
		QueryPerformanceFrequency((LARGE_INTEGER*)&Frequency);
		QueryPerformanceCounter((LARGE_INTEGER*)&count);
		BaseCount = count;
		CurrentCount = BaseCount;
		PreCount = BaseCount;
		Cycle = 1.0 / (double)Frequency;
		On = true;
	}
}

void Timer::Stop()
{
	if (On)
	{
		__int64 count;
		QueryPerformanceCounter((LARGE_INTEGER*)&count);
		StopCount = count;
		On = false;
	}
}

void Timer::Pause()
{
	if (On && IsPause == false)
	{
		__int64 count;
		QueryPerformanceCounter((LARGE_INTEGER*)&count);
		StopCount = count;

		IsPause = true;
	}
}

float Timer::Restart()
{
	__int64 count;
	QueryPerformanceCounter((LARGE_INTEGER*)&count);
	BaseCount = count;
	CurrentCount = BaseCount;

	float PauseTime;
	PauseTime = BaseCount - StopCount / Cycle;
	return PauseTime;
}

void Timer::Reset()
{
	if (On == false)
	{
		__int64 frequency;
		__int64 count;
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
		QueryPerformanceCounter((LARGE_INTEGER*)&count);
		BaseCount = count;
		Cycle = 1.0 / (double)frequency;
		On = true;
	}
}

void Timer::Update()
{
	__int64 count;
	QueryPerformanceCounter((LARGE_INTEGER*)&count);
	CurrentCount = count;
	DeltaTime = (float)((CurrentCount - PreCount) * Cycle);
	PreCount = CurrentCount;
}

float Timer::Now()
{
	return (CurrentCount - BaseCount) * Cycle;
}

float Timer::Delta()
{
	return DeltaTime;
}
