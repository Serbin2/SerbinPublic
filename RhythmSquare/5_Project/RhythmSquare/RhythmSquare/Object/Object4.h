#pragma once
#include "../../RhythmLibary/GameObject/GameObject.h"
#include "../Interpace/IRenderable.h"

class Object4 : public GameObject, public IRenderable
{
public:
	Object4();
	Object4(unsigned int id, Vector2 vec);
	Object4(unsigned int id, unsigned int layer, Vector2 vec);
	Object4(std::string name, unsigned int id, unsigned int layer, Vector2 vec);
	~Object4();

public:

private:

};

