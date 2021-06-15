#include "pchApp.h"
#include "ChildScene.h"
#include "SceneManager.h"
#include "../../RhythmLibary/Graphics/D2DGraphics.h"
#include "../Resource/ResourceManager.h"
#include "../GameProcess/GameProcess.h"

ChildScene::ChildScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother)
	:Scene(id, layer, vec, box, false)
{
	Mother = mother;
}

ChildScene::~ChildScene()
{
	unsigned int size = Object_Layer1.size();
	for (unsigned int i = 0; i < size; i++)
	{
		if (Object_Layer1[i] != nullptr)
			delete Object_Layer1[i];
	}
}

void ChildScene::Update()
{

}

void ChildScene::AttachObject(GameObject* obj)
{
	if (dynamic_cast<Object1*>(obj) != nullptr)
	{
		Object_Layer1.push_back(dynamic_cast<Object1*>(obj));
	}
}

void ChildScene::OnRender()
{
	// child scene가 active 된 경우, mother scene을 먼저 드로우 해준 후 드로잉 한다.
	if (IsActive)
	{
		Mother->OnRender();
		Mother->RenderObject(1);
		Mother->RenderObject(2);
		Mother->RenderObject(3);

		switch (static_cast<ObjectID>(ID))
		{
		default:
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(static_cast<ResourceID>(ID)), 0, 0);
			break;
		}
	}
}

void ChildScene::OnEvent()
{
	DefaultKeyEvent();
	unsigned int size = Object_Layer1.size();
	if (IsActive)
	{
		for (int i = 0; i < size; i++)
		{
			Object_Layer1[i]->OnEvent();
		}
	}
}

