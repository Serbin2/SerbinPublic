#include "pchApp.h"

#include "GameManager.h"

GameManager::GameManager()
{
	m_InputRev = 0;
}

GameManager::~GameManager()
{
	if (OptionData != nullptr)
		delete OptionData;
}

void GameManager::Initialize()
{
	ZeroMemory(&BestGameData, sizeof(OneGameData));
	Difficulty = GameDifficulty::EASY;
	Property = InGameProperty::NONE;
	LoadBestData();
	/// option Info 의 기본 데이터 생성. 기준값 1.0 옵션 info에서 조정된 비율 값을 업데이트 받음.
	OptionData = new OptionInfo;
	OptionData->BackGroundSound = 1.f;
	OptionData->EffectSound = 1.f;
	OptionData->InGameSound = 1.f;
	OptionData->TimingSpeed = 1.f;
	m_InputRev = 0;

}

GameDifficulty GameManager::GetDifficulty()
{
	return Difficulty;
}

void GameManager::SetDifficulty(GameDifficulty difficulty)
{
	Difficulty = difficulty;
}

InGameProperty GameManager::GetProperty()
{
	return Property;
}

void GameManager::SetProperty(InGameProperty property)
{
	Property = property;
}

LobbyInfo* GameManager::GetMusicSelectData()
{
	return MusicSelectData;
}

void GameManager::SetMusicSelectData(LobbyInfo* info)
{
	MusicSelectData = info;
}

OptionInfo* GameManager::GetOptionData()
{
	return OptionData;
}

void GameManager::SetSelectedSong(int song)
{
	SongName = song;
}

int GameManager::GetSelectedSong()
{
	return SongName;
}

void GameManager::SetOneGameData(OneGameData data)
{
	ClearData = data;
}

void GameManager::AddOneGameDataFromFile()
{
	BestGameData.m_Kill = max(ClearData.m_Kill, BestGameData.m_Kill);
	BestGameData.m_Combo = max(ClearData.m_Combo, BestGameData.m_Combo);
	BestGameData.m_Score = max(ClearData.m_Score, BestGameData.m_Score);
	BestGameData.m_Rate = max(ClearData.m_Rate, BestGameData.m_Rate);
	SaveBestData();
}

void GameManager::CleanOneGameData()
{
	ZeroMemory(&ClearData, sizeof(OneGameData));
}

void GameManager::LoadBestData()
{
	FILE* fp;
	std::string filePath = "";
	int err;
	switch (Property)
	{
	case InGameProperty::DESERT:
		filePath = "../Data/best_desert.txt";
		break;
	case InGameProperty::SEA:
		filePath = "../Data/best_sea.txt";
		break;
	case InGameProperty::FOREST:
		filePath = "../Data/best_forest.txt";
		break;
	default:
		filePath = "../Data/best_.txt";
		break;
	}

	err = fopen_s(&fp, filePath.c_str(), "rt");
	if (fp)
	{
		fscanf_s(fp, "%d", &BestGameData.m_Combo);
		fscanf_s(fp, "%d", &BestGameData.m_Kill);
		fscanf_s(fp, "%d", &BestGameData.m_Score);
		fscanf_s(fp, "%f", &BestGameData.m_Rate);
	}

	fclose(fp);
}

void GameManager::SaveBestData()
{
	FILE* fp;
	std::string filePath = "";

	switch (SongName)
	{
	case PLOT_TWIST:
		filePath = "../Data/best_forest.txt";
		break;
	case PRECISION_STRIKE:
		filePath = "../Data/best_sea.txt";
		break;
	case INTROSPECT:
		filePath = "../Data/best_desert.txt";
		break;
	default:
		filePath = "../Data/best_.txt";
		break;
	}

	int err = fopen_s(&fp, filePath.c_str(), "wt");
	if (fp)
	{
		fprintf_s(fp, "%d\n", BestGameData.m_Combo);
		fprintf_s(fp, "%d\n", BestGameData.m_Kill);
		fprintf_s(fp, "%d\n", BestGameData.m_Score);
		fprintf_s(fp, "%f\n", BestGameData.m_Rate);
	}
	fclose(fp);
}



OneGameData GameManager::GetOneGameData()
{
	return ClearData;
}