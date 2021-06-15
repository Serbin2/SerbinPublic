#pragma once



// ȭ���� ũ��
#define SCREENWIDTH 800
#define SCREENHEIGHT 600

using namespace std;

class REDemo
{
private:
	// �������� ����
	const int m_ScreenWidth = 800;
	const int m_ScreenHeight = 600;

	AudioComponent* AudioManager; 

	SoundEvent testSound; // ���� ������ �����͸� ��� Ŭ����
	SoundEvent testSound2;

	int test = 0;


	// ���� ����
	HWND m_hWnd;
	MSG m_Msg;

public:
	// ���ӿ� ���� �����ӿ��� �ʱ�ȭ�Ѵ�.
	HRESULT Initialize(HINSTANCE hInstance);


	// ���� ���� ����. ���� ������ ����Ǵ� �ݺ�����
	void Loop();
	void GameLoop();


	// ������ �����Ѵ�.
	void Finalize();


	// �޽��� �ڵ鷯 (���� �ݹ�)
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

