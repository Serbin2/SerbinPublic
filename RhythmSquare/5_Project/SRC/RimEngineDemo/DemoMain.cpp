#include "GH.h"


// ���α׷��� ��Ʈ�� ����Ʈ. ��Ƽ����Ʈ ������Ʈ ����
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	// ���� ���� Ŭ����
	// ���ο��� ���� ������ �޽��� �ݹ��� ó���Ѵ�.
	// ���� �׷��Ƚ� ���� ���� �����Ѵ�.
	REDemo* pGameProcess = new REDemo();
	pGameProcess->Initialize(hInstance);
	pGameProcess->Loop();
	pGameProcess->Finalize();

	return 0; // (int)msg.wParam;
}
