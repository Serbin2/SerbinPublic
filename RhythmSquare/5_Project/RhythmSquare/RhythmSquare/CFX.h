#pragma once
#include "../RhythmLibary/Util/Frame.h"
#include "Object/Object2.h"

class CFX : public Object2
{
public:
	CFX(int count, Vector2 vec, ResourceID id, bool Animated, Vector2 mov);
	~CFX();


	bool Render();
	virtual void Animate()  override;;
	virtual void OnRender()  override;;
	virtual void OnEvent() override;

private:

	ImageSheet* FXSprite;
	MotionSheet* FXSheet;
	int RemoveCount;
	int OnRemove;
	bool isAnimated;
	Vector2 m_mov;

};

