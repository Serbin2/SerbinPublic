#include "GH.h"
#include "BoxObject.h"
#include <math.h>

BoxObject::BoxObject() :
	m_Position({ 0,0 }), m_V1({ 0,0 }), m_V2({ 0,0 }), m_V3({ 0,0 }), m_V4({ 0,0 })
{

}

BoxObject::BoxObject(float left, float top, float right, float bottom) :
	m_V1({ left,top }), m_V2({ right,top }), m_V3({ right,bottom }), m_V4({ left,bottom })
{
	m_Position = Vector2{ (left + right) / 2 , (top + bottom) / 2 };
}

BoxObject::~BoxObject()
{

}

void BoxObject::Draw()
{
	if (m_Collision)
	{
		RimEngine::GetInstance()->DrawRectangle(m_V1, m_V2, m_V3, m_V4, RGB(0, 255, 0));
	}
	else
	{
		RimEngine::GetInstance()->DrawRectangle(m_V1, m_V2, m_V3, m_V4, RGB(255, 0, 0));
	}
}

void BoxObject::CollisionCheck(BoxObject other)
{
	Vector2 tmp = m_V1 - m_V2; // 한 변의 벡터

	// 내 박스의 내적
	float m1 = tmp.Dot(m_V1); 
	float m2 = tmp.Dot(m_V2);

	// 상대 박스의 내적
	float o1 = tmp.Dot(other.m_V1);
	float o2 = tmp.Dot(other.m_V2);
	float o3 = tmp.Dot(other.m_V3);
	float o4 = tmp.Dot(other.m_V4);

	float mMax = fmaxf(m1, m2);
	float mMin = fminf(m1, m2);

	float oMax = fmaxf(fmaxf(fmaxf(o1, o2), o3), o4);
	float oMin = fminf(fminf(fminf(o1, o2), o3), o4);




}
