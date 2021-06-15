#pragma once
#define _USE_MATH_DEFINES
#include<cstdio>
#include <windows.h>
#include<cmath>

#include <math.h> 

#define DGREE_RADINAN(_deg)	(M_PI*(_deg)/180.0f)
#define RADINAN_DGREE(_rad) (180 * (_rad) / (float)M_PI)


class Vector2
{
public:
	Vector2();
	Vector2(float value);
	Vector2(float posx, float posy);
	~Vector2();

	bool operator ==(const Vector2& other);
	bool operator !=(const Vector2& other);
	Vector2& operator +=(const Vector2& other);
	Vector2& operator -=(const Vector2& other);
	Vector2& operator /=(const Vector2& other);
	Vector2& operator*=(const Vector2& other);
	Vector2& operator=(const Vector2& other);
	Vector2& operator=(const POINT& other);	
	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator*(const float Scalar);
	Vector2 operator/(const float Scalar);

	// 벡터의 길이를 연산
	static float Length(Vector2 vec);

	// 백터를 1로 정규화 해주는 함수 임의의 방향 값만 원할 때 사용?
	static Vector2 Normalize(Vector2 vec);
	// 벡터를 1이 아닌 number값을 정규화 해주는 함수 임이의 길이까지 포함해서 받아올 때 사용?
	static Vector2 Normalize(Vector2 vec, int num);

	// 그냥 float를 POINT형으로 형변환 해주는 녀석
	static POINT VecToPoint(Vector2 vec);

	// 벡터의 내적
	static float DotProduct(Vector2 vec1, Vector2 vec2);
	static float DotProduct(float power1, float power2, int theta);

	///-> todo : 벡터의 외적
	// -> Vector2 에서는 3차원에서만 의미를 가진다. 외적은 결과 값으로 두 벡터와
	// 수직이 되는 벡터를 반환하기 때문이다.

public:
	float x;
	float y;
};
