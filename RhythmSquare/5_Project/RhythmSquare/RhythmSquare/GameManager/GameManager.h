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
	/// 게임 난이도.
	GameDifficulty Difficulty;
	/// 인게임 속성
	InGameProperty Property;
	/// 현재 내가 위치한 메뉴의 정보, 업데이트 해주기 위해 들고있음.
	LobbyInfo* MusicSelectData;
	/// 옵션 정보
	OptionInfo* OptionData;
	/// 클리어 씬에 들어갈 정보
	OneGameData ClearData;
	/// 선택한 곡
	int SongName;

public:
	OneGameData BestGameData;
};

