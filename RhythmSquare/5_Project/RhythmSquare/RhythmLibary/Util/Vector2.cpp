#include "pchLib.h"
#include "Vector2.h"

Vector2::Vector2()
	:x(0.0f), y(0.0f)
{
}

Vector2::Vector2(float value)
	: x(value), y(value)
{
}

Vector2::Vector2(float posx, float posy)
	: x(posx), y(posy)
{
}

Vector2::~Vector2()
{
}

bool Vector2::operator==(const Vector2& other)
{
	if (this->x == other.x && this->y == other.y)
		return true;
	else
		return false;
}

bool Vector2::operator!=(const Vector2& other)
{
	if (this->x != other.x || this->y != other.y)
		return true;
	else
		return false;
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2& other)
{
	this->x /= other.x;
	this->y /= other.y;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2& other)
{
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

Vector2& Vector2::operator=(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;
	return *this;
}

Vector2& Vector2::operator=(const POINT& other)
{
	this->x = static_cast<float>(other.x);
	this->y = static_cast<float>(other.y);
	return *this;

}

Vector2 Vector2::operator+(const Vector2& other)
{
	Vector2 vec;
	vec.x = this->x + other.x;
	vec.y = this->y + other.y;

	return vec;
}

Vector2 Vector2::operator-(const Vector2& other)
{
	Vector2 vec;
	vec.x = this->x - other.x;
	vec.y = this->y - other.y;

	return vec;
}

Vector2 Vector2::operator*(const float Scalar)
{
	Vector2 vec;
	vec.x = this->x * Scalar;
	vec.y = this->y * Scalar;
	return vec;
}

Vector2 Vector2::operator/(const float Scalar)
{
	Vector2 vec;
	vec.x = this->x / Scalar;
	vec.y = this->y / Scalar;
	return vec;
}

float Vector2::DotProduct(Vector2 vec1, Vector2 vec2)
{
	return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}

float Vector2::DotProduct(float power1, float power2, int theta)
{
	return power1 * power2 * cosf(theta);
}

float Vector2::Length(Vector2 vec)
{
	/// sqrtf 제곱근을 계산하는 함수.
	return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

Vector2 Vector2::Normalize(Vector2 vec)
{
	Vector2 NormalVec;
	float length = Length(vec);

	NormalVec.x = vec.x / length;
	NormalVec.y = vec.y / length;

	return NormalVec;
}

Vector2 Vector2::Normalize(Vector2 vec, int num)
{
	Vector2 NormalVec;
	float length = Length(vec) * num;

	NormalVec.x = vec.x / length;
	NormalVec.y = vec.y / length;

	return NormalVec;
}

POINT Vector2::VecToPoint(Vector2 vec)
{
	POINT Pos;
	Pos.x = static_cast<LONG>(vec.x);
	Pos.y = static_cast<LONG>(vec.y);

	return Pos;
}

void AlignRectangle(RECT* rt)
{
	int temp1, temp2;
	temp1 = rt->left;
	temp2 = rt->right;

	rt->left = min(temp1, temp2);
	rt->right = max(temp1, temp2);

	temp1 = rt->top;
	temp2 = rt->bottom;

	rt->top = min(temp1, temp2);
	rt->bottom = max(temp1, temp2);
}

bool ColisionAABB(RECT* rcA, RECT* rcB)
{
	if (rcA->right > rcB->left &&
		rcB->right > rcA->left &&
		rcA->bottom > rcB->top &&
		rcB->bottom > rcA->top)
		return true;
	return false;
}

POINT VecToPoint(Vector2 vec)
{
	POINT Pos;
	Pos.x = static_cast<LONG>(vec.x);
	Pos.y = static_cast<LONG>(vec.y);

	return Pos;
}

Vector2 PointToVec(POINT pt)
{
	Vector2 vec;
	vec.x = (static_cast<float>(pt.x));
	vec.y = (static_cast<float>(pt.y));

	return vec;
}
