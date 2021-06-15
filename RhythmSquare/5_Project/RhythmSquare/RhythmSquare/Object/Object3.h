#pragma once
#include "../../RhythmLibary/GameObject/GameObject.h"
#include "../Interpace/IRenderable.h"

class Object3 : public GameObject, public IRenderable
{
public:
	Object3();
	Object3(unsigned int id, Vector2 vec);
	Object3(unsigned int id, unsigned int layer, Vector2 vec);
	Object3(std::string name, unsigned int id, unsigned int layer, Vector2 vec);
	~Object3();

public:

private:

};

