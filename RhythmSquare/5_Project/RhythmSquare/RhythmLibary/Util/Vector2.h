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

	// ������ ���̸� ����
	static float Length(Vector2 vec);

	// ���͸� 1�� ����ȭ ���ִ� �Լ� ������ ���� ���� ���� �� ���?
	static Vector2 Normalize(Vector2 vec);
	// ���͸� 1�� �ƴ� number���� ����ȭ ���ִ� �Լ� ������ ���̱��� �����ؼ� �޾ƿ� �� ���?
	static Vector2 Normalize(Vector2 vec, int num);

	// �׳� float�� POINT������ ����ȯ ���ִ� �༮
	static POINT VecToPoint(Vector2 vec);

	// ������ ����
	static float DotProduct(Vector2 vec1, Vector2 vec2);
	static float DotProduct(float power1, float power2, int theta);

	///-> todo : ������ ����
	// -> Vector2 ������ 3���������� �ǹ̸� ������. ������ ��� ������ �� ���Ϳ�
	// ������ �Ǵ� ���͸� ��ȯ�ϱ� �����̴�.

public:
	float x;
	float y;
};
