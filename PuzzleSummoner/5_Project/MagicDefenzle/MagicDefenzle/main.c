#include "stdafx.h"
#include "TimeControler.h"
#include "Title.h"
#include "MDmain.h"
#include <crtdbg.h>

COORD myMouse;
HWND	  hWnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/// WinMain �Լ� : ������ ���α׷��� ���� ������ ( Entry Point )
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

	/// ���� Ŭ���� ���
	RegisterClass(&wndclass);

	/// ���� ������ �ʿ��� ũ�� ���
	RECT WindowSize = { 0,0,SCREENWIDTH ,SCREENHEIGHT };
	AdjustWindowRect(&WindowSize, WS_OVERLAPPEDWINDOW, FALSE);

	/// ���� ����
	hWnd = CreateWindow(szAppName,
		szAppName,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		0, 0, WindowSize.right-WindowSize.left, WindowSize.bottom-WindowSize.top,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;

	startLogger(FALSE);
	netStart();




	/// ������ ������ ȭ�鿡 ǥ��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//_CrtSetBreakAlloc(215);
	/// ���� ����
	HDC hdc = GetDC(hWnd);
	zzInitilizeEngine(hInstance, hWnd, hdc,0,0);
	timeBeginPeriod(1);
	zzInitializeTime(60.f);

	zzInitializeMenu(hWnd,hInstance);
	zzInitializeGame();
	
	/// �޽��� ����
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
			// FPS üũ
			zzCheckEndTime();
			if (zzCheckTimeForNextFrame())
			{
				zzCheckStartTime();
			}
			else
			{
				continue;
			}
			
			// ���� �����
			switch (CurState)
			{
			case 0:
				CurState = zzMainTitle(myMouse);
				break;
			case 1: // �� ����
				CurState = zzMDmain(myMouse);
				break;
			case 2: // �˾� �޴�
				CurState = zzInGamePopUpMenu(myMouse);
				break;
			case 3: // ��Ƽ �÷���
				CurState = zzMultyPlayMenu(myMouse);
				break;
			case 6: // ���� ȣ����
				CurState = zzGetHost();
				break;
			case 7: // Ŭ���̾�Ʈ
				CurState = zzGetIPAdress(myMouse);
				break;
			case 8: // ���� ���ӽ���
				CurState = 1;
				break;
			case 9: // Ŭ�� ���ӽ���
				CurState = 1;
				break;
			case 5: // ���� ����
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

