#pragma once

#include <windows.h>

enum eKeyState : unsigned char
{
	KEYRELEASE = 0x00, KEYDOWN = 0x01, KEYPRESS = 0x11, KEYUP = 0x10
};

class DInputControl
{
private:

	unsigned char KeyState[256] = { 0, };

public:
	DInputControl();
	~DInputControl();

	eKeyState GetKeyState(unsigned char key);

	void diCheckInput();


};

