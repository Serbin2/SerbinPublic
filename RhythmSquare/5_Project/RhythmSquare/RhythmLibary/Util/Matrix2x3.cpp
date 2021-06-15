#include "pchLib.h"
#include "Matrix2x3.h"
#include <math.h> 

#define DGREE_RADINAN(_deg)	(M_PI*(_deg)/180.0f)


Matrix2x3::Matrix2x3()
	:e11(0.0f), e12(0.0f), e13(0.0f), e21(0.0f), e22(0.0f), e23(0.0f)
{
}

Matrix2x3::Matrix2x3(float m11, float m12, float m13, float m21, float m22, float m23)
	: e11(m11), e12(m12), e13(m13), e21(m21), e22(m22), e23(m23)
{
}

Matrix2x3::~Matrix2x3()
{
}

Matrix2x3 Matrix2x3::Transform(Vector2 vec)
{
	Matrix2x3 transform(1, 0, vec.x,
						0, 1, vec.y);
	return transform;
}

Matrix2x3 Matrix2x3::Transform(float x, float y)
{
	Matrix2x3 transform(1, 0, x,
						0, 1, y);
	return transform;
}

Matrix2x3 Matrix2x3::Scale(float x, float y)
{
	Matrix2x3 scale(x, 0, 0,
					0, y, 0);
	return scale;
}

Matrix2x3 Matrix2x3::Scale(float x, float y, Vector2 base)
{	
	/// 일단 점을 크게 한 후 내가 이동할 만큼 빼줌.
	Matrix2x3 scale(x, 0, base.x + (-base.x * x),
					0, y, base.y + (-base.y * y));
	return scale;
}

Matrix2x3 Matrix2x3::Rocate(float theata, Vector2 base)
{
	float radian;
	radian = DGREE_RADINAN(theata);
	Matrix2x3 rocate(cosf(radian) , sinf(radian), sinf(radian) * base.y + base.x * (cosf(radian) - 1),
					-sinf(radian), cosf(radian), -sinf(radian) * base.x + base.y * (cosf(radian) - 1));
	return rocate;
}

Vector2 Matrix2x3::operator*(const Vector2& other)
{
	Vector2 vec;	
	vec.x = (this->e11 * other.x) + (this->e12 * other.y) + this->e13;
	vec.y = (this->e21 * other.x) + (this->e22 * other.y) + this->e23;
	return vec;
}
