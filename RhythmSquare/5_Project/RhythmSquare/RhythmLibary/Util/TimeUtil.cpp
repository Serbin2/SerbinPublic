#include "pchLib.h"
#include<Windows.h>
#include<iostream>
#include<string>
#include<chrono>
#include "TimeUtil.h"
#include "Timer.h"
#include "Frame.h"

Flag::Flag()
	:Sum(0.f), BaseTime(0.f)
{

}

Flag::Flag(float time)
	: Sum(0.f), BaseTime(time)
{
}

Flag::~Flag()
{
}

void Flag::Set(float time)
{
	BaseTime = time;
	Sum = 0.f;
}

bool Flag::OneTimeCheck()
{
	Sum += Timer::GetInstance().Delta();
	if (Sum >= BaseTime)
	{
		return true;
	}
	else
		return false;
}

bool Flag::Check()
{
	Sum += Timer::GetInstance().Delta();
	if (Sum >= BaseTime)
	{
		Sum = 0.0f;
		return true;
	}
	else
		return false;
}

Flag_Fream::Flag_Fream()
	:Sum(0.f), BaseTime(0.f)
{
}

Flag_Fream::Flag_Fream(float time)
	: Sum(0.f), BaseTime(time)
{
}

Flag_Fream::~Flag_Fream()
{

}

void Flag_Fream::Set(float time)
{
	BaseTime = time;
	Sum = 0.f;
}

bool Flag_Fream::OneTimeCheck()
{
	Sum += GameFream::GetInstance().Delta();
	if (Sum >= BaseTime)
	{
		return true;
	}
	else
		return false;
}

bool Flag_Fream::Check()
{
	Sum += GameFream::GetInstance().Delta();
	if (Sum >= BaseTime)
	{
		Sum = 0.0f;
		return true;
	}
	else
		return false;
}
