#pragma once



// 화면의 크기
#define SCREENWIDTH 800
#define SCREENHEIGHT 600

using namespace std;

class REDemo
{
private:
	// 공통적인 설정
	const int m_ScreenWidth = 800;
	const int m_ScreenHeight = 600;

	AudioComponent* AudioManager; 

	SoundEvent testSound; // 음악 파일의 데이터를 담는 클래스
	SoundEvent testSound2;

	int test = 0;


	// 윈도 관련
	HWND m_hWnd;
	MSG m_Msg;

public:
	// 게임용 윈도 프레임웍을 초기화한다.
	HRESULT Initialize(HINSTANCE hInstance);


	// 메인 게임 루프. 실제 게임이 진행되는 반복구문
	void Loop();
	void GameLoop();


	// 게임을 정리한다.
	void Finalize();


	// 메시지 핸들러 (윈도 콜백)
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

