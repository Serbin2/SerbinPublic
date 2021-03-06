#pragma once


class RSSheet : public GameObject
{
public:
	RSSheet();
	~RSSheet();


	std::vector<RSPage*> m_Page;
	// 앨범 커버(ID)
	wchar_t m_SongName;
	wchar_t m_Composer;
	float m_SongLength;
	int m_Level;

	int m_Place; // 0 : none  1: 사막  2 : 바다  3 : 숲
	float m_BPM; 
	
#ifndef RSTOOL
public:
	

	// 페이지당 저장된 노트를 라인당 노트로 변환
	void RestoreNotePool();

	// input은 0~7 의 값으로 받는다
	void GetInput(int input, float inputTime);

	// 노트를 그리는 함수
	void RenderNote(float PlayingTime, float TimePerBeat); // 노트로의 값 전달

	void MonsterAttackJudge(int key); // 0 : fire  1: water  2 : grass
	void RenderMonster();
	void PageEvent();

	int m_Combo;
	int m_MaxCombo;
	int m_Miss;
	int m_Good;
	int m_Perfect;
	int m_Early;
	int m_Late;

	int m_Score;
	int m_Fever;
	int m_FeverStack;
	float m_FeverTime;
	bool b_Fever;
	float m_PlayerHP;
	int m_KilledMonster;
	bool m_HealReady;
	int m_CurMon;  //  현재 몬스터 인덱스
	int m_TotalMon;  // 이 시트의 총 몬스터 수
	int m_MonNoteEa;  // 현재 몬스터의 노트 수
	int m_PassedNote;  // 지나간 노트 수
	int m_Missed; 

	bool b_ShotEvent; // 피격됨!

private:
	std::vector<RSQNote*> m_Note[8];
	RSPage* m_CurPage;
	
#endif
public:
	// 이상 파일 입출력에 등록된 변수들
	// 이하 파일 입출력에 등록 안된 변수들
	int m_TotalNote;
};

