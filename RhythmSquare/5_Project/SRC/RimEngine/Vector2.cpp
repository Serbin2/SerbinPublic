#include <math.h>
#include "Vector2.h"

Vector2::Vector2():
	X(0),Y(0)
{

}

Vector2::Vector2(float x, float y):
	X(x), Y(y)
{

}

Vector2 Vector2::operator+(const Vector2& V)
{
	return Vector2(X + V.X, Y + V.Y);
}

Vector2 Vector2::operator-(const Vector2& V)
{
	return Vector2(X - V.X, Y - V.Y);
}

Vector2 Vector2::operator*(const float& Val)
{
	return Vector2(X * Val, Y * Val);
}


float Vector2::Dot(const Vector2& V)
{
	return (X * V.X) + (Y * V.Y);
}

float Vector2::Distance()
{
	return sqrtf(X * X + Y * Y);
}
