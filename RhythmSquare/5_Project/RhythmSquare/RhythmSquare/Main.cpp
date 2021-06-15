#include "pchApp.h"
#include "framework.h"
#include "App.h"
#include "dbg_memory.h"
#include <time.h>

App* RhythmSquare;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI wWinMain(HINSTANCE /* hInstance */,
	HINSTANCE /* hPrevInstance */,
	LPWSTR /* lpCmdLine */,
	int /* nCmdShow */)
{
	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	RhythmSquare = new App();
	InitCrtCheck();
	std::srand(time(NULL));
	//CrtCheck(221);
	RhythmSquare->Create(HINST_THISCOMPONENT);
	RhythmSquare->Initialize();
	RhythmSquare->Run();

	EndCrtCheck();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
		RhythmSquare->Resize();
		break;
	case WM_DESTROY:
		if (RhythmSquare != nullptr)
			delete RhythmSquare;
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}