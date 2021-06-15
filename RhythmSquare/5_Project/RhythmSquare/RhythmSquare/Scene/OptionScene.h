#pragma once
#include "ChildScene.h"
class OptionScene : public ChildScene
{
public:
	OptionScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother);
	virtual ~OptionScene();
	
public:
	virtual void Awake();
	virtual void Sleep();
	//virtual void AttachObject(GameObject* obj);

	virtual void OnEvent() override;
	virtual void OnRender() override;
	virtual void DefaultKeyEvent() override;
	virtual void Update() override;

private:
	// 이 정보는 GameManager 로 부터 받는다.
	//OptionInfo* Info;
};

class OptionSound : public ChildScene
{
public:
	OptionSound(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother);
	virtual ~OptionSound();

public:
	virtual void Awake();
	virtual void Sleep();

	virtual void OnEvent() override;
	virtual void OnRender() override;
	virtual void DefaultKeyEvent() override;
	virtual void Update() override;

};

class OptionSettiong : public ChildScene
{
public:
	OptionSettiong(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother);
	virtual ~OptionSettiong();

public:
	virtual void Awake();
	virtual void Sleep();
	virtual void OnEvent() override;

	virtual void OnRender() override;
	virtual void DefaultKeyEvent() override;

private:
	std::wstring WstJudgment;
};

class OptionControl : public ChildScene
{
public:
	OptionControl(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, Scene* mother);
	virtual ~OptionControl();

public:
	virtual void Awake();
	virtual void Sleep();
	virtual void AttachObject(GameObject* obj);

	virtual void OnRender() override;
	virtual void DefaultKeyEvent() override;

private:
};