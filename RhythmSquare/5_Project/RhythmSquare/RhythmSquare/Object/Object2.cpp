#include "pchApp.h"
#include "Object2.h"

Object2::Object2(std::string name, unsigned int id, unsigned int layer, Vector2 vec)
	: GameObject(name, id, layer, vec), HP(0), Damege(0)
{
}

Object2::Object2(std::string name, unsigned int id, unsigned int layer, Vector2 vec, int hp, int damege)
	:GameObject(name, id, layer, vec), HP(hp), Damege(damege)
{
}

Object2::~Object2()
{

}
