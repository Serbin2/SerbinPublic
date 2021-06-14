#include "stdafx.h"
#include "TimeControler.h"
#include "Title.h"
#include "MDmain.h"
#include <crtdbg.h>

COORD myMouse;
HWND	  hWnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/// WinMain 함수 : 윈도즈 프로그램의 최초 진입점 ( Entry Point )
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR	  lpCmdLine,
	int		  nCmdShow)
{
	char	  szAppName[] = "Magic Defenzle";

	MSG      msg;
	WNDCLASS wndclass;

	int CurState = 0;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	/// 윈도 클래스 등록
	RegisterClass(&wndclass);

	/// 윈도 생성에 필요한 크기 계산
	RECT WindowSize = { 0,0,SCREENWIDTH ,SCREENHEIGHT };
	AdjustWindowRect(&WindowSize, WS_OVERLAPPEDWINDOW, FALSE);

	/// 윈도 생성
	hWnd = CreateWindow(szAppName,
		szAppName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		0, 0, WindowSize.right-WindowSize.left, WindowSize.bottom-WindowSize.top,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;

	startLogger(FALSE);
	netStart();




	/// 생성된 윈도를 화면에 표시
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//_CrtSetBreakAlloc(215);
	/// 엔진 구동
	HDC hdc = GetDC(hWnd);
	zzInitilizeEngine(hInstance, hWnd, hdc,0,0);
	timeBeginPeriod(1);
	zzInitializeTime(60.f);

	zzInitializeMenu(hWnd,hInstance);
	zzInitializeGame();
	
	/// 메시지 루프
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// FPS 체크
			zzCheckEndTime();
			if (zzCheckTimeForNextFrame())
			{
				zzCheckStartTime();
			}
			else
			{
				continue;
			}
			
			// 게임 진행부
			switch (CurState)
			{
			case 0:
				CurState = zzMainTitle(myMouse);
				break;
			case 1: // 인 게임
				CurState = zzMDmain(myMouse);
				break;
			case 2: // 팝업 메뉴
				CurState = zzInGamePopUpMenu(myMouse);
				break;
			case 3: // 멀티 플레이
				CurState = zzMultyPlayMenu(myMouse);
				break;
			case 6: // 서버 호스팅
				CurState = zzGetHost();
				break;
			case 7: // 클라이언트
				CurState = zzGetIPAdress(myMouse);
				break;
			case 8: // 서버 게임시작
				CurState = 1;
				break;
			case 9: // 클라 게임시작
				CurState = 1;
				break;
			case 5: // 게임 종료
				DestroyWindow(hWnd);
				break;
			case 15:
				CurState = zzHowToControl();
				break;
			case 16:
				CurState = zzMakers();
				break;
			case 17:
				CurState = zzStageSelect(myMouse);
				break;
			case 20:
				CurState = zzVictor();
				break;
			case 21:
				CurState = zzLoser();
				break;
			}
		}
	}
	_CrtDumpMemoryLeaks();
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	netEnd();
	endLogger();
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_MOUSEMOVE:
		myMouse.X = LOWORD(lParam);
		myMouse.Y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		soundCloseAll();
		timeEndPeriod(0);
		zzEndGame();
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

