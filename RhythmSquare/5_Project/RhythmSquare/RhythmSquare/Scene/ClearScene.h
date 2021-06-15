#pragma once
#include "ChildScene.h"

class ClearScene : public ChildScene
{
public:
	ClearScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother);
	virtual ~ClearScene();

public:
	virtual void OnEvent() override;
	virtual void OnRender() override;
	virtual void Sleep() override;
	virtual void DefaultKeyEvent() override;
private:

	OneGameData ClearInfo;
};

