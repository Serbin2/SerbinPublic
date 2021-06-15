#include "pchApp.h"
#include "MainScene.h"
#include "../Resource/ResourceManager.h"
#include "../GameProcess/GameProcess.h"

MainScene::MainScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, bool active)
	:Scene(id, layer, vec, box, active)
{
	Object_Layer1.reserve(50);
	Object_Layer2.reserve(50);
	Object_Layer3.reserve(50);

	Object_Layer1.clear();
	Object_Layer2.clear();
	Object_Layer3.clear();
}

MainScene::~MainScene()
{
	unsigned int size = Object_Layer1.size();
	for (unsigned int i = 0; i < size; i++)
	{
		delete Object_Layer1[i];
	}

	size = Object_Layer2.size();
	for (unsigned int i = 0; i < size; i++)
	{
		delete Object_Layer1[i];
	}

	size = Object_Layer3.size();
	for (unsigned int i = 0; i < size; i++)
	{
		delete Object_Layer1[i];
	}

	Object_Layer1.clear();
	Object_Layer2.clear();
	Object_Layer3.clear();
}


void MainScene::Update()
{

}

void MainScene::AttachObject(GameObject* obj)
{
	if (dynamic_cast<Object1*>(obj) != nullptr)
	{
		Object_Layer1.push_back(dynamic_cast<Object1*>(obj));
	}
	if (dynamic_cast<Object2*>(obj) != nullptr)
	{
		Object_Layer2.push_back(dynamic_cast<Object2*>(obj));
	}
	if (dynamic_cast<Object3*>(obj) != nullptr)
	{
		Object_Layer3.push_back(dynamic_cast<Object3*>(obj));
	}
}

void MainScene::OnEvent()
{
	DefaultKeyEvent();

	if (IsActive && Object_Layer1.empty() == false)
	{
		int size = Object_Layer1.size();

		for (int i = 0; i < size; i++)
		{
			Object_Layer1[i]->OnEvent();
		}
	}
}

void MainScene::OnRender()
{
	switch (static_cast<ObjectID>(ID))
	{
	case ObjectID::SCENE_START:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::SCENE_START), 0, 0);
		break;
	case ObjectID::SCENE_MAINMENU:
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::SCENE_MAINMENU), 0, 0);
		//Identify();
		//MakeTranslate(Vector2(1040.f, 480.f));
		//MakeTransformMatrix();
		//D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		//D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::BUTTON_NAME_TOWN), 0, 0);
		//Identify();
		break;
	case ObjectID::SCENE_ENDING:
		break;
	}
}

void MainScene::RenderObject(unsigned int Layer)
{
	int size = 0;
	if (Layer == 1)
	{
		size = Object_Layer1.size();
		for (int i = 0; i < size; i++)
		{
			Object_Layer1[i]->OnRender();
		}
	}

	if (Layer == 2)
	{
		size = Object_Layer2.size();
		for (int i = 0; i < size; i++)
		{
			Object_Layer2[i]->OnRender();
		}
	}

	if (Layer == 3)
	{
		size = Object_Layer3.size();
		for (int i = 0; i < size; i++)
		{
			Object_Layer3[i]->OnRender();
		}
	}
}

void MainScene::Awake()
{
	IsActive = true;
	AudioManager::GetInstance().AllSoundStop();
	AudioManager::GetInstance().PlaySound(SoundID::LOBBY_BACKGROUND);
}

