#pragma once


class Vector2
{
public:
	float X;
	float Y;

	Vector2();
	Vector2(float x, float y);
	~Vector2() {};

	Vector2 operator+(const Vector2& V);
	Vector2 operator-(const Vector2& V);
	Vector2 operator*(const float& Val);


	float Dot(const Vector2& V);
	float Distance();
};

