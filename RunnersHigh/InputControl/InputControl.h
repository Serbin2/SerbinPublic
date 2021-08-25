#pragma once

#define DIRECTINPUT_VERSION	0x0800

#include <windows.h>

#include <dinput.h>
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")



#ifndef SAFE_RELEASE
#define SAFE_RELEASE(pBuff) if((pBuff)){ (pBuff)->Release(); (pBuff) = NULL; }
#endif

//#include "framework.h"

class CInputControl
{
private:
	HWND hWnd;
	HINSTANCE hInstance;

	LPDIRECTINPUT8 DI;
	LPDIRECTINPUTDEVICE8 diKeyBoard;
	LPDIRECTINPUTDEVICE8 diMouse;

#define SAMPLE_BUFFUER_SIZE	32

	BYTE		 diKeyState[256] = { 0, };
	DIMOUSESTATE diMouseState;

	POINT diMousePos;
	POINT diMousePosAb;

	BYTE diPrevKeyState[256] = { 0, };
	BYTE diNewKeyState[256] = { 0, };

	enum eMouseButtonType
	{
		MBT_LEFT,
		MBT_RIGHT,
		MBT_MIDDLE,

		MBT_MAX
	};

	BYTE diMBTState[MBT_MAX] = { 0, };
	BYTE diPrevMBTState[MBT_MAX] = { 0, };
	BYTE diNewMBTState[MBT_MAX] = { 0, };

	void diMousePosUpdate();


public:
	CInputControl();
	~CInputControl();

	BOOL diInitialize(HWND hwnd, HINSTANCE hInst);
	BOOL diMouseInitialze();
	BOOL diKeyBoardInitialize();

	void diRelease();

	void diCleanUpKeyData();

//#define diIsKeyDown(key)	(diKeyState[(key)] & 0x01)
//#define diIsKeyUp(key)		(diKeyState[(key)] == 0x80)

	BOOL diIsKeyDown(int key);
	BOOL diIsKeyUp(int key);

	BOOL diCheckInput();
	BOOL diReadKeyBoardEX();
	BOOL diReadMouseEX();

#define IsLButtonDn() (diMBTState[MBT_LEFT] & 0x01)
#define IsRButtonDn() (diMBTState[MBT_RIGHT] & 0x01)
#define IsMButtonDn() (diMBTState[MBT_MIDDLE] & 0x01)

#define IsLButtonUp() (diMBTState[MBT_LEFT] ==  0x80)
#define IsRButtonUp() (diMBTState[MBT_RIGHT] == 0x80)
#define IsMButtonUp() (diMBTState[MBT_MIDDLE] == 0x80)


	void diGetMouseScreenPt(POINT* pPos);
	void diGetMouseRelativePt(LONG* pX, LONG* pY, LONG* pZ);

	void diCheckKeyBoard();
	void diCheckMouseButton();

	BOOL diRestore();
};