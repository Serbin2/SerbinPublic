#pragma once
#include <windows.h>
#include "../Util/Singleton.h"
#include "KeyDef.h"

#define KEY Key::GetInstance().

enum eKeyState : unsigned char
{
	KEYRELEASE = 0x00, KEYDOWN = 0x01, KEYPRESS = 0x11, KEYUP = 0x10
};

class Key : public Singleton<Key>
{
public:
	Key();
	~Key();

	unsigned char KeyState[256];
public:
	void Update();
	eKeyState GetKeyState(unsigned char key);
	bool AnyKey();

public:
	bool IsUpdate;
};
