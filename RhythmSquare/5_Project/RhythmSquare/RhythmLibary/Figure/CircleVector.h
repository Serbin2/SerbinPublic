#pragma once
#include "../Util/Vector2.h"

class CircleVector
{
public:
	CircleVector();
	CircleVector(Vector2 center, float radius);
	~CircleVector();

public:
	Vector2 Center;
	float Radius;
};

