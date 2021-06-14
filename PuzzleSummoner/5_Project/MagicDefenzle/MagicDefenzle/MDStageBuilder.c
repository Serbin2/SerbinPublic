// MDStageBuilder.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

//#include "framework.h"
#include "MDStageBuilder.h"
#include "stdafx.h"
//#include <crtdbg.h>


HWND hEdit_NumofStage, hEdit_NowStage, hEdit_StageHP, hEdit_StageTime, hEdit_StageSpeed;
HWND hEdit_NumofMonster, hEdit_NowMonster, hEdit_MonsterPower, hEdit_MonsterType, hEdit_MonsterDelay;
HWND hBtn_Save, hBtn_Load;
int NumofStage, NowStage, StageHP, StageTime, StageSpeed;
int NumofMonster, NowMonster, MonsterType, MonsterPower, MonsterDelay;
zzList stage;
char buffer[256];
zzOneStage stagedummy;
zzOneMonster monsterdummy;
OneNode* CurStage;
OneNode* CurMonster;

OPENFILENAME OFN;
char str[300];
char lpstrFile[MAX_PATH] = "";

HWND hBtn_NumofStage, hBtn_NowStage, hBtn_NumofMonster, hBtn_NowMonster;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
CHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
CHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
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
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MDANIVIEWER));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
	//_CrtDumpMemoryLeaks();
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
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_MDANIVIEWER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		hEdit_NumofStage = CreateWindow("edit",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL,
			10, 10, 100, 25, hWnd, (HMENU)1000,
			hInst, NULL);
		hBtn_NumofStage = CreateWindow("button",
			"apply",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			250, 10, 100, 25, hWnd, (HMENU)2000,
			hInst, NULL);
		hEdit_NowStage = CreateWindow("edit",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL,
			10, 40, 100, 25, hWnd, (HMENU)1001,
			hInst, NULL);
		hBtn_NowStage = CreateWindow("button",
			"apply",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			250, 40, 100, 25, hWnd, (HMENU)2001,
			hInst, NULL);
		hEdit_StageHP = CreateWindow("edit",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL,
			10, 70, 100, 25, hWnd, (HMENU)1002,
			hInst, NULL);
		hEdit_StageTime = CreateWindow("edit",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL,
			10, 100, 100, 25, hWnd, (HMENU)1003,
			hInst, NULL);
		hEdit_StageSpeed = CreateWindow("edit",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL,
			10, 130, 100, 25, hWnd, (HMENU)1004,
			hInst, NULL);
		hEdit_NumofMonster = CreateWindow("edit",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL,
			10, 160, 100, 25, hWnd, (HMENU)1005,
			hInst, NULL);
		hBtn_NumofMonster = CreateWindow("button",
			"apply",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			250, 160, 100, 25, hWnd, (HMENU)2005,
			hInst, NULL);
		hEdit_NowMonster = CreateWindow("edit",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL,
			10, 190, 100, 25, hWnd, (HMENU)1006,
			hInst, NULL);
		hBtn_NowMonster = CreateWindow("button",
			"apply",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			250, 190, 100, 25, hWnd, (HMENU)2006,
			hInst, NULL);
		hEdit_MonsterType = CreateWindow("edit",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL,
			10, 220, 100, 25, hWnd, (HMENU)1007,
			hInst, NULL);
		hEdit_MonsterPower = CreateWindow("edit",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL,
			10, 250, 100, 25, hWnd, (HMENU)1008,
			hInst, NULL);
		hEdit_MonsterDelay = CreateWindow("edit",
			NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER |
			ES_AUTOHSCROLL,
			10, 280, 100, 25, hWnd, (HMENU)1009,
			hInst, NULL);

		hBtn_Save = CreateWindow("button",
			"Save",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			400, 200, 100, 25, hWnd, (HMENU)3000,
			hInst, NULL);
		hBtn_Load = CreateWindow("button",
			"Load",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			400, 250, 100, 25, hWnd, (HMENU)3001,
			hInst, NULL);

		NumofStage = 1;
		NowStage = 0;
		StageHP = 1000;
		StageTime = 20;
		StageSpeed = 1;
		NumofMonster = 0;
		NowMonster = 0;
		MonsterPower = 3;
		MonsterType = 0;
		MonsterDelay = 3;

		ListInit(&stage);
		stagedummy.stageNumber = NowStage;
		stagedummy.stageHP = StageHP;
		stagedummy.stageTime = StageTime;
		stagedummy.stageSpeed = StageSpeed;
		stagedummy.numofMonster = 0;
		monsterdummy.TYPE = MonsterType;
		monsterdummy.level = MonsterPower;
		monsterdummy.spawntime = MonsterDelay;
		stgListInsertLast(&stage, stagedummy);

		CurStage = stgListFindAtNode(&stage, stage.count - 1);
		monListInit(&CurStage->d_stg);
		monListInsertLast(&CurStage->d_stg, monsterdummy);

		NumofStage = stage.count;
		_itoa_s(NumofStage, buffer, 256, 10);
		SetWindowText(hEdit_NumofStage, buffer);
		NowStage = stage.count - 1;
		_itoa_s(NowStage, buffer, 256, 10);
		SetWindowText(hEdit_NowStage, buffer);
		StageHP = CurStage->d_stg.stageHP;
		_itoa_s(StageHP, buffer, 256, 10);
		SetWindowText(hEdit_StageHP, buffer);
		StageTime = CurStage->d_stg.stageTime;
		_itoa_s(StageTime, buffer, 256, 10);
		SetWindowText(hEdit_StageTime, buffer);
		StageSpeed = CurStage->d_stg.stageSpeed;
		_itoa_s(StageSpeed, buffer, 256, 10);
		SetWindowText(hEdit_StageSpeed, buffer);
		NumofMonster = CurStage->d_stg.count;
		_itoa_s(NumofMonster, buffer, 256, 10);
		SetWindowText(hEdit_NumofMonster, buffer);
		NowMonster = CurStage->d_stg.count - 1;
		_itoa_s(NowMonster, buffer, 256, 10);
		SetWindowText(hEdit_NowMonster, buffer);
		CurMonster = monListFindAtNode(&CurStage->d_stg, CurStage->d_stg.count - 1);
		MonsterType = CurMonster->d_mon.TYPE;
		_itoa_s(MonsterType, buffer, 256, 10);
		SetWindowText(hEdit_MonsterType, buffer);
		MonsterPower = CurMonster->d_mon.level;
		_itoa_s(MonsterPower, buffer, 256, 10);
		SetWindowText(hEdit_MonsterPower, buffer);
		MonsterDelay = CurMonster->d_mon.spawntime;
		_itoa_s(MonsterDelay, buffer, 256, 10);
		SetWindowText(hEdit_MonsterDelay, buffer);



		SetFocus(hEdit_NumofStage);

		break;
	case WM_COMMAND:
		// 메뉴 선택을 구문 분석합니다:
		switch (LOWORD(wParam))
		{
		case 1000: // 총 스테이지
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit_NumofStage, buffer, 256);
				NumofStage = atoi(buffer);
				break;
			}
			break;
		case 1001: // 현재 스테이지
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit_NowStage, buffer, 256);
				NowStage = atoi(buffer);
				break;
			}
			break;
		case 1002: // 스테이지 체력
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit_StageHP, buffer, 256);
				StageHP = atoi(buffer);
				CurStage->d_stg.stageHP = StageHP;
				break;
			}
			break;
		case 1003: // 스테이지 시간
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit_StageTime, buffer, 256);
				StageTime = atoi(buffer);
				CurStage->d_stg.stageTime = StageTime;
				break;
			}
			break;
		case 1004: // 스테이지 속도
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit_StageSpeed, buffer, 256);
				StageSpeed = atoi(buffer);
				CurStage->d_stg.stageSpeed = StageSpeed;
				break;
			}
			break;
		case 1005: // 스테이지의 총 몬스터
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit_NumofMonster, buffer, 256);
				NumofMonster = atoi(buffer);
				break;
			}
			break;
		case 1006: // 현재 몬스터
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit_NowMonster, buffer, 256);
				NowMonster = atoi(buffer);
				break;
			}
			break;
		case 1007: // 몬스터 타입
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit_MonsterType, buffer, 256);
				MonsterType = atoi(buffer);
				CurMonster->d_mon.TYPE = MonsterType;
				break;
			}
			break;
		case 1008: // 몬스터 레벨
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit_MonsterPower, buffer, 256);
				MonsterPower = atoi(buffer);
				CurMonster->d_mon.level = MonsterPower;
				break;
			}
			break;
		case 1009: // 몬스터 소환 딜레이
			switch (HIWORD(wParam))
			{
			case EN_CHANGE:
				GetWindowText(hEdit_MonsterDelay, buffer, 256);
				MonsterDelay = atoi(buffer);
				CurMonster->d_mon.spawntime = MonsterDelay;
				break;
			}
			break;
		case 2000: // 총 스테이지 적용
			if (NumofStage > stage.count)
			{
				for (int i = stage.count; i < NumofStage; i++)
				{
					stagedummy.stageNumber = i;
					stagedummy.stageHP = StageHP;
					stagedummy.stageTime = StageTime;
					stagedummy.stageSpeed = StageSpeed;
					//stagedummy.numofMonster = 0;

					monsterdummy.TYPE = MonsterType;
					monsterdummy.level = MonsterPower;
					monsterdummy.spawntime = MonsterDelay;
					stgListInsertLast(&stage, stagedummy);

					CurStage = stgListFindAtNode(&stage, stage.count - 1);
					monListInit(&CurStage->d_stg);
					monListInsertLast(&CurStage->d_stg, monsterdummy);
					CurMonster = (monListFindAtNode(&CurStage->d_stg, CurStage->d_stg.count - 1));
					CurStage->d_stg.numofMonster = CurStage->d_stg.count;
				}
			}
			else if (NumofStage < stage.count)
			{
				for (int i = stage.count - 1; i > NumofStage; i--)
				{
					CurStage = stgListFindAtNode(&stage, i);
					while (monListRemoveLast(&CurStage->d_stg))
					{
					}
					free(CurStage->d_stg.head);
					stgListRemove(&stage, i);
				}
				CurStage = stgListFindAtNode(&stage, stage.count - 1);
			}
			NumofStage = stage.count;
			_itoa_s(NumofStage, buffer, 256, 10);
			SetWindowText(hEdit_NumofStage, buffer);
			NowStage = stage.count - 1;
			_itoa_s(NowStage, buffer, 256, 10);
			SetWindowText(hEdit_NowStage, buffer);
			StageHP = CurStage->d_stg.stageHP;
			_itoa_s(StageHP, buffer, 256, 10);
			SetWindowText(hEdit_StageHP, buffer);
			StageTime = CurStage->d_stg.stageTime;
			_itoa_s(StageTime, buffer, 256, 10);
			SetWindowText(hEdit_StageTime, buffer);
			StageSpeed = CurStage->d_stg.stageSpeed;
			_itoa_s(StageSpeed, buffer, 256, 10);
			SetWindowText(hEdit_StageSpeed, buffer);
			NumofMonster = CurStage->d_stg.count;
			_itoa_s(NumofMonster, buffer, 256, 10);
			SetWindowText(hEdit_NumofMonster, buffer);
			NowMonster = CurStage->d_stg.count - 1;
			_itoa_s(NowMonster, buffer, 256, 10);
			SetWindowText(hEdit_NowMonster, buffer);
			CurMonster = monListFindAtNode(&CurStage->d_stg, CurStage->d_stg.count - 1);
			MonsterType = CurMonster->d_mon.TYPE;
			_itoa_s(MonsterType, buffer, 256, 10);
			SetWindowText(hEdit_MonsterType, buffer);
			MonsterPower = CurMonster->d_mon.level;
			_itoa_s(MonsterPower, buffer, 256, 10);
			SetWindowText(hEdit_MonsterPower, buffer);
			MonsterDelay = CurMonster->d_mon.spawntime;
			_itoa_s(MonsterDelay, buffer, 256, 10);
			SetWindowText(hEdit_MonsterDelay, buffer);
			SetFocus(hWnd);
			break;
		case 2001: // 편집할 스테이지
			if (NowStage < stage.count)
			{
				CurStage = stgListFindAtNode(&stage, NowStage);
				StageHP = CurStage->d_stg.stageHP;
				_itoa_s(StageHP, buffer, 256, 10);
				SetWindowText(hEdit_StageHP, buffer);
				StageTime = CurStage->d_stg.stageTime;
				_itoa_s(StageTime, buffer, 256, 10);
				SetWindowText(hEdit_StageTime, buffer);
				StageSpeed = CurStage->d_stg.stageSpeed;
				_itoa_s(StageSpeed, buffer, 256, 10);
				SetWindowText(hEdit_StageSpeed, buffer);
				NumofMonster = CurStage->d_stg.count;
				_itoa_s(NumofMonster, buffer, 256, 10);
				SetWindowText(hEdit_NumofMonster, buffer);
				NowMonster = CurStage->d_stg.count - 1;
				_itoa_s(NowMonster, buffer, 256, 10);
				SetWindowText(hEdit_NowMonster, buffer);
				CurMonster = monListFindAtNode(&CurStage->d_stg, CurStage->d_stg.count - 1);
				MonsterType = CurMonster->d_mon.TYPE;
				_itoa_s(MonsterType, buffer, 256, 10);
				SetWindowText(hEdit_MonsterType, buffer);
				MonsterPower = CurMonster->d_mon.level;
				_itoa_s(MonsterPower, buffer, 256, 10);
				SetWindowText(hEdit_MonsterPower, buffer);
				MonsterDelay = CurMonster->d_mon.spawntime;
				_itoa_s(MonsterDelay, buffer, 256, 10);
				SetWindowText(hEdit_MonsterDelay, buffer);
			}
			SetFocus(hWnd);
			break;
		case 2005: // 현재 스테이지의 총 몬스터 적용
			if (NumofMonster > CurStage->d_stg.count)
			{
				for (int i = CurStage->d_stg.count; i < NumofMonster; i++)
				{
					monsterdummy.TYPE = MonsterType;
					monsterdummy.level = MonsterPower;
					monsterdummy.spawntime = MonsterDelay;

					monListInit(&CurStage->d_stg);
					monListInsertLast(&CurStage->d_stg, monsterdummy);
					CurMonster = (monListFindAtNode(&CurStage->d_stg, CurStage->d_stg.count - 1));
				}
			}
			else if (NumofMonster < CurStage->d_stg.count)
			{
				for (int i = CurStage->d_stg.count - 1; i > NumofMonster; i--)
				{

					monListRemove(&CurStage->d_stg, i);
				}
				CurMonster = (monListFindAtNode(&CurStage->d_stg, CurStage->d_stg.count - 1));
			}
			NumofMonster = CurStage->d_stg.count;
			_itoa_s(NumofMonster, buffer, 256, 10);
			SetWindowText(hEdit_NumofMonster, buffer);
			NowMonster = CurStage->d_stg.count - 1;
			_itoa_s(NowMonster, buffer, 256, 10);
			SetWindowText(hEdit_NowMonster, buffer);
			MonsterType = CurMonster->d_mon.TYPE;
			_itoa_s(MonsterType, buffer, 256, 10);
			SetWindowText(hEdit_MonsterType, buffer);
			MonsterPower = CurMonster->d_mon.level;
			_itoa_s(MonsterPower, buffer, 256, 10);
			SetWindowText(hEdit_MonsterPower, buffer);
			MonsterDelay = CurMonster->d_mon.spawntime;
			_itoa_s(MonsterDelay, buffer, 256, 10);
			SetWindowText(hEdit_MonsterDelay, buffer);
			SetFocus(hWnd);
			break;
		case 2006: // 현재 편집할 몬스터
			if (NowMonster < CurStage->d_stg.count)
			{
				CurMonster = (monListFindAtNode(&CurStage->d_stg, NowMonster));
				MonsterType = CurMonster->d_mon.TYPE;
				_itoa_s(MonsterType, buffer, 256, 10);
				SetWindowText(hEdit_MonsterType, buffer);
				MonsterPower = CurMonster->d_mon.level;
				_itoa_s(MonsterPower, buffer, 256, 10);
				SetWindowText(hEdit_MonsterPower, buffer);
				MonsterDelay = CurMonster->d_mon.spawntime;
				_itoa_s(MonsterDelay, buffer, 256, 10);
				SetWindowText(hEdit_MonsterDelay, buffer);
			}
			SetFocus(hWnd);
			break;
		case 3000: // 파일 저장
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
			OFN.lpstrInitialDir = "..\\MagicDefenzle\\Stage\\";
			OFN.lpstrTitle = "파일저장 테스트";
			OFN.lpstrDefExt = "bin";

			//// File Open Dialog
			if (GetSaveFileName(&OFN))
			{
				//// 경로를 포함한 파일이름
				zzSaveMap(OFN.lpstrFile, &stage);

			}
			SetFocus(hWnd);
			break;
		case 3001: // 파일 불러오기
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
			OFN.lpstrInitialDir = "..\\MagicDefenzle\\Stage\\";
			OFN.lpstrTitle = "파일열기 테스트";

			//// File Open Dialog
			if (GetOpenFileName(&OFN))
			{
				zzLoadMap(OFN.lpstrFile, &stage);
				CurStage = stgListFindAtNode(&stage, stage.count - 1);
				NumofStage = stage.count;
				_itoa_s(NumofStage, buffer, 256, 10);
				SetWindowText(hEdit_NumofStage, buffer);
				NowStage = stage.count - 1;
				_itoa_s(NowStage, buffer, 256, 10);
				SetWindowText(hEdit_NowStage, buffer);
				StageHP = CurStage->d_stg.stageHP;
				_itoa_s(StageHP, buffer, 256, 10);
				SetWindowText(hEdit_StageHP, buffer);
				StageTime = CurStage->d_stg.stageTime;
				_itoa_s(StageTime, buffer, 256, 10);
				SetWindowText(hEdit_StageTime, buffer);
				StageSpeed = CurStage->d_stg.stageSpeed;
				_itoa_s(StageSpeed, buffer, 256, 10);
				SetWindowText(hEdit_StageSpeed, buffer);
				NumofMonster = CurStage->d_stg.count;
				_itoa_s(NumofMonster, buffer, 256, 10);
				SetWindowText(hEdit_NumofMonster, buffer);
				NowMonster = CurStage->d_stg.count - 1;
				_itoa_s(NowMonster, buffer, 256, 10);
				SetWindowText(hEdit_NowMonster, buffer);
				CurMonster = monListFindAtNode(&CurStage->d_stg, CurStage->d_stg.count - 1);
				MonsterType = CurMonster->d_mon.TYPE;
				_itoa_s(MonsterType, buffer, 256, 10);
				SetWindowText(hEdit_MonsterType, buffer);
				MonsterPower = CurMonster->d_mon.level;
				_itoa_s(MonsterPower, buffer, 256, 10);
				SetWindowText(hEdit_MonsterPower, buffer);
				MonsterDelay = CurMonster->d_mon.spawntime;
				_itoa_s(MonsterDelay, buffer, 256, 10);
				SetWindowText(hEdit_MonsterDelay, buffer);
			}
			SetFocus(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		TextOut(hdc, 110, 10, "Total Stage", 11);
		TextOut(hdc, 110, 40, "Current Stage", 13);
		TextOut(hdc, 110, 70, "Stage HP", 8);
		TextOut(hdc, 110, 100, "Stage Time", 10);
		TextOut(hdc, 110, 130, "Stage Speed", 11);
		TextOut(hdc, 110, 160, "Total Monster", 13);
		TextOut(hdc, 110, 190, "Current Monster", 15);
		TextOut(hdc, 110, 220, "Monster Type", 12);
		TextOut(hdc, 110, 250, "Monster Power", 13);
		TextOut(hdc, 110, 280, "Monster Delay", 13);


		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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
