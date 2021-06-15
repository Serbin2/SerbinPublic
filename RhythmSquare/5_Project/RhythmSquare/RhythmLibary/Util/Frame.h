#pragma once
#include <iostream>
#include <string>
#include "../Util/Singleton.h"

class Frame
{
public:
	Frame();
	Frame(float fps);
	~Frame();

	void SetFPS(float fps);	
	bool FreamChecker();
	float Delta();
	int GetFPS() { return FPS; }


protected:
	float DeltaTime;
	float BaseTime;
	// 프레임이 시작된 시간
	float StartFrameTime;
	// 프레임계산을 위한 DeltaTime들의 누적시간
	float SumTimer;
	// 1 프레임에 걸리는 시간
	float FrameSecond;
	// Frame Per Second
	int FPS;
	// 프레임 계산을 위한 카운터
	int FrameCount;
	// 프레임 계산을 위한 카운터
	int FPSCounter;
};


class GameFream : public Frame, public Singleton<GameFream>
{
public:
	GameFream();
	GameFream(float fps);
public:
	void CalcFPS();

private:
	//출력할 수 있는 최대프레임 계산을 위한 카운터
	unsigned int MaxFPSCounter;
	//출력할 수 있는 최대프레임
	unsigned int MaxFPS;
	//출력할 수 있는 최대 FPS를 리턴하는 함수
	int GetMaxFPS();
};