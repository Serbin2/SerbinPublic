#pragma once
/// �ش� �ʸ��� �����ϰ� �ִ� ���� �������� ����.
/// fopen�� Ȱ��, �ϴ� txt�� ������� ��.
struct LobbyInfo
{
	unsigned int BestScore;
	unsigned int BestCombo;
	unsigned int BestKill;
	float Rate;
	unsigned int Speed;
	unsigned int Rank;
};

/// �ΰ��� �� ����Ǵ� �������� ����. 
/// ���� �÷��̽� ���ŵǸ�, ���� ���� �ÿ� LobbyInfo �� �ջ�Ǿ� ����ȴ�.
struct InGameInfo
{
	unsigned int Score;
	unsigned int Combo;
	unsigned int MaxCombo;
	unsigned int Kill;
	bool IsPause;
};

/// ���� �ΰ��ӿ� �ʿ��� ���ǵ�, ����, ���� � ���� ����.
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

/// ������ ���̵�
enum class GameDifficulty
{
	EASY,
	NORMAL,
	HARD
};

/// �ΰ��� �Ӽ�
enum class InGameProperty : unsigned int
{
	NONE,
	DESERT,
	SEA,
	FOREST
};

/// ���� �Ӽ�
enum class MonsterProperty : unsigned int
{
	Fire,
	Water,
	Leaf
};

/// ���� Ÿ��
enum class MonsterLevel : unsigned int
{
	Small,
	Medium,
	Large
};

/// ���� ����
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