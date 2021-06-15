#pragma once
#include "Vector2.h"

class CircleCollision
{
private:
	Vector2 Pos;
	float Rad;
	bool isCollision;
public:
	CircleCollision(float x, float y, float radius);
	CircleCollision(Vector2 V, float radius);
	~CircleCollision();

	bool OnCollision(CircleCollision& Circle);

};

