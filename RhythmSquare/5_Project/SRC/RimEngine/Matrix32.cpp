#include "Matrix32.h"

Matrix32::Matrix32()
{
	_11 = _12 = _13 = _21 = _22 = _23 = 0;
}

Matrix32::Matrix32(float m11, float m12, float m13, float m21, float m22, float m23) :
	_11(m11), _12(m12), _13(m13), _21(m21), _22(m22), _23(m23)
{

}

Matrix32::~Matrix32()
{

}

Vector2 Matrix32::operator*(const Vector2& V)
{
	return Vector2(_11 * V.X + _12 * V.Y + _13, _21 * V.X + _22 * V.Y + _23);
}
