#include "pchLib.h"

#include<chrono>
#include<ctime>
#include<Windows.h>
#include "TimeUtil.h"
#include "Timer.h"
#include "Frame.h"

Frame::Frame()
	:SumTimer(0.f), FrameCount(0), BaseTime(0), FrameSecond(0.f), FPS(0), FPSCounter(1)
{
	StartFrameTime = Timer::GetInstance().Now();
}

Frame::Frame(float fps)	: SumTimer(0.f), FrameCount(0), FPS(0), FPSCounter(0), BaseTime(0)
{
	StartFrameTime = Timer::GetInstance().Now();
	SetFPS(fps);
}

Frame::~Frame()
{
}


void Frame::SetFPS(float fps)
{
	FrameSecond = 1.f / fps;
}

bool Frame::FreamChecker()
{
	SumTimer += Timer::GetInstance().Delta();
	if (SumTimer > 1.f)
	{
		FPS = FPSCounter;
		SumTimer = 0.f;
		FPSCounter = 1;
	}
	BaseTime = Timer::GetInstance().Now() - StartFrameTime;
	DeltaTime = BaseTime;
	if (BaseTime >= FrameSecond)
	{
		FrameCount++;
		FPSCounter++;
		StartFrameTime = Timer::GetInstance().Now();
		BaseTime = 0;
		return true;
	}
	else
		return false;
}

float Frame::Delta()
{
	return DeltaTime;
}

/// ------------------------------ GameFream -------------------------------- ///

GameFream::GameFream()
{
	StartFrameTime = Timer::GetInstance().Now();
}

GameFream::GameFream(float fps)
	:Frame(fps), MaxFPS(0), MaxFPSCounter(0)
{
}

void GameFream::CalcFPS()
{
	SumTimer += BaseTime;
	if (SumTimer > 1.f)
	{
		MaxFPS = MaxFPSCounter;
		FPS = FPSCounter;
		SumTimer = 0.f;
		FPSCounter = 0;
		MaxFPSCounter = 0;
	}
	MaxFPSCounter++;
}

int GameFream::GetMaxFPS()
{
	return MaxFPS;
}