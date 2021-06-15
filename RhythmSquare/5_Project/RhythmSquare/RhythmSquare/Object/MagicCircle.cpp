#include "pchApp.h"
#include "MagicCircle.h"
#include "../Resource/ResourceManager.h"

MagicCircle::MagicCircle()
	: GameObject(0, 2, Vector2(0, 0))
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Line[i][j] = false;
		}
	}
}

MagicCircle::~MagicCircle()
{
}

void MagicCircle::OnRender()
{
	DrawCircle();

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Line[i][j])
			{
				DrawMagicLine(i, j, true);
			}
		}
	}
	DrawNumber();
}

void MagicCircle::OnRender(bool miss, bool fever)
{
	DrawCircle(miss, fever);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Line[i][j])
			{
				DrawMagicLine(i, j, true);
			}
		}
	}
	if (miss)
	{
		DrawMissNumber();
	}
	else
	{
		DrawNumber();
	}
}

void MagicCircle::BaseFourVecRender()
{
	float angle;
	float scale;
	Vector2 distanceVec(0, 0);
	float distance;

	// four to six
	distanceVec = Vector2(SixVec) - FourVec;
	angle = RADINAN_DGREE(atan2f(distanceVec.y, distanceVec.x));
	distance = sqrtf(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);
	scale = distance / 712;

	MakeScale(Vector2(scale, 1.f), Vector2(0, 23.f));
	MakeTranslate(FourVec);
	MakeRotate(angle, Vector2(0, 0));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_BAR), 0, 0);
	Identify();

	// four to seven
	distanceVec = Vector2(SevenVec) - FourVec;
	angle = RADINAN_DGREE(atan2f(distanceVec.y, distanceVec.x));
	distance = sqrtf(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);

	scale = distance / 712;

	MakeScale(Vector2(scale, 1.f), Vector2(0, 0));
	MakeTranslate(FourVec);
	MakeRotate(angle, Vector2(0, 0));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_BAR), 0, 0);
	Identify();

	// four to eight
	distanceVec = Vector2(EightVec) - FourVec;
	angle = RADINAN_DGREE(atan2f(distanceVec.y, distanceVec.x));
	distance = sqrtf(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);

	scale = distance / 712;

	MakeScale(Vector2(scale, 1.f), Vector2(0, 0));
	MakeTranslate(FourVec);
	MakeRotate(angle, Vector2(0, 0));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_BAR), 0, 0);
	Identify();

	// four to nine
	distanceVec = Vector2(NineVec) - FourVec;
	angle = RADINAN_DGREE(atan2f(distanceVec.y, distanceVec.x));
	distance = sqrtf(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);

	scale = distance / 712;

	MakeScale(Vector2(scale, 1.f), Vector2(0, 0));
	MakeTranslate(FourVec);
	MakeRotate(angle, Vector2(0, 0));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_BAR), 0, 0);
	Identify();

	// four to one
	distanceVec = Vector2(OneVec) - FourVec;
	angle = RADINAN_DGREE(atan2f(distanceVec.y, distanceVec.x));
	distance = sqrtf(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);

	scale = distance / 712;

	MakeScale(Vector2(scale, 1.f), Vector2(0, 0));
	MakeTranslate(FourVec);
	MakeRotate(angle, Vector2(0, 0));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_BAR), 0, 0);
	Identify();

	// four to two
	distanceVec = Vector2(TwoVec) - FourVec;
	angle = RADINAN_DGREE(atan2f(distanceVec.y, distanceVec.x));
	distance = sqrtf(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);

	scale = distance / 712;

	MakeTranslate(FourVec);
	MakeRotate(angle, Vector2(0, 0));
	MakeScale(Vector2(scale, 1.f), Vector2(0, 0));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_BAR), 0, 0);
	Identify();

	// four to three
	distanceVec = Vector2(ThreeVec) - FourVec;
	angle = RADINAN_DGREE(atan2f(distanceVec.y, distanceVec.x));
	distance = sqrtf(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);

	scale = distance / 712;

	MakeTranslate(FourVec);
	MakeRotate(angle, Vector2(0, 0));
	MakeScale(Vector2(scale, 1.f), Vector2(0, 0));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_BAR), 0, 0);
	Identify();
}

void MagicCircle::SettingTRS(Vector2 Src, Vector2 Dst)
{
	float angle;
	float scale;
	Vector2 distanceVec(0, 0);
	float distance;

	Identify();
	distanceVec = Dst - Src;
	angle = RADINAN_DGREE(atan2f(distanceVec.y, distanceVec.x));
	distance = sqrtf(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);
	scale = distance / 712;
	MakeTranslate(Src);
	MakeScale(Vector2(scale, 1.f), Vector2(0, 23.f));
	MakeRotate(angle, Vector2(0, 23.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
}


void MagicCircle::DrawMagicLine(int src, int dst, bool light)
{
	Vector2 srcV;
	Vector2 dstV;
	switch (src)
	{
	default:
	case 0:
		srcV = OneVec;
		break;
	case 1:
		srcV = TwoVec;
		break;
	case 2:
		srcV = ThreeVec;
		break;
	case 3:
		srcV = FourVec;
		break;
	case 4:
		srcV = SixVec;
		break;
	case 5:
		srcV = SevenVec;
		break;
	case 6:
		srcV = EightVec;
		break;
	case 7:
		srcV = NineVec;
		break;
	}
	switch (dst)
	{
	default:
	case 0:
		dstV = OneVec;
		break;
	case 1:
		dstV = TwoVec;
		break;
	case 2:
		dstV = ThreeVec;
		break;
	case 3:
		dstV = FourVec;
		break;
	case 4:
		dstV = SixVec;
		break;
	case 5:
		dstV = SevenVec;
		break;
	case 6:
		dstV = EightVec;
		break;
	case 7:
		dstV = NineVec;
		break;
	}

	SettingTRS(srcV, dstV);

	if (light)
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_BAR_LIGHT), 0, 0);
	else
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_BAR), 0, 0);
	Identify();
}

void MagicCircle::DrawCircle()
{
	/// 1. first, 
	Identify();
	// 0. x 스케일을 구한다.
	Identify();
	MakeTranslate(Vector2(720, 60));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_SQUARE), 0, 0);
	Identify();

	MakeTranslate(Vector2(810.f, 190.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE), 0, 0);
	Identify();
}

void MagicCircle::DrawCircle(bool miss, bool fever)
{
	/// 1. first, 
	Identify();
	// 0. x 스케일을 구한다.
	Identify();
	MakeTranslate(Vector2(720, 60));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	if (miss)
	{
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_SQUARE_MISS), 0, 0);
	}
	else
	{
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_SQUARE), 0, 0);
	}
	Identify();

	MakeTranslate(Vector2(810.f, 190.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	if (miss)
	{
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE_BLACK), 0, 0);
	}
	else
	{
		if (fever)
		{
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE_LIGHT), 0, 0);
		}
		else
		{
			D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE), 0, 0);
		}
	}
	Identify();
}

void MagicCircle::DrawNumber()
{
	// num 1
	MakeTranslate(Vector2(958, 844));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_1), 0, 0);
	Identify();
	// num2
	MakeTranslate(Vector2(1210.f, 944.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_2), 0, 0);
	Identify();
	// num3
	MakeTranslate(Vector2(1462.f, 844.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_3), 0, 0);
	Identify();
	// num4
	MakeTranslate(Vector2(856.f, 590.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_4), 0, 0);
	Identify();
	// num6
	MakeTranslate(Vector2(1564.f, 590.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_6), 0, 0);
	Identify();
	// num7
	MakeTranslate(Vector2(958.f, 340.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_7), 0, 0);
	Identify();
	// num8
	MakeTranslate(Vector2(1210.f, 236.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_8), 0, 0);
	Identify();
	// num9
	MakeTranslate(Vector2(1462.f, 340.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_9), 0, 0);
	Identify();


}

void MagicCircle::DrawMissNumber()
{
	// num 1
	MakeTranslate(Vector2(958, 844));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_1_BLACK), 0, 0);
	Identify();
	// num2
	MakeTranslate(Vector2(1210.f, 944.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_2_BLACK), 0, 0);
	Identify();
	// num3
	MakeTranslate(Vector2(1462.f, 844.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_3_BLACK), 0, 0);
	Identify();
	// num4
	MakeTranslate(Vector2(856.f, 590.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_4_BLACK), 0, 0);
	Identify();
	// num6
	MakeTranslate(Vector2(1564.f, 590.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_6_BLACK), 0, 0);
	Identify();
	// num7
	MakeTranslate(Vector2(958.f, 340.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_7_BLACK), 0, 0);
	Identify();
	// num8
	MakeTranslate(Vector2(1210.f, 236.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_8_BLACK), 0, 0);
	Identify();
	// num9
	MakeTranslate(Vector2(1462.f, 340.f));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_9_BLACK), 0, 0);
	Identify();
}

void MagicCircle::DrawNumberLight(int key)
{
	Identify();
	switch (key)
	{
	default:
	case 1:
		// num 1
		MakeTranslate(Vector2(958, 844));
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_1_LIGHT), 0, 0);
		break;
	case 2:
		// num2
		MakeTranslate(Vector2(1210.f, 944.f));
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_2_LIGHT), 0, 0);
		break;
	case 3:
		// num3
		MakeTranslate(Vector2(1462.f, 844.f));
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_3_LIGHT), 0, 0);
		break;
	case 4:
		// num4
		MakeTranslate(Vector2(856.f, 590.f));
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_4_LIGHT), 0, 0);
		break;
	case 5:
		// num6
		MakeTranslate(Vector2(1564.f, 590.f));
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_6_LIGHT), 0, 0);
		break;
	case 6:
		// num7
		MakeTranslate(Vector2(958.f, 340.f));
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_7_LIGHT), 0, 0);
		break;
	case 7:
		// num8
		MakeTranslate(Vector2(1210.f, 236.f));
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_8_LIGHT), 0, 0);
		break;
	case 8:
		// num9
		MakeTranslate(Vector2(1462.f, 340.f));
		MakeTransformMatrix();
		D2DGraphics::GetInstance().SetTransform(TransformMatrix);
		D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_NUM_9_LIGHT), 0, 0);
		break;
	}
	Identify();
}

void MagicCircle::ClearLine()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Line[i][j] = false;
		}
	}
}

void MagicCircle::SetLine(int src, int dst)
{
	Line[src][dst] = true;
}

void MagicCircle::OnEvent()
{

}
