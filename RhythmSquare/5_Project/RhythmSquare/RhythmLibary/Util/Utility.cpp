#include "pchLib.h"
#include "Utility.h"

bool Collision::CheckRectangle(D2D1_RECT_U rect1, D2D1_RECT_U rect2)
{
	if (rect1.left < rect2.right && rect2.left < rect2.right &&
		rect1.top < rect2.bottom && rect2.top < rect1.bottom)
	{
		return true;
	}
	else
		return false;
}

bool Collision::CheckRectangle(D2D1_RECT_F rect1, D2D1_RECT_F rect2)
{
	if ((rect1.left < rect2.right && rect2.left < rect2.right) &&
		(rect1.top < rect2.bottom && rect2.top < rect1.bottom))
	{
		return true;
	}
	else
		return false;
}

bool Collision::CheckRectangle(RECT rect1, RECT rect2)
{
	if (rect1.left < rect2.right && rect2.left < rect2.right &&
		rect1.top < rect2.bottom && rect2.top < rect1.bottom)
	{
		return true;
	}
	else
		return false;
}

bool Collision::CheckRectangleOBB(RectVector rect1, RectVector rect2)
{
	Vector2 line;
	float p1[2] = { 0.0f, };
	float p2[4] = { 0.0f, };

	float rect1Min;
	float rect1Max;
	float rect2Min;
	float rect2Max;

	// 1. lt - rt line check
	line = rect1.LeftTop - rect1.RightTop;

	p1[0] = Vector2::DotProduct(line, rect1.LeftTop);
	p1[1] = Vector2::DotProduct(line, rect1.RightTop);

	rect1Min = fmin(p1[0], p1[1]);
	rect1Max = fmax(p1[0], p1[1]);

	p2[0] = Vector2::DotProduct(line, rect2.LeftTop);
	p2[1] = Vector2::DotProduct(line, rect2.LeftBottom);
	p2[2] = Vector2::DotProduct(line, rect2.RightTop);
	p2[3] = Vector2::DotProduct(line, rect2.RightBottom);

	rect2Min = fmin(fmin(fmin(p2[0], p2[1]), p2[2]), p2[3]);
	rect2Max = fmax(fmax(fmax(p2[0], p2[1]), p2[2]), p2[3]);

	if (rect1Min < rect2Max && rect2Min < rect1Max)
		return false;

	// 1. lt - rt line check
	line = rect1.LeftTop - rect1.RightTop;

	p1[0] = Vector2::DotProduct(line, rect1.LeftTop);
	p1[1] = Vector2::DotProduct(line, rect1.RightTop);

	rect1Min = fmin(p1[0], p1[1]);
	rect1Max = fmax(p1[0], p1[1]);

	p2[0] = Vector2::DotProduct(line, rect2.LeftTop);
	p2[1] = Vector2::DotProduct(line, rect2.LeftBottom);
	p2[2] = Vector2::DotProduct(line, rect2.RightTop);
	p2[3] = Vector2::DotProduct(line, rect2.RightBottom);

	rect2Min = fmin(fmin(fmin(p2[0], p2[1]), p2[2]), p2[3]);
	rect2Max = fmax(fmax(fmax(p2[0], p2[1]), p2[2]), p2[3]);

	if (rect1Min > rect2Max && rect2Min > rect1Max)
		return false;

	// 2. lt - lb line check
	line = rect1.LeftTop - rect1.LeftBottom;

	p1[0] = Vector2::DotProduct(line, rect1.LeftTop);
	p1[1] = Vector2::DotProduct(line, rect1.LeftBottom);

	rect1Min = fmin(p1[0], p1[1]);
	rect1Max = fmax(p1[0], p1[1]);

	p2[0] = Vector2::DotProduct(line, rect2.LeftTop);
	p2[1] = Vector2::DotProduct(line, rect2.LeftBottom);
	p2[2] = Vector2::DotProduct(line, rect2.RightTop);
	p2[3] = Vector2::DotProduct(line, rect2.RightBottom);

	rect2Min = fmin(fmin(fmin(p2[0], p2[1]), p2[2]), p2[3]);
	rect2Max = fmax(fmax(fmax(p2[0], p2[1]), p2[2]), p2[3]);

	if (rect1Min > rect2Max && rect2Min > rect1Max)
		return false;

	// 3. rt - rb line check
	line = rect1.LeftBottom - rect1.RightBottom;

	p1[0] = Vector2::DotProduct(line, rect1.RightTop);
	p1[1] = Vector2::DotProduct(line, rect1.RightBottom);

	rect1Min = fmin(p1[0], p1[1]);
	rect1Max = fmax(p1[0], p1[1]);

	p2[0] = Vector2::DotProduct(line, rect2.LeftTop);
	p2[1] = Vector2::DotProduct(line, rect2.LeftBottom);
	p2[2] = Vector2::DotProduct(line, rect2.RightTop);
	p2[3] = Vector2::DotProduct(line, rect2.RightBottom);

	rect2Min = fmin(fmin(fmin(p2[0], p2[1]), p2[2]), p2[3]);
	rect2Max = fmax(fmax(fmax(p2[0], p2[1]), p2[2]), p2[3]);

	if (rect1Min > rect2Max && rect2Min > rect1Max)
		return false;

	// 4. lb - rb line check
	line = rect1.LeftBottom - rect1.RightBottom;

	p1[0] = Vector2::DotProduct(line, rect1.LeftBottom);
	p1[1] = Vector2::DotProduct(line, rect1.RightBottom);

	rect1Min = fmin(p1[0], p1[1]);
	rect1Max = fmax(p1[0], p1[1]);

	p2[0] = Vector2::DotProduct(line, rect2.LeftTop);
	p2[1] = Vector2::DotProduct(line, rect2.LeftBottom);
	p2[2] = Vector2::DotProduct(line, rect2.RightTop);
	p2[3] = Vector2::DotProduct(line, rect2.RightBottom);

	rect2Min = fmin(fmin(fmin(p2[0], p2[1]), p2[2]), p2[3]);
	rect2Max = fmax(fmax(fmax(p2[0], p2[1]), p2[2]), p2[3]);

	if (rect1Min > rect2Max && rect2Min > rect1Max)
		return false;

	return true;
}

bool Collision::CheckRectPoint(D2D1_RECT_F rect, Vector2 point)
{
	if (point.x < 0 && point.y < 0)
		return false;
	if (rect.left <= point.x && rect.right >= point.x &&
		rect.top <= point.y && rect.bottom >= point.y)
	{
		return true;
	}
		return false;
}

bool Collision::CheckCircle(int posx1, int posy1, int radius1, int posx2, int posy2, int radius2)
{
	/// sqrtf 제곱근을 계산하는 함수.
	float dis1 = posx1 - posx2;
	float disy = posy1 - posy2;

	float distance = sqrtf(dis1 * dis1 + disy * disy);

	if (distance > (radius1 + radius2))
		return false;
	if (distance <= (radius1 + radius2))
		return true;

	return false;
}

bool Collision::CheckCircle(CircleVector circle1, CircleVector circle2)
{
	float disx = circle1.Center.x - circle2.Center.x;
	float disy = circle1.Center.y - circle2.Center.y;

	float distance = sqrtf(disx * disx + disy * disy);

	if (distance > (circle1.Radius + circle2.Radius))
		return false;
	if (distance <= (circle1.Radius + circle2.Radius))
		return true;

	return false;
}
