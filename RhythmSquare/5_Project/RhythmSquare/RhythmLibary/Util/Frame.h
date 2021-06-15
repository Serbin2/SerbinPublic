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
	// �������� ���۵� �ð�
	float StartFrameTime;
	// �����Ӱ���� ���� DeltaTime���� �����ð�
	float SumTimer;
	// 1 �����ӿ� �ɸ��� �ð�
	float FrameSecond;
	// Frame Per Second
	int FPS;
	// ������ ����� ���� ī����
	int FrameCount;
	// ������ ����� ���� ī����
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
	//����� �� �ִ� �ִ������� ����� ���� ī����
	unsigned int MaxFPSCounter;
	//����� �� �ִ� �ִ�������
	unsigned int MaxFPS;
	//����� �� �ִ� �ִ� FPS�� �����ϴ� �Լ�
	int GetMaxFPS();
};