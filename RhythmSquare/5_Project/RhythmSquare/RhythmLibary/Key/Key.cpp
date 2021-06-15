#include "pchLib.h"
#include "Key.h"

Key::Key()
{
	for (int i = 0; i < 256; i++)
	{
		KeyState[i] = 0;
	}
}

Key::~Key()
{

}

void Key::Update()
{
	/*if (IsUpdate)
	{*/
	unsigned char i = 0;
	for (i = 0; i < 0xFF; i++)
	{
		KeyState[i] = KeyState[i] << 4;
		if (GetAsyncKeyState(i))
		{
			KeyState[i] = KeyState[i] | 0x01;
		}
	}
	//}
}

eKeyState Key::GetKeyState(unsigned char key)
{
	return static_cast<eKeyState>(KeyState[key]);
}

bool Key::AnyKey()
{
	unsigned char i = 0;
	for (i = 1; i < 0xFF; i++)
	{
		if (GetAsyncKeyState(i))
		{
			return true;
		}
	}
	return false;
}

