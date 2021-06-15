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
	// �̵� ����� �����.
	void MakeTranslate(Vector2 delta);
	// ȸ�� ����� �����.
	void MakeRotate(float angle, Vector2 axis);
	// ������ ����� �����.
	void MakeScale(Vector2 size, Vector2 center);
	
	// ��ȯ ����� �ʱ�ȭ�Ѵ�.
	void Identify();
	// ��ȯ ����� �����.
	void MakeTransformMatrix();

protected:
	D2D1::Matrix3x2F TranslateMatrix;
	D2D1::Matrix3x2F RotationMatrix;
	D2D1::Matrix3x2F ScaleMatrix;

	// ���� ��ȯ ���
	D2D1::Matrix3x2F TransformMatrix;
	// ���� ���
	D2D1::Matrix3x2F FlipMatrix;
};

