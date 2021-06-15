#pragma once
#include "ChildScene.h"
#include "../GameProcess/DefaultGameData.h"

class MusicSelectScene : public ChildScene
{
public:
	MusicSelectScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother);
	virtual ~MusicSelectScene();

	virtual void Awake();
	virtual void Sleep();
	virtual void AttachObject(GameObject* obj);


	virtual void OnEvent() override;
	virtual void OnRender() override;
	virtual void DefaultKeyEvent() override;
	virtual void Update() override;

private:
	Vector2 DivVec;

	// 이 정보는 GameManager로 부터 받는다.
	LobbyInfo* Info;
	MusicInfo MusicData;
	ImageSheet* Background;

	std::wstring WstScore;
	std::wstring WstCombo;
	std::wstring WstKill;
	std::wstring WstRate;
	std::wstring WstSpeed;
	std::wstring WstBPM;
};

class SliderScene : public ChildScene
{
public:
	SliderScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother);
	virtual ~SliderScene();

	virtual void Awake();
	virtual void Sleep();

	virtual void OnEvent() override;
	virtual void OnRender() override;
	virtual void Update() override;

private:
	Vector2 DivVec;
	Vector2 StartVec;
	Vector2 NameFreamVec;
	Vector2 SpeedFreamVec;
	Vector2 StarVec;
	Vector2 MusicCoverVec;
	Vector2 BestRankVec;
};