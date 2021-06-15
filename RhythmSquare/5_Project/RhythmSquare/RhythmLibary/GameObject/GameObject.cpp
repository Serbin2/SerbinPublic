#include "pchLib.h"
#include "GameObject.h"

GameObject::GameObject()
	:Transform(), Name(""), ID(0), Layer(-1), World_Position(0, 0)
{
}

GameObject::GameObject(unsigned int id, Vector2 vec)
	: Transform(), Name(""), ID(id), Layer(-1), World_Position(vec)
{
}

GameObject::GameObject(unsigned int id, unsigned int layer, Vector2 vec)
	: Transform(), Name(""), ID(id), Layer(layer), World_Position(vec)
{
}

GameObject::GameObject(std::string name, unsigned int id, unsigned int layer, Vector2 vec)
	: Transform(), Name(name), ID(id), Layer(layer), World_Position(vec)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}
