// InputControl.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
//
#include "InputControl.h"

void CInputControl::diMousePosUpdate()
{
	POINT temp;

	GetCursorPos(&temp);
	ScreenToClient(hWnd, &temp);

	diMousePos = temp;
}

CInputControl::CInputControl() 
{
	DI = NULL;
	diKeyBoard = NULL;
	diMouse = NULL;

	
	diMouseState = { 0 };

	diMousePos = { 0 };
	diMousePosAb = { 0 };

}

CInputControl::~CInputControl()
{

}

BOOL CInputControl::diInitialize(HWND hwnd, HINSTANCE hInst)
{
	diRelease();

	hWnd = hwnd;

	HRESULT hr = S_OK;

	hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&DI, NULL);
	if (FAILED(hr))
	{
		return FALSE;
	}

	if (!diKeyBoardInitialize())
	{
		diRelease();
		return FALSE;
	}

	if (!diMouseInitialze())
	{
		diRelease();
		return FALSE;
	}

	diCleanUpKeyData();

	return TRUE;

}

BOOL CInputControl::diMouseInitialze()
{
	HRESULT hr = S_OK;

	hr = DI->CreateDevice(GUID_SysMouse, &diMouse, NULL);
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = diMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = diMouse->SetCooperativeLevel(hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	if (FAILED(hr))
	{
		return FALSE;
	}

	diMouse->Acquire();

	return TRUE;
}

BOOL CInputControl::diKeyBoardInitialize()
{
	HRESULT hr = S_OK;

	hr = DI->CreateDevice(GUID_SysKeyboard, &diKeyBoard, NULL);
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = diKeyBoard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = diKeyBoard->SetCooperativeLevel(hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = diKeyBoard->Acquire();

	//if (FAILED(hr))
	//{
	//	return FALSE;
	//}

	return TRUE;
}

void CInputControl::diRelease()
{
	if (diKeyBoard)	diKeyBoard->Unacquire();
	if (diMouse)		diMouse->Unacquire();

	SAFE_RELEASE(diKeyBoard);
	SAFE_RELEASE(diMouse);
	SAFE_RELEASE(DI);
}

void CInputControl::diCleanUpKeyData()
{
	ZeroMemory(diPrevKeyState, sizeof(BYTE) * 256);
	ZeroMemory(diNewKeyState, sizeof(BYTE) * 256);
	ZeroMemory(diKeyState, sizeof(BYTE) * 256);
	ZeroMemory(&diMouseState, sizeof(DIMOUSESTATE));
}

BOOL CInputControl::diIsKeyDown(int key)
{
	if (diKeyState[key] & 0x01)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CInputControl::diIsKeyUp(int key)
{
	if (diKeyState[key] & 0x80)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CInputControl::diCheckInput()
{
	if (diReadKeyBoardEX())
	{
		if (diReadMouseEX())
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CInputControl::diReadKeyBoardEX()
{
	if (diKeyBoard == NULL) return FALSE;

	HRESULT hr;

	hr = diKeyBoard->Poll();

	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = diKeyBoard->GetDeviceState(sizeof(BYTE) * 256, diNewKeyState);

	if (FAILED(hr))
	{
		return diRestore();
	}

	diCheckKeyBoard();

	return TRUE;
}

BOOL CInputControl::diReadMouseEX()
{
	if (diMouse == NULL) return FALSE;

	HRESULT hr;

	diMouse->Poll();

	hr = diMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&diMouseState);

	if (FAILED(hr))
	{
		return diRestore();
	}

	diCheckMouseButton();

	diMousePosUpdate();

	return TRUE;
}

void CInputControl::diGetMouseScreenPt(POINT* pPos)
{
	if (pPos)
	{
		*pPos = diMousePos;
	}
}

void CInputControl::diGetMouseRelativePt(LONG* pX, LONG* pY, LONG* pZ)
{
	if (pX) *pX = diMouseState.lX;
	if (pY) *pY = diMouseState.lY;
	if (pZ) *pZ = diMouseState.lZ;
}

void CInputControl::diCheckKeyBoard()
{
	for (int i = 0; i < 256; i++)
	{
		if (diNewKeyState[i] & 0x80)
		{
			if (!(diPrevKeyState[i] & 0x80))
			{
				diKeyState[i] = 0x01; // 처음 눌림
			}
			else if (diPrevKeyState[i] & 0x80)
			{
				diKeyState[i] = 0x81; // 눌린 상태
			}
		}
		else
		{
			if (!(diPrevKeyState[i] & 0x80))
			{
				diKeyState[i] = 0x00; // 눌리지 않은 상태
			}
			else if (diPrevKeyState[i] & 0x80)
			{
				diKeyState[i] = 0x80; // 눌렸다 뗀 상태
			}
		}
	}

	memcpy(diPrevKeyState, diNewKeyState, sizeof(BYTE) * 256);
}

void CInputControl::diCheckMouseButton()
{
	for (int i = 0; i < MBT_MAX; i++)
	{
		diNewMBTState[i] = diMouseState.rgbButtons[i];

		if (diNewMBTState[i] & 0x80)
		{
			if (!(diPrevMBTState[i] & 0x80))
			{
				diMBTState[i] = 0x01; // 처음 눌림
			}
			else if (diPrevMBTState[i] & 0x80)
			{
				diMBTState[i] = 0x81; // 눌린 상태
			}
		}
		else
		{
			if (!(diPrevMBTState[i] & 0x80))
			{
				diMBTState[i] = 0x00; // 눌리지 않은 상태
			}
			else if (diPrevMBTState[i] & 0x80)
			{
				diMBTState[i] = 0x80; // 눌렸다 뗀 상태
			}
		}
	}

	memcpy(diPrevMBTState, diNewMBTState, sizeof(BYTE) * MBT_MAX);
}

BOOL CInputControl::diRestore()
{
	if (diKeyBoard)
	{
		HRESULT hr = diKeyBoard->Acquire();
		while (hr == DIERR_INPUTLOST)
		{
			hr = diKeyBoard->Acquire();
		}
	}

	if (diMouse)
	{
		HRESULT hr = diMouse->Acquire();
		while (hr == DIERR_INPUTLOST)
		{
			hr = diMouse->Acquire();
		}
	}

	return TRUE;
}
