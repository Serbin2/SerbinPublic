#pragma once
#include <list>	
#include <vector>
#include "../Object/ObjectDef.h"
#include "../Object/Object1.h"
#include "../Object/Object2.h"
#include "../Object/Object3.h"
#include "../Object/Object4.h"
#include "../../RhythmLibary/Graphics/D2DImage.h"
#include "../../RhythmLibary/GameObject/GameObject.h"
#include "../Input/Button.h"

class Scene : public Object1
{
public:
	Scene(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box, bool active);
	virtual ~Scene();

public:

	Scene* GetMother();
	Scene** GetNext();
	bool CheckActive();

	virtual void Awake();
	virtual void Continue();
	virtual void Sleep();
	virtual void Pause();
	virtual void OffPause();
	virtual void Restart();

	virtual void AttachObject(GameObject* obj);
	virtual void RenderObject(unsigned int Layer);
	virtual void DefaultKeyEvent();

	/// Zoop Up À§ÇØ ¸¸µê.
	virtual void ObjectIdentify();
	virtual void ObjectMakeTranslate(Vector2 delta);
	virtual void ObjectMakeScale(Vector2 scale, Vector2 center);
	virtual void ObjectRocate(float angle, Vector2 axis);
	virtual void Object_MakeTdransform();

	virtual void OnRender() override;
	virtual void OnEvent() override;
	virtual void Update() override;


protected:
	std::vector<Object1*> Object_Layer1;
	Scene* Mother;
	Scene** Next;
	Flag* Alram;
	bool IsActive;
	bool IsPause;
};



