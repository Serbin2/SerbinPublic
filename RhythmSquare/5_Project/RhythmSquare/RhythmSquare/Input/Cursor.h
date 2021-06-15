#pragma once

#include "../Interpace/IRenderable.h"
#include "../../RhythmLibary/GameObject/GameObject.h"
#include "../../RhythmLibary/Key/Key.h"
#include "../../RhythmLibary/Graphics/D2DImage.h"
#include "../../RhythmLibary/Graphics/D2DGraphics.h"
#include "../../RhythmLibary/Util/Singleton.h"

class Cursor : public Singleton<Cursor>, public GameObject
{
public:
	Cursor();
	~Cursor();

public:
	void OnRender();	
	virtual void Update() override;
	Vector2 GetCursorEngineDpiPos();
	void OnResize(int width, int height);
private:


	float _ratioX;
	float _ratioY;
	POINT _cursorPos;
	RECT _clientRect;

};

