// MDAniViewer.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "MDAniViewer.h"
#include "GraphicEngine.h"
#include "TimeControler.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND hWnd;

//TIMER timr;

zzBitmap nowSprite,BackGround;
zzSummonee nowCharater;
int Anis;
int frames;
int playani;
int delay;
HDC hdc;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK		GetINFO(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadString(hInstance, IDC_MDANIVIEWER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MDANIVIEWER));

    MSG msg;
	hdc = GetDC(hWnd);
	zzInitilizeEngine(hInst, hWnd, hdc, 600, 600);

	Anis = 4;
	frames = 10;
	playani = 0;
	delay = 5;
	LoadBitmap_FromFile2(&nowSprite, "./Resources/dummy.bmp");
	LoadBitmap_FromFile2(&BackGround, "./Resources/BackGround.bmp");
	CreateCharacterRes(&nowCharater, &nowSprite, Anis, frames,delay);

	zzInitializeTime(60.f);

	/// 메시지 루프
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			//calcFPS(&timr);


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
			DrawBitmap_Simple(0, 0, &BackGround);
			zzCheckNowTime();


			/// 시간 정보를 찍어본다.
			_TT(100, 450, "RealTimeTick : %d", zzGetTick());
			_TT(100, 500, "RealTimeElapsed : %d", zzGetTotalTime());
			_TT(100, 550, "RealTimeFPS : %f", zzGetmyFPS());


			Animate_PickPos(10, 10, &nowCharater, playani,255);
			DrawAllToScreen();

		}
	}

    return (int) msg.wParam;
}

OPENFILENAME OFN;
char str[300];
char lpstrFile[MAX_PATH] = "";


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_OPEN:
			//// 구조체 초기화
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			// 파일 필터 : 파일형식 \0 필터 (널종료문자로 구분)
			OFN.lpstrFilter = "Bitmap(.bmp)\0*.bmp\0\0";
			// 파일 이름 에디트에 처음 나타낼 파일명 & 대화상자에서 선택한 파일의 이름을 리턴
			OFN.lpstrFile = lpstrFile;
			// OFN.lpstrFile의 길이
			OFN.nMaxFile = 256;
			// 파일 찾기를 시작할 디렉토리, 
			OFN.lpstrInitialDir = ".\Resouces\\";
			OFN.lpstrTitle = "파일열기 테스트";

			//// File Open Dialog
			if (GetOpenFileName(&OFN))
			{

				//zzLoadMap(OFN.lpstrFile, &mapHeight, &mapWidth);
				//// 경로를 포함한 파일이름
				//wsprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
				//MessageBox(hWnd, str, "파일 열기 성공", MB_OK);

				if (DialogBox(hInst, MAKEINTRESOURCE(IDD_GETINFO), hWnd, GetINFO)==1)
				{
					FreeCharacterMalloc(&nowCharater);
					LoadBitmap_FromFile2(&nowSprite, OFN.lpstrFile);
					CreateCharacterRes(&nowCharater, &nowSprite, Anis, frames, delay);
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case IDM_SAVE:
			//// 구조체 초기화
			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			// 파일 필터 : 파일형식 \0 필터 (널종료문자로 구분)
			OFN.lpstrFilter = "Binary(.bin)\0*.bin\0\0";
			// 파일 이름 에디트에 처음 나타낼 파일명 & 대화상자에서 선택한 파일의 이름을 리턴
			OFN.lpstrFile = lpstrFile;
			// OFN.lpstrFile의 길이
			OFN.nMaxFile = 256;
			// 파일 찾기를 시작할 디렉토리, 
			OFN.lpstrInitialDir = "..\\amuteunProject\\Maps\\";
			OFN.lpstrTitle = "파일저장 테스트";
			OFN.lpstrDefExt = "bin";

			//// File Open Dialog
			//if (GetSaveFileName(&OFN))
			//{
			//	//// 경로를 포함한 파일이름
			//	zzSaveMap(OFN.lpstrFile, mapHeight, mapWidth);
			//	//wsprintf(str, "%s 파일을 선택했습니다.", OFN.lpstrFile);
			//	//MessageBox(hWnd, str, "파일 저장 성공", MB_OK);
			//}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_DESTROY:
		ReleaseDC(hWnd, hdc);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

BOOL CALLBACK GetINFO(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			Anis = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, FALSE);
			frames = GetDlgItemInt(hDlg, IDC_EDIT2, NULL, FALSE);
			playani = GetDlgItemInt(hDlg, IDC_EDIT3, NULL, FALSE);
			delay = GetDlgItemInt(hDlg, IDC_EDIT4, NULL, FALSE);
			EndDialog(hDlg, 1);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return FALSE;
		}
		break;
	}
	return FALSE;
}



// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDANIVIEWER));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MDANIVIEWER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 1200, 800, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
