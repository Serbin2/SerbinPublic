#pragma once
#include "../Graphics/D2DMacros.h"
#include "../Util/Vector2.h"
#include "../Figure/RectVector.h"
#include "../Figure/CircleVector.h"

namespace Collision
{
	bool CheckRectangle(D2D1_RECT_U rect1, D2D1_RECT_U rect2);
	bool CheckRectangle(D2D1_RECT_F rect1, D2D1_RECT_F rect2);
	bool CheckRectangle(RECT rect1, RECT rect2);
	bool CheckRectangleOBB(RectVector rect1, RectVector rect2);
	bool CheckRectPoint(D2D1_RECT_F rect, Vector2 point);
	bool CheckCircle(int posx1, int posy1, int raidus1,	int posx2, int posy2, int raidus2);
	bool CheckCircle(CircleVector circle1, CircleVector circle2);
}

