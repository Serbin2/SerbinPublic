#pragma once
#include "../../RhythmLibary/GameObject/GameObject.h"
#include "../Interpace/IEventable.h"
#include "../Interpace/IRenderable.h"
#include "../Interpace/IAnimatable.h"

class Object2 : public GameObject, public IRenderable, public IAnimatable, public IEventable
{
public:
	Object2(std::string name, unsigned int id, unsigned int layer, Vector2 vec);
	Object2(std::string name, unsigned int id, unsigned int layer, Vector2 vec, int hp, int damege);
	virtual ~Object2();

protected:
	int HP;
	int Damege;	
};

