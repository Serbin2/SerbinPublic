#include "DInputControl.h"

DInputControl::DInputControl()
{
	for (int i = 0; i < 256; i++)
	{
		KeyState[i] = 0;
	}
}

DInputControl::~DInputControl()
{

}

eKeyState DInputControl::GetKeyState(unsigned char key)
{
	return static_cast<eKeyState>(KeyState[key]);
}

void DInputControl::diCheckInput()
{
	unsigned char i = 0;
	for (i = 0; i < 0xFF; i++)
	{
		KeyState[i] = KeyState[i] << 4;
		if (GetAsyncKeyState(i))
		{
			KeyState[i] = KeyState[i] | 0x01;
		}
	}
}

