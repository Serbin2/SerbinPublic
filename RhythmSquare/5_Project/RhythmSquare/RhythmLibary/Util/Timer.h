#pragma once
#include "Singleton.h"

class Timer	: public Singleton<Timer>
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	void Pause();
	float Restart();
	void Reset();
	void Update();
	float Now();
	float Delta();

	double Cycle;
	float DeltaTime;

	__int64 Frequency;
	__int64 BaseCount;
	__int64 StopCount;
	__int64 CurrentCount;
	__int64 PreCount;

	bool On;
	bool IsPause;
};
