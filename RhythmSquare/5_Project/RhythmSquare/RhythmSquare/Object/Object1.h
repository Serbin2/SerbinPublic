#pragma once
#include "../../RhythmLibary/GameObject/GameObject.h"
#include "../Interpace/IRenderable.h"
#include "../Interpace/IEventable.h"

class Object1 : public GameObject, public IRenderable, public IEventable
{
public:
	Object1();
	Object1(unsigned int id, Vector2 vec);
	Object1(unsigned int id, unsigned int layer, Vector2 vec);
	Object1(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box);
	Object1(std::string name, unsigned int id, unsigned int layer, Vector2 vec);
	virtual ~Object1();

public:
	void SetBox(D2D1_RECT_F box) { Box = box; }	
	void AddBox(D2D1_RECT_F box) {
		Box.left += box.left; Box.top += box.top;
		Box.right += box.right; 	Box.bottom += box.bottom; }
	D2D1_RECT_F GetBox() const { return Box; }
	void AddBox(Vector2 vec) {
		Box.left += vec.x; Box.top += vec.y;
		Box.right += vec.x; 	Box.bottom += vec.y;
	}
	void AddCenter(Vector2 vec) { CenterPos.x += vec.x; CenterPos.y += vec.y; };


protected:
	D2D1_RECT_F Box;
	Vector2 CenterPos;
};
