#pragma once
#include "ChildScene.h"

class LoseScene : public ChildScene
{
public:
	LoseScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother);
	virtual ~LoseScene();

public:
	virtual void OnEvent() override;
	virtual void OnRender() override;
	virtual void Sleep() override;
	virtual void DefaultKeyEvent() override;
private:
};

