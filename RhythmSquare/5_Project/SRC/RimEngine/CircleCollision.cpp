#include "CircleCollision.h"

CircleCollision::CircleCollision(float x, float y, float radius) :
	Pos(Vector2{ x,y }), Rad(radius), isCollision(false)
{

}

CircleCollision::CircleCollision(Vector2 V, float radius) :
	Pos(V), Rad(radius), isCollision(false)
{

}

CircleCollision::~CircleCollision()
{
	
}

bool CircleCollision::OnCollision(CircleCollision& Circle)
{
	float dist = (Pos - Circle.Pos).Distance();
	if (Rad + Circle.Rad > dist)
	{
		isCollision = true;
		Circle.isCollision = true;
		return true;
	}
	isCollision = false;
	Circle.isCollision = false;
	return false;
}
