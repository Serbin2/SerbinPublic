#pragma once
#include "ChildScene.h"
#include "../Object/UI_SIZE_Def.h"

class PauseScene : public ChildScene
{
public:
	PauseScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother);
	virtual ~PauseScene();

public:
	virtual void OnRender() override;
	virtual void Sleep()override;
	virtual void OnEvent() override;
	virtual void DefaultKeyEvent() override;
};

