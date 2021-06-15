#include "pchApp.h"
#include "LoseScene.h"
#include "../Resource/ResourceManager.h"

LoseScene::LoseScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother)
	:ChildScene(id, layer, vec, box, mother)
{

}

LoseScene::~LoseScene()
{

}

void LoseScene::OnEvent()
{
	DefaultKeyEvent();
}

void LoseScene::OnRender()
{
	if (IsActive)
	{
		Identify();
		MakeTranslate(World_Position);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::GAME_LOSE_BACK_GROUND), 0, 0);
		Identify();
	}
}

void LoseScene::Sleep()
{
	IsActive = false;
	IsPause = false;
}

void LoseScene::DefaultKeyEvent()
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
		IsActive = false;
		Mother->OffPause();
		SceneManager::GetInstance().SetCurrentScene(ObjectID::SCENE_MAINMENU);
		break;
	default:
		break;
	}
}
