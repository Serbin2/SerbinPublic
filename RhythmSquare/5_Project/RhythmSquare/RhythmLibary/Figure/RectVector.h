#pragma once
#include "../Util/Vector2.h"

class RectVector
{
public:
	RectVector();
	RectVector(Vector2 lt, Vector2 rt, Vector2 lb, Vector2 rb);
	~RectVector();

public:
	Vector2 LeftTop;
	Vector2 RightTop;
	Vector2 LeftBottom;
	Vector2 RightBottom;
};

