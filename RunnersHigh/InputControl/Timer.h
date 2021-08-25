#pragma once

#include <Windows.h>

class Timer
{
public:
	Timer();
	~Timer();


	//Ÿ�̸Ӹ� �����մϴ�
	void InitializeTimer();
	//Ÿ�̸��� �ð��� �����մϴ�
	float TimerTotalTime();
	//���� �����ӿ��� �̹� �����ӱ��� �ɸ� �ð��� �����մϴ�.
	float TimerDeltaTime();
	//Ÿ�̸Ӹ� �����մϴ�.
	void TimerReset();
	//Ÿ�̸Ӱ� ���������ϰ�� Ÿ�̸Ӹ� �����Ѵ�.
	void TimerStart();
	//Ÿ�̸Ӹ� �����Ѵ� �������¿����� �ƹ��͵� �����ʴ´�
	void TimerStop();
	//�� ���ӷ������� ȣ���ؾ��մϴ�.
	void TimerTick();
	//���� Ÿ�̸��� ���¸� �����մϴ�.
	bool TimerIsStop() { return mStopped; };

	//�����Ӱ�� ������ �ڵ����� ���ִ� ����
	void calcFPS();


private:
	double mSecondsPerCount; // ���ɿ� ���� �ּ� �����ð�
	double mDeltaTime;

	long long mBaseTime;
	long long mPausedTime;
	long long mStopTime;
	long long mPrevTime;
	long long mCurrTime;

	bool mStopped;

public:
	//�������� ���۵� �ð�
	float startFrameTime;
	//�����Ӱ���� ���� deltaTime���� �����ð�
	float sumTimer;
	//����� �� �ִ� �ִ������� ����� ���� ī����
	unsigned int maxFPSCounter;
	//����� �� �ִ� �ִ�������
	unsigned int maxFPS;
	//������ ����� ���� ī����
	int frameCount;
	//1�����ӿ� �ɸ��� �ð�
	float frameSecond;
	//Frame Per Second
	int FPS;
	//������ ����� ���� ī����
	int FPSCounter;
};

