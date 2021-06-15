#pragma once
#include"MainScene.h"
#include "../Monster/Monster.h"

class InGameScene : public MainScene
{
public:
	InGameScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, bool active);
	virtual ~InGameScene();

public:
	virtual void Awake() override;
	virtual void OnEvent() override;
	virtual void OnRender() override;
	virtual void Continue() override;
	virtual void Restart() override;
	virtual void Update();
	void DefaultKeyEvent();

private:
	Vector2 MonsterVec;
	Vector2 CharacterVec;
	Vector2 SquareVec;

	Player* m_Player;


	float ContinueTime;
	bool IsContinue;
};
