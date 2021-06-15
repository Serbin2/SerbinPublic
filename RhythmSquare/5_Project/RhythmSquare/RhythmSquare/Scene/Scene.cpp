#include "pchApp.h"
#include "Scene.h"
#include "../Resource/ResourceManager.h"
#include "../../RhythmLibary/Graphics/D2DGraphics.h"
#include "../GameProcess/GameProcess.h"


Scene::Scene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, bool active)
	:Object1(id, layer, vec, box), IsActive(active), Mother(nullptr)
{
}

Scene::~Scene()
{

}

void Scene::Update()
{

}

void Scene::Sleep()
{
	if (Mother != nullptr)
	{
		SceneManager::GetInstance().GetCurrenctScene()->Sleep();
		SceneManager::GetInstance().SetCurrentScene(static_cast<ObjectID>(Mother->GetID()));
		SceneManager::GetInstance().GetCurrenctScene()->Awake();
	}
	else
		IsActive = false;
}

void Scene::Pause()
{
	IsPause = true;
}

void Scene::OffPause()
{
	IsPause = false;
}

void Scene::Restart()
{
	IsPause = false;
}

void Scene::Awake()
{
	IsActive = true;
}

void Scene::Continue()
{
}

Scene* Scene::GetMother()
{
	return Mother;
}

Scene** Scene::GetNext()
{
	return Next;
}

bool Scene::CheckActive()
{
	return IsActive;
}

void Scene::AttachObject(GameObject* obj)
{
	Object_Layer1.push_back(dynamic_cast<Object1*>(obj));
}

void Scene::RenderObject(unsigned int Layer)
{
	if (Layer == 1)
	{
		unsigned int size = Object_Layer1.size();
		for (unsigned int i = 0; i < Object_Layer1.size(); i++)
		{
			Object_Layer1[i]->OnRender();
		}
	}
}

void Scene::DefaultKeyEvent()
{
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
		AudioManager::GetInstance().AllSoundStop();
		if (mother == nullptr)
		{
			PostQuitMessage(0);
		}
		else
		{
			curscene->Sleep();
			mother->Awake();
			SceneManager::GetInstance().SetCurrentScene(static_cast<ObjectID>(mother->GetID()));
		}
		break;
	}
}


void Scene::ObjectMakeTranslate(Vector2 delta)
{
	unsigned int size = Object_Layer1.size();
	for (unsigned int i = 0; i < Object_Layer1.size(); i++)
	{
		Object_Layer1[i]->MakeTranslate(delta);
	}
}

void Scene::ObjectMakeScale(Vector2 scale, Vector2 center)
{
	unsigned int size = Object_Layer1.size();
	for (unsigned int i = 0; i < Object_Layer1.size(); i++)
	{
		Object_Layer1[i]->MakeScale(scale, center);
	}
}

void Scene::ObjectRocate(float angle, Vector2 axis)
{
	unsigned int size = Object_Layer1.size();
	for (unsigned int i = 0; i < Object_Layer1.size(); i++)
	{
		Object_Layer1[i]->MakeRotate(angle, axis);
	}
}

void Scene::Object_MakeTdransform()
{
	unsigned int size = Object_Layer1.size();
	for (unsigned int i = 0; i < Object_Layer1.size(); i++)
	{
		Object_Layer1[i]->MakeTransformMatrix();
	}
}

void Scene::ObjectIdentify()
{
	unsigned int size = Object_Layer1.size();
	for (unsigned int i = 0; i < Object_Layer1.size(); i++)
	{
		Object_Layer1[i]->Identify();
	}
}

void Scene::OnRender()
{
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(static_cast<ResourceID>(ID)), 0, 0);
}

void Scene::OnEvent()
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

