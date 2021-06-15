#pragma once
#include "Scene.h"

class ChildScene : public Scene
{
public:
	ChildScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother);
	virtual ~ChildScene();

	virtual void Update();
	virtual void AttachObject(GameObject* obj);

	virtual void OnEvent() override;
	virtual void OnRender() override;

protected:
};