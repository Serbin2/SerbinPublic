#pragma once
#include "../../RhythmLibary/Util/Singleton.h"
#include "../GameProcess/DefaultGameData.h"

class GameManager : public Singleton<GameManager>
{
public:
	GameManager();
	~GameManager();

public:
	void Initialize();
	GameDifficulty GetDifficulty();
	void SetDifficulty(GameDifficulty difficulty);
	InGameProperty GetProperty();
	void SetProperty(InGameProperty property);
	LobbyInfo* GetMusicSelectData();
	void SetMusicSelectData(LobbyInfo* info);
	OptionInfo* GetOptionData();
	void SetSelectedSong(int song);
	int GetSelectedSong();
	void SetOneGameData(OneGameData data);
	void AddOneGameDataFromFile();
	void CleanOneGameData();
	void LoadBestData();
	void SaveBestData();

	float m_InputRev;

	OneGameData GetOneGameData();
private:
	/// ���� ���̵�.
	GameDifficulty Difficulty;
	/// �ΰ��� �Ӽ�
	InGameProperty Property;
	/// ���� ���� ��ġ�� �޴��� ����, ������Ʈ ���ֱ� ���� �������.
	LobbyInfo* MusicSelectData;
	/// �ɼ� ����
	OptionInfo* OptionData;
	/// Ŭ���� ���� �� ����
	OneGameData ClearData;
	/// ������ ��
	int SongName;

public:
	OneGameData BestGameData;
};

