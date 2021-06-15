#pragma once
#include <Queue>

struct SKeyInput
{
	unsigned char InputKey;
	float InputTime;
};

class Player : public GameObject
{
public:
	Player();
	~Player();

public:
	void OnRender();
	void Animate();

	// 1. 선택한 곡에 따라서 파일 경로를 넣어주세요 
	void PlayingSheetLoad(LPCTSTR filePath);
	void PlayingMusicLoad(LPCTSTR filePath);

	// 2. 게임 플레이 준비 단계에서 호출해주세요
	void GamePlayInit();

	// 3. 게임 플레이 중 매 루프마다 호출해주세요
	// 0 게임진행
	// 1 esc
	// 2 게임 클리어

	unsigned int GamePlay();
	void PlayRender();

	bool GetKey();
	bool b_ShotEvent;


	// 4. 게임 종료시 호출해주세요
	void Finalize();

private:
	//bool IsFiver; // 오타야 오타!
	//bool m_IsFever;
	//int m_TotalKill;
	float m_PlayingTime;
	float m_PlayLength;
	float m_TimePerBeat;

	RSSheet m_CurPlayingSheet;
	SoundEvent* m_CurPlayingMusic;
	bool m_isPlaying;
	bool m_IsFisrt;

	//std::queue<SKeyInput> InputQue;

	// 유저가 설정한 키
	unsigned char m_key1;
	unsigned char m_key1State;
	unsigned char m_key2;
	unsigned char m_key2State;
	unsigned char m_key3;
	unsigned char m_key3State;
	unsigned char m_key4;
	unsigned char m_key4State;
	unsigned char m_key6;
	unsigned char m_key6State;
	unsigned char m_key7;
	unsigned char m_key7State;
	unsigned char m_key8;
	unsigned char m_key8State;
	unsigned char m_key9;
	unsigned char m_key9State;

	unsigned char m_keyFire;
	unsigned char m_keyFireState;
	unsigned char m_keyWater;
	unsigned char m_keyWaterState;
	unsigned char m_keyGrass;
	unsigned char m_keyGrassState;

	unsigned char m_EscKetState;

};

