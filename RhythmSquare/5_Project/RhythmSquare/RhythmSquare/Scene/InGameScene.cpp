#include "pchApp.h"
#include "InGameScene.h"
#include "ClearScene.h"
#include "LoseScene.h"


#include "../Resource/ResourceManager.h"
#include "../GameProcess/GameProcess.h"

#include <string>

InGameScene::InGameScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, bool active)
	:MainScene(id, layer, vec, box, active), MonsterVec(2280, 1080), CharacterVec(380, 602),
	SquareVec(720, 60), ContinueTime(0.0f), IsContinue(false)
{
	Next = new Scene * [3];
	Next[0] = new PauseScene(static_cast<unsigned int>(ObjectID::CHILD_SCENE_PAUSE_INGAME), 1, Pause_Scene_Vec, Pause_Scene_Size, this);
	m_Player = nullptr;

	Next[1] = new ClearScene(static_cast<unsigned int>(ObjectID::CHILD_SCENE_CLEAR_INGAME), 1, Clear_Scene_Vec, Clear_Scene_Size, this);
	Next[2] = new LoseScene(static_cast<unsigned int>(ObjectID::CHILD_SCENE_FAIL_INGAME), 1, Clear_Scene_Vec, Clear_Scene_Size, this);
}

InGameScene::~InGameScene()
{
	unsigned int size = Object_Layer1.size();
	for (unsigned int i = 0; i < size; i++)
	{
		delete Object_Layer1[i];
	}

	size = Object_Layer2.size();
	for (unsigned int i = 0; i < size; i++)
	{
		delete Object_Layer2[i];
	}

	size = Object_Layer3.size();
	for (unsigned int i = 0; i < size; i++)
	{
		delete Object_Layer3[i];
	}

	Object_Layer1.clear();
	Object_Layer2.clear();
	Object_Layer3.clear();

	if (Next[0] != nullptr)
		delete Next[0];
	if (Next != nullptr)
		delete Next;

	if (m_Player != nullptr)
	{
		m_Player->Finalize();
		delete m_Player;
	}
}

void InGameScene::Awake()
{
	// 로딩 시작 (로딩 화면을 띄워주세요)
	AudioManager::GetInstance().AllSoundStop();
	Identify();
	IsActive = true;
	IsPause = false;
	IsContinue = false;
	D2DGraphics::GetInstance().BeginDraw();
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::LODINGIMAGE), 0, 0);
	D2DGraphics::GetInstance().EndDraw();


	if (m_Player != nullptr)
	{
		m_Player->Finalize();
		delete m_Player;
	}
	m_Player = new Player();

	std::wstring strWaveFilePath;
	std::wstring strSheetFilePath;

	strWaveFilePath = WAVE_PATH;
	strSheetFilePath = SHEET_PATH;
	switch (GameManager::GetInstance().GetSelectedSong())
	{
	case PLOT_TWIST:
		strWaveFilePath += PLOT_TWIST_WAVE;
		strSheetFilePath += PLOT_TWIST_WAVE;
		strWaveFilePath += PLOT_TWIST_EXT;
		break;
	case PRECISION_STRIKE:
		strWaveFilePath += PRECISION_STRIKE_WAVE;
		strSheetFilePath += PRECISION_STRIKE_WAVE;
		strWaveFilePath += PRECISION_STRIKE_EXT;
		break;
	case INTROSPECT:
		strWaveFilePath += INTROSPECT_WAVE;
		strWaveFilePath += INTROSPECT_EXT;
		strSheetFilePath += INTROSPECT_WAVE;
		break;
	default:
		break;
	}

	switch (GameManager::GetInstance().GetDifficulty())
	{
	case GameDifficulty::EASY:
		strSheetFilePath += L"_Easy.bin";
		break;
	case GameDifficulty::NORMAL:
		strSheetFilePath += L"_Normal.bin";
		break;
	case GameDifficulty::HARD:
		strSheetFilePath += L"_Hard.bin";
		break;
	default:
		break;
	}

	m_Player->PlayingMusicLoad(strWaveFilePath.c_str());
	m_Player->PlayingSheetLoad(strSheetFilePath.c_str());

	m_Player->GamePlayInit();
	// 로딩 끝
}

void InGameScene::OnEvent()
{
	DefaultKeyEvent();
	//m_Monster->OnEvent();
	if (!IsPause)
	{
		if (IsActive && Object_Layer1.empty() == false)
		{
			int size = Object_Layer1.size();

			for (int i = 0; i < size; i++)
			{
				Object_Layer1[i]->OnEvent();
			}
		}
	}

	if (IsPause)
	{
		if (!Next[1]->CheckActive() && !Next[2]->CheckActive())
			Next[0]->OnEvent();
		if (!Next[0]->CheckActive() && !Next[2]->CheckActive())
			Next[1]->OnEvent();
		if (!Next[0]->CheckActive() && !Next[1]->CheckActive())
			Next[2]->OnEvent();
	}
}

// 메인 게임 렌더
void InGameScene::OnRender()
{
	if (IsActive)
	{
		// 배경
		switch (static_cast<ObjectID>(ID))
		{
		case ObjectID::SCENE_INGAME_DESERT:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::SCENE_INGAME_DESERT), 0, 0);
			break;
		case ObjectID::SCENE_INGAME_FOREST:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::SCENE_INGAME_FOREST), 0, 0);
			break;
		case ObjectID::SCENE_INGAME_SEA:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::SCENE_INGAME_SEA), 0, 0);
			break;
		}

		// UI 제일 나중에 그려야 함
		/*D2D1_RECT_F hpbar = { 720, 1340, 1840, 1340 };
		D2D1_RECT_F scorebox = { 2000, 40, 2520, 184 };*/

		/*D2DGraphics::GetInstance().DrawRectangle(hpbar, D2D1::ColorF::GreenYellow, true);
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, hpbar, L"hpbar");*/

		/*D2DGraphics::GetInstance().DrawRectangle(scorebox, D2D1::ColorF::GreenYellow, true);
		D2DGraphics::GetInstance().WriteText(D2D1::ColorF::Black, scorebox, L"scorebox");*/

		//캐릭터 디버그
		
		// 캐릭터
		SpriteInfo info = D2DGraphics::GetInstance().CurrentSheetInfo(ResourceManager::GetInstance().GetMotionSheet(ResourceID::OBJECT_PLAYER_));
		D2D1_RECT_F rect = D2D1::RectF(0, 0, info.Layout.right - info.Layout.left, info.Layout.bottom - info.Layout.top);


		if (m_Player->b_ShotEvent)
		{
			Identify();
			MakeTranslate(CharacterVec - Vector2(info.CenterX, info.CenterY));
			MakeTransformMatrix();
			D2DGraphics::GetInstance().SetTransform(TransformMatrix);
			D2DGraphics::GetInstance().AnimateImage(ResourceManager::GetInstance().GetMotionSheet(ResourceID::OBJECT_PLAYER_FAIRY_SHOT), 0, 0, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, 0);
			
			if (ResourceManager::GetInstance().GetMotionSheet(ResourceID::OBJECT_PLAYER_FAIRY_SHOT)->CurrentSpriteCount ==
				ResourceManager::GetInstance().GetMotionSheet(ResourceID::OBJECT_PLAYER_FAIRY_SHOT)->MaxSpriteCount - 1)
			{
				ResourceManager::GetInstance().GetMotionSheet(ResourceID::OBJECT_PLAYER_FAIRY_SHOT)->CurrentSpriteCount = 0;
				m_Player->b_ShotEvent = false;
			}
			Identify();
		}
		else
		{
			Identify();
			MakeTranslate(CharacterVec - Vector2(info.CenterX, info.CenterY));
			MakeTransformMatrix();
			D2DGraphics::GetInstance().SetTransform(TransformMatrix);
			D2DGraphics::GetInstance().AnimateImage(ResourceManager::GetInstance().GetMotionSheet(ResourceID::OBJECT_PLAYER_), 0, 0, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, 0);
			Identify();
		}


		// 속성창
		Identify();
		MakeTranslate(Attribute_Vec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_ATTRIBUTE_BOX), 0, 0);
		Identify();

		// 몬스터 출력 -> 몬스터 클래스로 변경
		//m_Monster->OnRender();

		// 마법진 더 먼저 그려야 함
		

		if (!IsPause && IsContinue)
		{	
			MagicCircle::GetInstance().OnRender();

			Identify();
			MakeTransformMatrix();
			D2DGraphics::GetInstance().SetTransform(TransformMatrix);
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PAUSE_PLAN), 0, 0, 0.5, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

			Identify();
			MakeTranslate(Vector2(1280.f, 720.f) - Vector2(160, 160));
			MakeTransformMatrix();
			D2DGraphics::GetInstance().SetTransform(TransformMatrix);
			if (ContinueTime >= 0.f && ContinueTime <= 1.f)
			{
				D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::CONTINUE_NUMBER_3), 0, 0);
			}
			if (ContinueTime >= 1.f && ContinueTime <= 2.f)
			{
				D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::CONTINUE_NUMBER_2), 0, 0);
			}
			if (ContinueTime >= 2.f && ContinueTime <= 3.f)
			{
				D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::CONTINUE_NUMBER_1), 0, 0);
			}
			Identify();
		}

		if (!IsPause && !IsContinue)
		{
			m_Player->PlayRender();
			FXManager::GetInstance().RenderAll();
		}
		if (IsPause)
		{
		}
		for (int i = 1; i <= 3; i++)
		{
			RenderObject(i);
		}
	}
	if (IsPause)
	{
		if (!Next[1]->CheckActive() && !Next[2]->CheckActive())
			Next[0]->OnRender();
		if (Next[1]->CheckActive() && !Next[2]->CheckActive())
			Next[1]->OnRender();
		if (Next[2]->CheckActive() && !Next[1]->CheckActive())
			Next[2]->OnRender();
	}
}

void InGameScene::Continue()
{
	IsContinue = true;
	IsPause = false;
	Next[0]->Sleep();
	Next[1]->Sleep();
	Next[2]->Sleep();
}

void InGameScene::Restart()
{
	IsContinue = false;
	IsPause = false;
	Next[0]->Sleep();
	Next[1]->Sleep();
	Next[2]->Sleep();
	Awake();
}

void InGameScene::Update()
{
	if (!IsPause && IsContinue)
	{
		ContinueTime += Timer::GetInstance().Delta();
		if (ContinueTime >= 3.5f)
		{
			ContinueTime = 0.0f;
			IsContinue = false;
		}
	}

	if (!IsPause && !IsContinue)
	{
		switch (m_Player->GamePlay())
		{
		case 0:
			break;
		case 1:
			IsPause = true;
			Next[0]->Awake();
			break;
		case 2:
			IsPause = true;
			if (GameManager::GetInstance().GetOneGameData().m_HP <= 0)
			{
				Next[2]->Awake();
			}
			else
			{
				Next[1]->Awake();
			}
		}
	}
}

void InGameScene::DefaultKeyEvent()
{
	/*
	Scene* curscene = SceneManager::GetInstance().GetCurrenctScene();
	Scene* mother = curscene->GetMother();

	switch (Key::GetInstance().GetKeyState(VK_ESCAPE))
	{
	case KEYRELEASE:
		break;
	case KEYDOWN:
		break;
	case KEYPRESS:
		break;
	case KEYUP:
		IsPause = true;
		Next[0]->Awake();
		break;
	}
	*/
}