#include "GH.h"

HRESULT REDemo::Initialize(HINSTANCE hInstance)
{
	/// Win32 관련
	// 윈도 클래스
	char szAppName[] = "GameAcademy 2019 Direct2D Demo";
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = REDemo::WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	// 윈도 클래스 등록
	RegisterClass(&wndclass);

	// 윈도 생성
	m_hWnd = CreateWindow(
		szAppName,
		szAppName,
		WS_OVERLAPPEDWINDOW,
		100, 100, m_ScreenWidth, m_ScreenHeight,
		NULL, NULL, hInstance, NULL);

	if (!m_hWnd) return FALSE;

	// 생성된 윈도를 화면에 표시
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);


	/// 그래픽스 엔진 관련

	// 그래픽스 엔진 초기화
	

	RimEngine::GetInstance()->InitializeEngine(m_hWnd);
	AudioManager = new AudioComponent;
	/*
	AudioManager->loadFile(L"../RimEngine/Evolution.mp3", testSound);
	

	AudioManager->playSoundEvent(testSound);
	*/
	//AudioManager->playSoundEvent(testSound2);
	return S_OK;
}

void REDemo::Loop()
{
	while (true)
	{
		if (PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_Msg.message == WM_QUIT) break;

			DispatchMessage(&m_Msg);
		}
		else
		{
			GameLoop();
		}
	}
}

void REDemo::GameLoop()
{
	RimEngine::GetInstance()->BeginDraw();
	

	RimEngine::GetInstance()->DrawEllipse(50, 50, 10,RGB(0,255,0));

	/// 백버퍼의 내용을 화면으로 출력한다.
	RimEngine::GetInstance()->EndDraw();
}

void REDemo::Finalize()
{
	RimEngine::GetInstance()->Finalize();

	
}

// 메시지 핸들러 (윈도 콜백)
LRESULT CALLBACK REDemo::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
