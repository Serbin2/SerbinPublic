#include "pchApp.h"
#include "SceneManager.h"
#include "../Input/Game_Button.h"
#include "../Object/UI_SIZE_Def.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	for (int i = 0; i < max_scene_size; i++)
	{
		delete ScenePool[i];
	}
	ScenePool.clear();
}

void SceneManager::Initialize()
{
	ScenePool.clear();
	ScenePool.reserve(max_scene_size);
	Load();
}

void SceneManager::Load()
{
	/// new main scene
	ScenePool.push_back(new MainScene(static_cast<unsigned int>(ObjectID::SCENE_START), 1, Main_Start_Vec, Main_Start_Box, true));
	ScenePool.push_back(new MainScene(static_cast<unsigned int>(ObjectID::SCENE_MAINMENU), 1, Main_Menu_Vec, Main_Menu_Box, false));
	ScenePool.push_back(new MainScene(static_cast<unsigned int>(ObjectID::SCENE_ENDING), 1, Main_Ending_Vec, Main_Ending_Box, false));

	/// new Ingame scene
	ScenePool.push_back(new InGameScene(static_cast<unsigned int>(ObjectID::SCENE_INGAME_DESERT), 1, Ingame_Desert_Vec, Ingame_Desert_Box, false));
	ScenePool.push_back(new InGameScene(static_cast<unsigned int>(ObjectID::SCENE_INGAME_FOREST), 1, Ingame_Forest_Vec, Ingame_Forest_Box, false));
	ScenePool.push_back(new InGameScene(static_cast<unsigned int>(ObjectID::SCENE_INGAME_SEA), 1, Ingame_Sea_Vec, Ingame_Sea_Box, false));

	/// new child scene
	// my town
	ScenePool.push_back(new MusicSelectScene(static_cast<unsigned int>(ObjectID::CHILD_SCENE_MYTOWN_MAINMENU), 1, Music_BackGround_Vec, Music_BackGround_Box, ScenePool[static_cast<unsigned int>(ObjectID::SCENE_MAINMENU) - scene_start_number]));
	ScenePool.push_back(new MusicSelectScene(static_cast<unsigned int>(ObjectID::CHILD_SCENE_DESERT_MAINMENU), 1, Music_BackGround_Vec, Music_BackGround_Box, ScenePool[static_cast<unsigned int>(ObjectID::SCENE_MAINMENU) - scene_start_number]));
	ScenePool.push_back(new MusicSelectScene(static_cast<unsigned int>(ObjectID::CHILD_SCENE_SEA_MAINMENU), 1, Music_BackGround_Vec, Music_BackGround_Box, ScenePool[static_cast<unsigned int>(ObjectID::SCENE_MAINMENU) - scene_start_number]));
	ScenePool.push_back(new MusicSelectScene(static_cast<unsigned int>(ObjectID::CHILD_SCENE_FOREST_MAINMENU), 1, Music_BackGround_Vec, Music_BackGround_Box, ScenePool[static_cast<unsigned int>(ObjectID::SCENE_MAINMENU) - scene_start_number]));

	ScenePool.push_back(new OptionScene(static_cast<unsigned int>(ObjectID::CHILD_SCENE_OPTION_MAINMENU), 1, Option_Box_Vec, Option_Box_Size, ScenePool[static_cast<unsigned int>(ObjectID::SCENE_MAINMENU) - scene_start_number]));

	/// load scene control
	for (int i = 0; i < max_scene_size; i++)
	{
		switch (static_cast<ObjectID>(scene_start_number + i))
		{
		case ObjectID::SCENE_START:
			AudioManager::GetInstance().AllSoundStop();
			AudioManager::GetInstance().PlaySound(SoundID::START_BACKGROUND);
			ScenePool[i]->AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_PALY), 1, Vector2(0, 0), D2D1::RectF(0, 0, 0, 0), static_cast<unsigned int>(VK_ANY_KEY)));
			break;
		case ObjectID::SCENE_MAINMENU:
			ScenePool[i]->AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_MENU_DESERT), 1, Vector2(1150, 0 ), D2D1::RectF(0.0f, 0.0f, 480.0f, 480.0f), VK_LBUTTON));
			ScenePool[i]->AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_MENU_FOREST), 1, Vector2(478 , 280 ), D2D1::RectF(0.0f, 0.0f, 480.0f, 480.0f), VK_LBUTTON));
			ScenePool[i]->AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_MENU_SEA), 1, Vector2(1560 , 660 ), D2D1::RectF(0.0f, 0.0f, 480.0f, 480.0f), VK_LBUTTON));
			ScenePool[i]->AttachObject(new Button(static_cast<unsigned int>(ObjectID::BUTTON_OPTION), 1, Vector2(2400, 40), D2D1::RectF(0.0f, 0.0f, 120.f, 120.f), VK_LBUTTON));
			break;
		case ObjectID::SCENE_ENDING:
			break;
		case ObjectID::SCENE_INGAME_DESERT:
			break;
		case ObjectID::SCENE_INGAME_FOREST:
			break;
		case ObjectID::SCENE_INGAME_SEA:
			break;
		case ObjectID::CHILD_SCENE_MYTOWN_MAINMENU:
			break;
		case ObjectID::CHILD_SCENE_DESERT_MAINMENU:
			break;
		case ObjectID::CHILD_SCENE_SEA_MAINMENU:
			break;
		case ObjectID::CHILD_SCENE_FOREST_MAINMENU:
			break;
		case ObjectID::CHILD_SCENE_OPTION_MAINMENU:
			break;
		case ObjectID::CHILD_NEXT_SCENE_SLIDE_INGAMEMENU:
			break;
		}
	}
}

Scene* SceneManager::GetScene(ObjectID id)
{
	return ScenePool[static_cast<unsigned int>(id) - scene_start_number];
}

void SceneManager::Finalize()
{

}

void SceneManager::SetCurrentScene(ObjectID id)
{
	CurrentScene = ScenePool[static_cast<unsigned int>(id) - scene_start_number];
}

Scene* SceneManager::GetCurrenctScene()
{
	return this->CurrentScene;
}

void SceneManager::MoveInGameScene()
{
	switch (GameManager::GetInstance().GetProperty())
	{
	case InGameProperty::NONE:
		return;
	case InGameProperty::DESERT:
		SceneManager::GetInstance().SetCurrentScene(ObjectID::SCENE_INGAME_DESERT);
		GameManager::GetInstance().SetSelectedSong(INTROSPECT);
		break;
	case InGameProperty::SEA:
		SceneManager::GetInstance().SetCurrentScene(ObjectID::SCENE_INGAME_SEA);
		GameManager::GetInstance().SetSelectedSong(PRECISION_STRIKE);
		break;
	case InGameProperty::FOREST:
		SceneManager::GetInstance().SetCurrentScene(ObjectID::SCENE_INGAME_FOREST);
		GameManager::GetInstance().SetSelectedSong(PLOT_TWIST);
		break;
	default:
		return;
	}
	SceneManager::GetInstance().GetCurrenctScene()->Awake();
}
