#pragma once
/// 해당 맵마다 보유하고 있는 게임 데이터의 모음.
/// fopen을 활용, 일단 txt로 들고있을 듯.
struct LobbyInfo
{
	unsigned int BestScore;
	unsigned int BestCombo;
	unsigned int BestKill;
	float Rate;
	unsigned int Speed;
	unsigned int Rank;
};

/// 인게임 시 적용되는 유동적인 정보. 
/// 게임 플레이시 갱신되며, 게임 종료 시에 LobbyInfo 에 합산되어 저장된다.
struct InGameInfo
{
	unsigned int Score;
	unsigned int Combo;
	unsigned int MaxCombo;
	unsigned int Kill;
	bool IsPause;
};

/// 실제 인게임에 필요한 스피드, 사운드, 볼륨 등에 대한 정보.
struct OptionInfo
{
	float TimingSpeed;
	float BackGroundSound;
	float InGameSound;
	float EffectSound;
};

struct MusicInfo
{
	std::wstring Name;
	std::wstring Composer;
	unsigned int BPM;
};

/// 게임의 난이도
enum class GameDifficulty
{
	EASY,
	NORMAL,
	HARD
};

/// 인게임 속성
enum class InGameProperty : unsigned int
{
	NONE,
	DESERT,
	SEA,
	FOREST
};

/// 몬스터 속성
enum class MonsterProperty : unsigned int
{
	Fire,
	Water,
	Leaf
};

/// 몬스터 타입
enum class MonsterLevel : unsigned int
{
	Small,
	Medium,
	Large
};

/// 몬스터 상태
enum class MonsterStatus : unsigned int
{
	Walk,
	Attack,
	Dead
};

struct OneGameData
{
	unsigned int m_Combo;
	unsigned int m_Miss;
	unsigned int m_Good;
	unsigned int m_Perfect;
	unsigned int m_Score;
	unsigned int m_Kill;
	float m_Rate;
	int m_HP;
};