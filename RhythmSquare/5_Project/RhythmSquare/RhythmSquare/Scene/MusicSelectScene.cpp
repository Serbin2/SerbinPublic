#include "pchApp.h"
#include "MusicSelectScene.h"
#include "../Scene/SceneManager.h"
#include "../Resource/ResourceManager.h"
#include "../GameManager/GameManager.h"
#include "../Object/UI_SIZE_Def.h"


MusicSelectScene::MusicSelectScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother)
	:ChildScene(id, layer, vec, box, mother), DivVec(ZoomDiv), Background(nullptr)
{
	Alram = new Flag();
	Info = new LobbyInfo;
	Next = new Scene*;

	Next[0] = new SliderScene(static_cast<unsigned int>(ObjectID::CHILD_NEXT_SCENE_SLIDE_INGAMEMENU), layer, Slide_Start_Vec, Slide_Size_Box, this);
	Next[0]->AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_SELECT_EASY), 1, Easy_Button_Vec, Select_Button_Size, VK_LBUTTON));
	Next[0]->AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_SELECT_NORMAL), 1, Normal_Button_Vec, Select_Button_Size, VK_LBUTTON));
	Next[0]->AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_SELECT_HARD), 1, Hard_Button_Vec, Select_Button_Size, VK_LBUTTON));
	Next[0]->AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_GAME_START), 1, Start_Button_Vec, Start_Button_Size, VK_LBUTTON));
	Next[0]->AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_MENU_EXIT), 1, Menu_Exit_Button_Vec, Menu_Exit_Button_Box, VK_LBUTTON));

	/// 이쪽에서 fopen을 통하여 최고기록, 최고 콤보, 최고 킬, 노래의 정보 등을 불러와 들고있는다..
	/// 이 데이터들은 실제 저장되는 데이터들, 텍스트 박스에 링크 되는 데이터는 따로 만들어줘야 한다.

	switch (static_cast<ObjectID>(ID))
	{
	case ObjectID::CHILD_SCENE_DESERT_MAINMENU:
		MusicData.Composer = L"Lokan";
		MusicData.Name = L"Introspect";
		WstBPM = L"BPM 132";
		break;
	case ObjectID::CHILD_SCENE_SEA_MAINMENU:
		MusicData.Composer = L"Lokan";
		MusicData.Name = L"PercisionStrike";
		WstBPM = L"BPM 140~145";
		break;
	case ObjectID::CHILD_SCENE_FOREST_MAINMENU:
		MusicData.Composer = L"Lokan";
		MusicData.Name = L"PlotTwist";
		WstBPM = L"BPM 140";
		break;
	}

	/// 각각의 정보들을 textbox에 연결시킨다. 업데이트 시킨 데이터는 OnEvent에서 지속적으로 업데이트하며 데이터를 변경해 나갈 것 이다.
	Next[0]->AttachObject(new TextBox(static_cast<unsigned int>(ObjectID::TEXTBOX_MENU_MUSIC_COMPOSER), 1, TextBox_Composer, Speed_Layout, MusicData.Composer.c_str()));
	Next[0]->AttachObject(new TextBox(static_cast<unsigned int>(ObjectID::TEXTBOX_MENU_MUSIC_NAME), 1, TextBox_MusicName, Speed_Layout, MusicData.Name.c_str()));
	Next[0]->AttachObject(new TextBox(static_cast<unsigned int>(ObjectID::TEXTBOX_MENU_MUSIC_BPM), 1, TextBox_BPM, Speed_Layout, WstBPM.c_str()));

	Next[0]->AttachObject(new TextBox(static_cast<unsigned int>(ObjectID::TEXTBOX_MENU_BESTSCORE), 1, TextBox_BestScore, BestScore_Layout, WstScore.c_str()));
	Next[0]->AttachObject(new TextBox(static_cast<unsigned int>(ObjectID::TEXTBOX_MENU_COMBO), 1, TextBox_Combo, Combo_Layout, WstCombo.c_str()));
	Next[0]->AttachObject(new TextBox(static_cast<unsigned int>(ObjectID::TEXTBOX_MENU_KILL), 1, TextBox_Kill, Kill_Layout, WstKill.c_str()));
	Next[0]->AttachObject(new TextBox(static_cast<unsigned int>(ObjectID::TEXTBOX_MENU_RATE), 1, TextBox_Rate, Rate_Layout, WstRate.c_str()));
}

MusicSelectScene::~MusicSelectScene()
{
	if (Next[0] != nullptr)
		delete Next[0];
	if (Next != nullptr)
		delete Next;
	if (Alram != nullptr)
		delete Alram;
	if (Info != nullptr)
		delete Info;
}

void MusicSelectScene::Awake()
{
	Alram->Set(ZoomTime);
	DivVec = ZoomDiv;
	Scale = BaseScaleSize;
	IsActive = true;
	GameManager::GetInstance().SetMusicSelectData(this->Info);
}

void MusicSelectScene::Sleep()
{
	Alram->Set(0.01f);
	DivVec *= -1;
	GameManager::GetInstance().SetMusicSelectData(nullptr);
	SceneManager::GetInstance().MoveInGameScene();
}

void MusicSelectScene::AttachObject(GameObject* obj)
{
	if (dynamic_cast<Object1*>(obj) != nullptr)
	{
		Next[0]->AttachObject(obj);
	}
}

void MusicSelectScene::OnRender()
{
	/// scale 확대, 축소
	if (IsActive)
	{
		switch (static_cast<ObjectID>(ID))
		{
		case ObjectID::CHILD_SCENE_DESERT_MAINMENU:
			Identify();
			MakeScale(Scale, Desert_Zoom_Point);
			MakeTransformMatrix();
			D2DGraphics::GetInstance().SetTransform(TransformMatrix);
			Mother->OnRender();
			Identify();
			break;
		case ObjectID::CHILD_SCENE_SEA_MAINMENU:
			Identify();
			MakeScale(Scale, Sea_Zoom_Point);
			MakeTransformMatrix();
			D2DGraphics::GetInstance().SetTransform(TransformMatrix);
			Mother->OnRender();
			Identify();
			break;
		case ObjectID::CHILD_SCENE_FOREST_MAINMENU:
			Identify();
			MakeScale(Scale, Forest_Zoom_Point);
			MakeTransformMatrix();
			D2DGraphics::GetInstance().SetTransform(TransformMatrix);
			Mother->OnRender();
			Identify();
			break;
		}
		Next[0]->OnRender();
	}
}

void MusicSelectScene::OnEvent()
{

	DefaultKeyEvent();
	if (IsActive)
	{
		if (Alram->Check())
		{
			if (DivVec.x > 0)
			{
				if (Scale.x < MaxScaleSize.x && Scale.y < MaxScaleSize.x)
				{
					Scale += DivVec;
				}
			}
			if (DivVec.x < 0)
			{
				if (Scale.x > BaseScaleSize.x && Scale.y > BaseScaleSize.x)
				{
					Scale += DivVec;
				}
				if (Scale.x < BaseScaleSize.x)
				{
					Scale = BaseScaleSize;
					IsActive = false;
					Mother->Awake();
					SceneManager::GetInstance().SetCurrentScene(static_cast<ObjectID>(Mother->GetID()));
				}
			}
		}
	}

	if (Scale.x > 3.0f)
	{
		Scale = MaxScaleSize;
		if (!Next[0]->CheckActive())
		{
			Next[0]->Awake();
		}
	}
	Info->BestCombo = GameManager::GetInstance().BestGameData.m_Combo;
	Info->BestKill = GameManager::GetInstance().BestGameData.m_Kill;
	Info->Rate = GameManager::GetInstance().BestGameData.m_Rate;
	Info->BestScore = GameManager::GetInstance().BestGameData.m_Score;

	WstScore = std::to_wstring(Info->BestScore);
	WstCombo = std::to_wstring(Info->BestCombo);
	WstKill = std::to_wstring(Info->BestKill);
	WstRate = std::to_wstring(static_cast<unsigned int>(Info->Rate));
	Next[0]->OnEvent();
}

void MusicSelectScene::DefaultKeyEvent()
{
	switch (Key::GetInstance().GetKeyState(VK_ESCAPE))
	{
	case KEYRELEASE:
		break;
	case KEYDOWN:
		break;
	case KEYPRESS:
		break;
	case KEYUP:
		AudioManager::GetInstance().AllSoundStop();
		Next[0]->Sleep();
		GameManager::GetInstance().SetProperty(InGameProperty::NONE);
	}
}

void MusicSelectScene::Update()
{
}

SliderScene::SliderScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother)
	:ChildScene(id, layer, vec, box, mother), DivVec(SlideDivVec),
	MusicCoverVec(Music_Cover_Vec), NameFreamVec(Name_Box_Vec), SpeedFreamVec(Speed_Box_Vec), StarVec(Star_Box_Vec), BestRankVec(RANK_Vec)

{
	Alram = new Flag();
}

SliderScene::~SliderScene()
{
	for (unsigned int i = 0; i < Object_Layer1.size(); i++)
	{
		if (Object_Layer1[i] != nullptr)
			delete Object_Layer1[i];
	}
	delete Alram;
	Object_Layer1.clear();
}

void SliderScene::Awake()
{
	Alram->Set(SlideTime);
	DivVec = SlideDivVec;
	IsActive = true;
}

void SliderScene::Sleep()
{
	Alram->Set(SlideTime);
	DivVec = Vector2(1.f, 0);
}

void SliderScene::OnEvent()
{
	unsigned int size = Object_Layer1.size();

	if (IsActive)
	{
		if (Alram->Check())
		{
			if (DivVec.x < 0)
			{
				if (Box.right <= 2560)
				{
					DivVec = Vector2(0, 0);
				}

				AddPositionW(DivVec);
				AddBox(DivVec);
				MusicCoverVec += DivVec;
				NameFreamVec += DivVec;
				SpeedFreamVec += DivVec;
				BestRankVec += DivVec;
				StarVec += DivVec;

				unsigned int size = Object_Layer1.size();
				for (unsigned int i = 0; i < size; i++)
				{
					Object_Layer1[i]->AddPositionW(DivVec);
					Object_Layer1[i]->AddBox(DivVec);
				}
			}
			if (DivVec.x > 0)
			{
				if (Box.right >= (2560 + 1240))
				{
					DivVec = Vector2(0, 0);
					Mother->Sleep();
					IsActive = false;
				}

				AddPositionW(DivVec);
				AddBox(DivVec);
				MusicCoverVec += DivVec;
				NameFreamVec += DivVec;
				SpeedFreamVec += DivVec;
				StarVec += DivVec;
				BestRankVec += DivVec;

				for (unsigned int i = 0; i < size; i++)
				{
					Object_Layer1[i]->AddPositionW(DivVec);
					Object_Layer1[i]->AddBox(DivVec);
				}
			}
		}
	}

	for (unsigned int i = 0; i < size; i++)
	{
		Object_Layer1[i]->OnEvent();
	}
}



void SliderScene::OnRender()
{
	if (IsActive)
	{
		Identify();
		MakeTranslate(World_Position);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::CHILD_NEXT_SCENE_SLIDE_INGAMEMENU), 0, 0);

		Identify();
		MakeTranslate(MusicCoverVec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		switch (static_cast<ObjectID>(Mother->GetID()))
		{
		case ObjectID::CHILD_SCENE_DESERT_MAINMENU:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(static_cast<ResourceID>(ResourceID::MUSIC_COVER_1)), 0, 0);
			break;
		case ObjectID::CHILD_SCENE_SEA_MAINMENU:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(static_cast<ResourceID>(ResourceID::MUSIC_COVER_3)), 0, 0);
			break;
		case ObjectID::CHILD_SCENE_FOREST_MAINMENU:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(static_cast<ResourceID>(ResourceID::MUSIC_COVER_2)), 0, 0);
			break;
		}

		Identify();
		MakeTranslate(BestRankVec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		OneGameData info = GameManager::GetInstance().BestGameData;
		if (info.m_Rate > 95)
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::MENU_SELECT_RANK_S), 0, 0);
		if (info.m_Rate > 80 && info.m_Rate <= 95)
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::MENU_SELECT_RANK_A), 0, 0);
		if (info.m_Rate > 70 && info.m_Rate <= 80)
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::MENU_SELECT_RANK_B), 0, 0);
		if (info.m_Rate < 70)
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::MENU_SELECT_RANK_C), 0, 0);
		Identify();


		//MakeTranslate(NameFreamVec);
		//MakeTransformMatrix();
		//D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		//D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(static_cast<ResourceID>(ResourceID::TEXTBOX_MENU_MUSIC_INFO_BG)), 0, 0);
		//Identify();
		/*MakeTranslate(StarVec);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(static_cast<ResourceID>(ResourceID::MENU_SELECT_STARTS)), 0, 0);
		Identify();*/
		RenderObject(1);
	}
}

void SliderScene::Update()
{
}

