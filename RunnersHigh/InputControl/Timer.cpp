#include "Timer.h"

Timer::Timer()
{
	mSecondsPerCount = 0.f;
	mDeltaTime = -1.f;
	mBaseTime = 0;
	mPausedTime = 0;
	mStopTime = 0;
	mPrevTime = 0;
	mCurrTime = 0;
	mStopped = false;	//TRUE�� ��������

	long long countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	mSecondsPerCount = 1.0 / (double)countsPerSec;

	startFrameTime = 0;
	sumTimer = 0;
	maxFPSCounter = 0;
	maxFPS = 0;
	frameCount = 0;
	frameSecond = 0;
	FPS = 0;
	FPSCounter = 0;
}

Timer::~Timer()
{

}

void Timer::InitializeTimer()
{
	long long currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

float Timer::TimerTotalTime()
{
	if (mStopped)
	{
		return (float)(((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
	}
	else
	{
		return (float)(((mCurrTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
	}
}

float Timer::TimerDeltaTime()
{
	return (float)mDeltaTime;
}

void Timer::TimerReset()
{
	long long currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	mBaseTime = currTime;
	mPrevTime = currTime;
	mStopTime = 0;
	mStopped = false;
}

void Timer::TimerStart()
{
	long long startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

	//������ ���� ���̿� �帥�ð��� �����Ѵ�

	if (mStopped)
	{
		//������ �ð��� �����Ѵ�.
		mPausedTime += (startTime - mStopTime);

		mPrevTime = startTime;
		mStopTime = 0;
		mStopped = false;
	}
}

void Timer::TimerStop()
{
	//���������̸� �ƹ��ϵ� ���Ѵ�
	if (!mStopped)
	{
		long long currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		//�����ð��� Ÿ�̸������������� �����ϰ� �÷��׸� �Ҵ�
		mStopTime = currTime;
		mStopped = true;
	}
}

void Timer::TimerTick()
{
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	long long currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	mCurrTime = currTime;

	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;

	mPrevTime = mCurrTime;

	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}
}

void Timer::calcFPS()
{
	TimerTick();
	sumTimer += TimerDeltaTime();
	if (sumTimer >= 1.f)
	{
		maxFPS = maxFPSCounter;
		FPS = FPSCounter;
		sumTimer = 0.f;
		FPSCounter = 0;
		maxFPSCounter = 0;
	}
	maxFPSCounter++;
}
