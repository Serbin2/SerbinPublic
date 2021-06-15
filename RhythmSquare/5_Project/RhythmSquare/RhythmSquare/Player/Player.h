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

	// 1. ������ � ���� ���� ��θ� �־��ּ��� 
	void PlayingSheetLoad(LPCTSTR filePath);
	void PlayingMusicLoad(LPCTSTR filePath);

	// 2. ���� �÷��� �غ� �ܰ迡�� ȣ�����ּ���
	void GamePlayInit();

	// 3. ���� �÷��� �� �� �������� ȣ�����ּ���
	// 0 ��������
	// 1 esc
	// 2 ���� Ŭ����

	unsigned int GamePlay();
	void PlayRender();

	bool GetKey();
	bool b_ShotEvent;


	// 4. ���� ����� ȣ�����ּ���
	void Finalize();

private:
	//bool IsFiver; // ��Ÿ�� ��Ÿ!
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

	// ������ ������ Ű
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

