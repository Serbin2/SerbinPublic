#pragma once
#include "../Util/Vector2.h"

class LineVector
{
public:
	LineVector();
	LineVector(Vector2 src, Vector2 dst);
	~LineVector();

public:
	Vector2 Src;
	Vector2 Dst;
};

