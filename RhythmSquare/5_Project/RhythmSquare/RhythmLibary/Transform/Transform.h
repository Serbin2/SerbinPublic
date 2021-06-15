#pragma once
#include "../Graphics/D2DMacros.h"
#include "../Util/Vector2.h"
#include "../Util/Matrix2x3.h"

class Transform
{
public:
	Transform();
	virtual ~Transform();

public:
	// 이동 행렬을 만든다.
	void MakeTranslate(Vector2 delta);
	// 회전 행렬을 만든다.
	void MakeRotate(float angle, Vector2 axis);
	// 스케일 행렬을 만든다.
	void MakeScale(Vector2 size, Vector2 center);
	
	// 변환 행렬을 초기화한다.
	void Identify();
	// 변환 행렬을 만든다.
	void MakeTransformMatrix();

protected:
	D2D1::Matrix3x2F TranslateMatrix;
	D2D1::Matrix3x2F RotationMatrix;
	D2D1::Matrix3x2F ScaleMatrix;

	// 최종 변환 행렬
	D2D1::Matrix3x2F TransformMatrix;
	// 반전 행렬
	D2D1::Matrix3x2F FlipMatrix;
};

