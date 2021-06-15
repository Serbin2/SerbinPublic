#include "pchLib.h"
#include "Transform.h"

Transform::Transform()
	:FlipMatrix(D2D1::Matrix3x2F(-1, 0, 0, 1, 0, 0))
{

}

Transform::~Transform()
{

}

void Transform::MakeTranslate(Vector2 delta)
{
	TranslateMatrix = D2D1::Matrix3x2F::Translation(delta.x, delta.y);
}

void Transform::MakeRotate(float angle, Vector2 axis)
{
	RotationMatrix = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(axis.x, axis.y));
}

void Transform::MakeScale(Vector2 size, Vector2 center)
{
	ScaleMatrix = D2D1::Matrix3x2F::Scale(size.x, size.y, D2D1::Point2F(center.x, center.y));
}

void Transform::Identify()
{
	TranslateMatrix = D2D1::Matrix3x2F::Identity();
	RotationMatrix = D2D1::Matrix3x2F::Identity();
	ScaleMatrix = D2D1::Matrix3x2F::Identity();
	TransformMatrix = D2D1::Matrix3x2F::Identity();
}

void Transform::MakeTransformMatrix()
{
	// 최종적인 변환행렬을 만들어준다.
	TransformMatrix = ScaleMatrix * RotationMatrix * TranslateMatrix;
}