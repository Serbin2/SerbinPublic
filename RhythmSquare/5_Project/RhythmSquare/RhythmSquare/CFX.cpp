#include "pchApp.h"
#include "CFX.h"
#include "Resource/ResourceManager.h"

CFX::CFX(int count, Vector2 vec, ResourceID id, bool Animated, Vector2 mov) :Object2("fx", 98, 2, vec)
{
	OnRemove = count;
	RemoveCount = 0;
	m_mov = mov;
	if (Animated)
	{
		FXSheet = ResourceManager::GetInstance().GetMotionSheet(id);
		FXSprite = nullptr;
		isAnimated = true;
	}
	else
	{
		FXSprite = ResourceManager::GetInstance().GetImageSheet(id);
		FXSheet = nullptr;
		isAnimated = false;
	}
}

CFX::~CFX()
{

}

bool CFX::Render()
{
	OnRender();
	RemoveCount++;
	if (RemoveCount >= OnRemove)
	{
		return false;
	}
	return true;
}

void CFX::Animate()
{
	Identify();
	MakeTranslate(World_Position);
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().AnimateImage(FXSheet, 0, 0, 1.0, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, 0);
	Identify();
}

void CFX::OnRender()
{
	if (isAnimated)
	{
		Animate();
	}
	else
	{
		SetPositionW({ World_Position.x + m_mov.x, World_Position.y + m_mov.y });
		Identify();
		MakeTranslate(World_Position);
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(FXSprite, 0, 0);
		Identify();
	}
}

void CFX::OnEvent()
{

}
