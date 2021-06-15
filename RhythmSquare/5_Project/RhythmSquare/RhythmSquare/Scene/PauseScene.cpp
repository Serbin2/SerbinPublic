#include "pchApp.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "../../RhythmLibary/Graphics/D2DGraphics.h"
#include "../Resource/ResourceManager.h"

PauseScene::PauseScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother)
	:ChildScene(id, layer, vec, box, mother)
{
	AttachObject(new Button(static_cast<unsigned>(ObjectID::PAUSE_SCENE_BUTTON_CONTINUE), 1, Continue_Button_Vec, Continue_Button_Size, VK_LBUTTON));
	AttachObject(new Button(static_cast<unsigned>(ObjectID::PAUSE_SCENE_BUTTON_RESTART), 1, Restart_Button_Vec, Restart_Button_Size, VK_LBUTTON));
	AttachObject(new Button(static_cast<unsigned>(ObjectID::PAUSE_SCENE_BUTTON_MUSIC_SELECT), 1, MusicSelect_Button_Vec, MusicSelect_Button_Size, VK_LBUTTON));
}

PauseScene::~PauseScene()
{
	for (unsigned int i = 0; i < Object_Layer1.size(); i++)
	{
		if (Object_Layer1[i] != nullptr)
			delete Object_Layer1[i];
	}
	Object_Layer1.clear();
}

void PauseScene::OnRender()
{
	if (IsActive)
	{
		Identify();
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PAUSE_PLAN), 0, 0, 0.5, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

		Identify();
		MakeTranslate(World_Position);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PAUSE_SCENE), 0, 0);
		Identify();

		unsigned int size = Object_Layer1.size();

		for (int i = 0; i < size; i++)
		{
			Object_Layer1[i]->OnRender();
		}
	}
}

void PauseScene::Sleep()
{
	IsActive = false;
	IsPause = false;
}

void PauseScene::OnEvent()
{
	if (IsActive)
	{
		unsigned int size = Object_Layer1.size();

		for (int i = 0; i < size; i++)
		{
			Object_Layer1[i]->OnEvent();
		}
	}
}

void PauseScene::DefaultKeyEvent()
{

}

