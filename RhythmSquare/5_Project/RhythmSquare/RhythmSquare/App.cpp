#include "pchApp.h"
#include "App.h"
#include "../RhythmLibary/Util/Utility.h"	
#include "../RhythmLibary/Util/Vector2.h"
#include "../RhythmLibary/Util/Matrix2x3.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

Vector2 GetCenterPos(Vector2 lt, Vector2 rb)
{
	Vector2 cp;
	cp.x = lt.x + (rb.x - lt.x) / 2;
	cp.y = lt.y + (rb.y - lt.y) / 2;

	return cp;
}

App::App() :
	hInst(NULL), hWnd(NULL), hDC(NULL), rt({ 0, }), WinSize({ 0, })
{

}

App::~App()
{
	Process->OnDestroy();
	delete Process;
	ReleaseDC(hWnd, hDC);
}

bool App::Create(HINSTANCE hInstance)
{
	// 전역 문자열을 초기화합니다.
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RHYTHMSQUARE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = L"MusicIsMyLife";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	RECT _rt = { 0, 0, 1920, 1080 };
	AdjustWindowRect(&_rt, WS_OVERLAPPEDWINDOW, FALSE);

	this->hInst = hInstance;
	this->hWnd = CreateWindowW(L"MusicIsMyLife", L"MusicIsMyLife", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, _rt.right - _rt.left, _rt.bottom - _rt.top, nullptr, nullptr, hInstance, nullptr);
	this->hDC = GetDC(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	GetClientRect(hWnd, &rt);
	WinSize.x = rt.right;
	WinSize.y = rt.bottom;

	return true;
}

void App::Initialize()
{
	Timer::GetInstance().Start();
	Process = new GameProcess();
	Process->Initialize(hWnd, hDC, rt);
	Process->Awake();
	Process->Start();
}

int App::Run()
{
	MSG msg;

	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			Timer::GetInstance().Update();
			Cursor::GetInstance().Update();
			Key::GetInstance().Update();

			Process->OnInputEvent();

			Process->Update();
			Process->LateUpdate();

			Process->OnRender();
		}
	}
	return (int)msg.wParam;
}

void App::Resize()
{
	GetClientRect(hWnd, &rt);
	WinSize.x = rt.right;
	WinSize.y = rt.bottom;
	D2DGraphics::GetInstance().OnResize(rt.right, rt.bottom);
	Cursor::GetInstance().OnResize(rt.right, rt.bottom);
}

HINSTANCE App::GethInst()
{
	return hInst;
}

HWND App::GethWnd()
{
	return hWnd;
}

HDC App::GethDC()
{
	return hDC;
}

POINT App::GetWinSize()
{
	return WinSize;
}