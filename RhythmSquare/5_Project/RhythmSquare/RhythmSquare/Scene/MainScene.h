#pragma once
#include "Scene.h"
class MainScene : public Scene
{
public:
	MainScene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, bool active);
	virtual ~MainScene();

public:
	void Update();
	void AttachObject(GameObject* obj);
	void RenderObject(unsigned int Layer);

	virtual void Awake() override;
	virtual void OnEvent() override;
	virtual void OnRender() override;

protected:
	std::vector<Object2*> Object_Layer2;
	std::vector<Object3*> Object_Layer3;
};
