#include "pchApp.h"
#include "Object1.h"

Object1::Object1()
	:GameObject(), Box({ 0, 0, 0, 0 })
{

}

Object1::Object1(unsigned int id, Vector2 vec)
	:GameObject(id, vec) , Box({ 0, 0, 0, 0 })
{
}

Object1::Object1(unsigned int id, unsigned int layer, Vector2 vec)
	: GameObject(id, layer, vec), Box({0, 0, 0, 0})
{
}

Object1::Object1(unsigned int id, unsigned int layer, Vector2 vec, D2D1_RECT_F box)
	:GameObject(id, layer, vec) , Box({ vec.x + box.left, vec.y + box.top, vec.x + box.right, vec.y + box.bottom})
{
	CenterPos.x = vec.x + box.right / 2;
	CenterPos.y = vec.y + box.bottom / 2;
}

Object1::Object1(std::string name, unsigned int id, unsigned int layer, Vector2 vec)
	:GameObject(name, id, layer, vec)
{
}

Object1::~Object1()
{

}