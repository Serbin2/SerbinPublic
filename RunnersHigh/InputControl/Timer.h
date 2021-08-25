#pragma once

#include <Windows.h>

class Timer
{
public:
	Timer();
	~Timer();


	//타이머를 생성합니다
	void InitializeTimer();
	//타이머의 시간을 리턴합니다
	float TimerTotalTime();
	//이전 프레임에서 이번 프레임까지 걸린 시간을 리턴합니다.
	float TimerDeltaTime();
	//타이머를 리셋합니다.
	void TimerReset();
	//타이머가 정지상태일경우 타이머를 시작한다.
	void TimerStart();
	//타이머를 정지한다 정지상태에서는 아무것도 하지않는다
	void TimerStop();
	//매 게임루프마다 호출해야합니다.
	void TimerTick();
	//현제 타이머의 상태를 리턴합니다.
	bool TimerIsStop() { return mStopped; };

	//프레임계산 역할을 자동으로 해주는 버전
	void calcFPS();


private:
	double mSecondsPerCount; // 성능에 따른 최소 단위시간
	double mDeltaTime;

	long long mBaseTime;
	long long mPausedTime;
	long long mStopTime;
	long long mPrevTime;
	long long mCurrTime;

	bool mStopped;

public:
	//프레임이 시작된 시간
	float startFrameTime;
	//프레임계산을 위한 deltaTime들의 누적시간
	float sumTimer;
	//출력할 수 있는 최대프레임 계산을 위한 카운터
	unsigned int maxFPSCounter;
	//출력할 수 있는 최대프레임
	unsigned int maxFPS;
	//프레임 계산을 위한 카운터
	int frameCount;
	//1프레임에 걸리는 시간
	float frameSecond;
	//Frame Per Second
	int FPS;
	//프레임 계산을 위한 카운터
	int FPSCounter;
};

