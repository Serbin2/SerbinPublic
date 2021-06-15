#pragma once
#include "resource.h"
#include "../RhythmLibary/Graphics/D2DGraphics.h"
#include "../RhythmLibary/Key/Key.h"
#include "../RhythmLibary/Util/Frame.h"
#include "./GameProcess/GameProcess.h"
#include "Input/Cursor.h"

class App
{
public:
	App();
	~App();

public:
	bool Create(HINSTANCE hInstance);
	static LRESULT Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Initialize();
	int Run();

	void Resize();

	HINSTANCE GethInst();
	HWND GethWnd();
	HDC GethDC();
	POINT GetWinSize();

private:
	HINSTANCE hInst;
	HWND hWnd;
	HDC hDC;
	RECT rt;
	POINT WinSize;
	FLOAT DpiX, DpiY;

	GameProcess* Process;
};