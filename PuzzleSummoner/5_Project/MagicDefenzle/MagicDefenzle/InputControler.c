#include "stdafx.h"
#include "InputControler.h"

#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

BOOL UpKeyDown = FALSE;
BOOL UpKeyOn = FALSE;
BOOL DownKeyDown = FALSE;
BOOL DownKeyOn = FALSE;
BOOL LeftKeyDown = FALSE;
BOOL LeftKeyOn = FALSE;
BOOL RightKeyDown = FALSE;
BOOL RightKeyOn = FALSE;
BOOL SpaceKeyDown = FALSE;
BOOL SpaceKeyOn = FALSE;
BOOL EnterKeyDown = FALSE;
BOOL EnterKeyOn = FALSE;
BOOL EscKeyDown = FALSE;
BOOL EscKeyOn = FALSE;
BOOL MLBTNDown = FALSE;
BOOL MLBTNOn = FALSE;

XINPUT_STATE state;
XINPUT_KEYSTROKE stroke;

int MLBTNInput()
{
	// 키가 눌려있는 상태라면 1
	if ((GetKeyState(VK_LBUTTON) & 0x8000))
	{
		MLBTNDown = MLBTNOn;
		MLBTNOn = TRUE;
	}
	else
	{
		MLBTNDown = MLBTNOn;
		MLBTNOn = FALSE;
	}

	if (MLBTNDown == FALSE && MLBTNOn == TRUE)
	{
		return 1;
	}
	else if(MLBTNDown == TRUE && MLBTNOn == FALSE)
	{
		return 3;
	}
	else if(MLBTNDown && MLBTNOn)
	{
		return 2;
	}
	else
	{
		return 4;
	}
}

BOOL UpKeyInput()
{
	// 키가 눌려있는 상태라면 1
	if ((GetKeyState(VK_UP) & 0x8000))
	{
		UpKeyDown = UpKeyOn;
		UpKeyOn = TRUE;
	}
	else
	{
		UpKeyDown = UpKeyOn;
		UpKeyOn = FALSE;
	}

	if (UpKeyDown == FALSE && UpKeyOn == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL DownKeyInput()
{
	// 키가 눌려있는 상태라면 1
	if ((GetKeyState(VK_DOWN) & 0x8000))
	{
		DownKeyDown = DownKeyOn;
		DownKeyOn = TRUE;
	}
	else
	{
		DownKeyDown = DownKeyOn;
		DownKeyOn = FALSE;
	}

	if (DownKeyDown == FALSE && DownKeyOn == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL LeftKeyInput()
{
	// 키가 눌려있는 상태라면 1
	if ((GetKeyState(VK_LEFT) & 0x8000))
	{
		LeftKeyDown = LeftKeyOn;
		LeftKeyOn = TRUE;
	}
	else
	{
		LeftKeyDown = LeftKeyOn;
		LeftKeyOn = FALSE;
	}

	if (LeftKeyDown == FALSE && LeftKeyOn == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL RightKeyInput()
{
	// 키가 눌려있는 상태라면 1
	if ((GetKeyState(VK_RIGHT) & 0x8000))
	{
		RightKeyDown = RightKeyOn;
		RightKeyOn = TRUE;
	}
	else
	{
		RightKeyDown = RightKeyOn;
		RightKeyOn = FALSE;
	}

	if (RightKeyDown == FALSE && RightKeyOn == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL SpaceKeyInput()
{
	if ((GetKeyState(VK_SPACE) & 0x8000))
	{
		SpaceKeyDown = SpaceKeyOn;
		SpaceKeyOn = TRUE;
	}
	else
	{
		SpaceKeyDown = SpaceKeyOn;
		SpaceKeyOn = FALSE;
	}

	if (SpaceKeyDown == FALSE && SpaceKeyOn == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL EnterKeyInput()
{
	if ((GetKeyState(VK_RETURN) & 0x8000))
	{
		EnterKeyDown = EnterKeyOn;
		EnterKeyOn = TRUE;
	}
	else
	{
		EnterKeyDown = EnterKeyOn;
		EnterKeyOn = FALSE;
	}

	if (EnterKeyDown == FALSE && EnterKeyOn == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL EscKeyInput()
{
	if ((GetKeyState(VK_ESCAPE) & 0x8000))
	{
		EscKeyDown = EscKeyOn;
		EscKeyOn = TRUE;
	}
	else
	{
		EscKeyDown = EscKeyOn;
		EscKeyOn = FALSE;
	}

	if (EscKeyDown == FALSE && EscKeyOn == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

DWORD XInput_GetPadState(XINPUT_STATE* state)
{
	ZeroMemory(state, sizeof(XINPUT_STATE)); // 초기화
	DWORD result = XInputGetState(0, state); // 상태 얻기

	return result;
}

DWORD XInput_GetPadInput(XINPUT_KEYSTROKE* keyStroke)
{
	ZeroMemory(keyStroke, sizeof(XINPUT_KEYSTROKE)); // 초기화
	DWORD result = XInputGetKeystroke(0, 0, keyStroke); // 입력 얻기

	return result;
}

BOOL Xinput_menu()
{
	XInput_GetPadInput(&stroke);
	if (stroke.VirtualKey == VK_PAD_START)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL Xinput_A()
{
	XInput_GetPadInput(&stroke);
	if (stroke.VirtualKey == VK_PAD_A)
	{
		return TRUE;
	}
	return FALSE;
}