#pragma once
#include "../Util/Vector2.h"

class TriangleVector
{
public:
	TriangleVector();
	TriangleVector(Vector2 left, Vector2 center, Vector2 right);
	~TriangleVector();

public:
	Vector2 Left;
	Vector2 Center;
	Vector2 Right;
};

