#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include "Vector2.h"

class Matrix32
{
public:
	float _11, _12, _13;
	float _21, _22, _23;

	Matrix32();
	Matrix32(float m11, float m12, float m13, float m21, float m22, float m23);
	~Matrix32();



	Vector2 operator*(const Vector2& V);

};

