#pragma once
#include "Vector2.h"

class Matrix2x3
{
public:
	Matrix2x3();
	Matrix2x3(float m11, float m12, float m13,
			  float m21, float m22, float m23);
	~Matrix2x3();

public:
	static Matrix2x3 Transform(Vector2 vec);
	static Matrix2x3 Transform(float x, float y);

	static Matrix2x3 Scale(float x, float y);
	static Matrix2x3 Scale(float x, float y, Vector2 base);
	static Matrix2x3 Rocate(float theata, Vector2 base);

	//static Matrix2x3 Skew();
	Vector2 operator*(const Vector2& other);

public:
	float e11, e12, e13;
	float e21, e22, e23;	
};