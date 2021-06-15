#include "pchApp.h"

#include "RSQNote.h"
#include "../RhythmSquare/Resource/ResourceManager.h"


RSQNote::RSQNote() : m_time(0), m_Key(0), m_Type(0), m_PrevKey(0), m_Distance(D2D1::Point2F(0, 0)), m_Dst(D2D1::Point2F(0, 0)), m_Src(D2D1::Point2F(0, 0))
{
	isLastNote = false;
	
#ifdef RSTOOL
	rect = { 0,0,60,20 };
	pageNum = 0;

#endif
}

RSQNote::RSQNote(float time, int key) : m_time(time), m_Key(key), m_Type(0), m_PrevKey(0), m_Distance(D2D1::Point2F(0, 0)), m_Dst(D2D1::Point2F(0, 0)), m_Src(D2D1::Point2F(0, 0))
{
	isLastNote = false;
#ifndef RSTOOL
	switch (m_Key)
	{
	case 1:
		m_Dst.x = X_2;
		m_Dst.y = Y_4;
		break;
	case 2:
		m_Dst.x = X_3;
		m_Dst.y = Y_5;
		break;
	case 3:
		m_Dst.x = X_4;
		m_Dst.y = Y_4;
		break;
	case 4:
		m_Dst.x = X_1;
		m_Dst.y = Y_3;
		break;
	case 5:
		m_Dst = { X_5, Y_3 };
		break;
	case 6:
		m_Dst = { X_2, Y_2 };
		break;
	case 7:
		m_Dst = { X_3, Y_1 };
		break;
	case 8:
		m_Dst = { X_4, Y_2 };
		break;
	default:
		break;
	}

#endif // !RSTOOL


#ifdef RSTOOL
	rect = { 0,0,60,20 };
	pageNum = 0;

#endif
}

RSQNote::RSQNote(float time, unsigned char key) : m_time(time), m_Type(0), m_PrevKey(0),
m_Distance(D2D1::Point2F(0, 0)), m_Dst(D2D1::Point2F(0, 0)), m_Src(D2D1::Point2F(0, 0))
{
	switch (key)
	{
	case 0x31:
	case 0x61:
		m_Key = 1;
		break;
	case 0x32:
	case 0x62:
		m_Key = 2;
		break;
	case 0x33:
	case 0x63:
		m_Key = 3;
		break;
	case 0x34:
	case 0x64:
		m_Key = 4;
		break;
	case 0x36:
	case 0x66:
		m_Key = 5;
		break;
	case 0x37:
	case 0x67:
		m_Key = 6;
		break;
	case 0x38:
	case 0x68:
		m_Key = 7;
		break;
	case 0x39:
	case 0x69:
		m_Key = 8;
		break;
	default:
		m_Key = 0;
		break;
	}
	isLastNote = false;
#ifndef RSTOOL
	switch (m_Key)
	{
	case 1:
		m_Dst.x = X_2;
		m_Dst.y = Y_4;
		break;
	case 2:
		m_Dst.x = X_3;
		m_Dst.y = Y_5;
		break;
	case 3:
		m_Dst.x = X_4;
		m_Dst.y = Y_4;
		break;
	case 4:
		m_Dst.x = X_1;
		m_Dst.y = Y_3;
		break;
	case 5:
		m_Dst = { X_5, Y_3 };
		break;
	case 6:
		m_Dst = { X_2, Y_2 };
		break;
	case 7:
		m_Dst = { X_3, Y_1 };
		break;
	case 8:
		m_Dst = { X_4, Y_2 };
		break;
	default:
		break;
	}

#endif // !RSTOOL

#ifdef RSTOOL
	rect = { 0,0,60,20 };
	pageNum = 0;

#endif
}

RSQNote::~RSQNote()
{

}

void RSQNote::SetTime(float time)
{
	m_time = time;
}


void RSQNote::SetKey(int key)
{
	m_Key = key;

#ifndef RSTOOL
	switch (m_Key)
	{
	case 1:
		m_Dst.x = X_2;
		m_Dst.y = Y_4;
		break;
	case 2:
		m_Dst.x = X_3;
		m_Dst.y = Y_5;
		break;
	case 3:
		m_Dst.x = X_4;
		m_Dst.y = Y_4;
		break;
	case 4:
		m_Dst.x = X_1;
		m_Dst.y = Y_3;
		break;
	case 5:
		m_Dst = { X_5, Y_3 };
		break;
	case 6:
		m_Dst = { X_2, Y_2 };
		break;
	case 7:
		m_Dst = { X_3, Y_1 };
		break;
	case 8:
		m_Dst = { X_4, Y_2 };
		break;
	default:
		break;
	}

#endif // !RSTOOL

}

void RSQNote::SetPrevKey(int key)
{
	m_PrevKey = key;

#ifndef RSTOOL

	switch (m_PrevKey)
	{
	case 1:
		m_Src.x = X_2;
		m_Src.y = Y_4;
		break;
	case 2:
		m_Src.x = X_3;
		m_Src.y = Y_5;
		break;
	case 3:
		m_Src.x = X_4;
		m_Src.y = Y_4;
		break;
	case 4:
		m_Src.x = X_1;
		m_Src.y = Y_3;
		break;
	case 5:
		m_Src = { X_5, Y_3 };
		break;
	case 6:
		m_Src = { X_2, Y_2 };
		break;
	case 7:
		m_Src = { X_3, Y_1 };
		break;
	case 8:
		m_Src = { X_4, Y_2 };
		break;
	default:
		break;
	}

	CalcDistance();
#endif // !RSTOOL

}

#ifndef RSTOOL
int RSQNote::Judge(float time, bool fever) // 곡이 재생되는 시간을 기준으로 키가 입력된 시간을 받아야 합니다.
{
	float judTime = m_time - time + GameManager::GetInstance().m_InputRev; // 양수일 경우 Early, 음수일 경우 Late

	if (judTime > JUD_MISS)
	{
		//판정이 일어나지 않음
		return JUD_NO_MATCH;
	}
	if (judTime < JUD_MISS && judTime > JUD_GOOD)
	{
		return JUD_EARL_MISS;
		FXManager::GetInstance().RenderJudgeFX(0, fever);
	}
	if (judTime < JUD_GOOD && judTime > JUD_PERF)
	{
		MagicCircle::GetInstance().SetLine(m_PrevKey - 1, m_Key - 1);
		FXManager::GetInstance().RenderJudgeFX(1, fever);
		return JUD_EARL_GOOD;
	}
	if (judTime < JUD_PERF && judTime > JUD_EXAC)
	{
		MagicCircle::GetInstance().SetLine(m_PrevKey - 1, m_Key - 1);
		FXManager::GetInstance().RenderJudgeFX(2, fever);
		return JUD_EARL_PERF;
	}
	if (judTime < JUD_EXAC && judTime > -JUD_EXAC)
	{
		MagicCircle::GetInstance().SetLine(m_PrevKey - 1, m_Key - 1);
		FXManager::GetInstance().RenderJudgeFX(2, fever);
		return JUD_EXAC_PERF;
	}
	if (judTime < -JUD_EXAC && judTime > -JUD_PERF)
	{
		MagicCircle::GetInstance().SetLine(m_PrevKey - 1, m_Key - 1);
		FXManager::GetInstance().RenderJudgeFX(2, fever);
		return JUD_LATE_PERF;
	}
	if (judTime < -JUD_PERF && judTime > -JUD_GOOD)
	{
		MagicCircle::GetInstance().SetLine(m_PrevKey - 1, m_Key - 1);
		FXManager::GetInstance().RenderJudgeFX(1, fever);
		return JUD_LATE_GOOD;
	}
	if (judTime < -JUD_GOOD)
	{
		FXManager::GetInstance().RenderJudgeFX(0, fever);
		return JUD_LATE_MISS;
	}
	return JUD_NO_MATCH;
}

int RSQNote::RenderPosition(float playingTime, float TimePerBeat)
{

	float judTime = m_time - playingTime;
	if (judTime < -JUD_MISS)
	{
		return 1; // 이미 지나간 노트
	}
	if (judTime > TimePerBeat * PRE_BEAT)
	{
		return 2; // 아직 그릴 필요가 없는 노트
	}
	if (!isLastNote)
	{
		D2D1_POINT_2F position;

		position.x = 0;
		position.y = 0;

		if (judTime == 0)
		{
			position = m_Dst;
		}
		else
		{
			float per = judTime / (TimePerBeat * PRE_BEAT);

			position.x = m_Dst.x + m_Distance.x * per;
			position.y = m_Dst.y + m_Distance.y * per;
		}
		Draw(position.x, position.y);
	}
	else
	{
		float scale;

		if (judTime == 0)
		{
			scale = 1.f;
		}
		else
		{
			scale = 1 - (judTime / (TimePerBeat * PRE_BEAT));
		}
		Draw(scale);
	}
	return 0;
}

void RSQNote::Draw(float x, float y)
{
	/*SetPositionW(Vector2(m_Dst.x - 125.f, m_Dst.y - 125.f));
	Identify();
	MakeTranslate(Vector2(World_Position));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::DUMMY_NOTE), 0, 0);
	Identify();*/

	MagicCircle::GetInstance().DrawNumberLight(m_Key);

	SetPositionW(Vector2(x - 125.f, y - 125.f));
	Identify();
	MakeTranslate(Vector2(World_Position));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_NOTE_GUIDE_CIRCLE), 0, 0);
	Identify();
}

void RSQNote::Draw(float scale)
{
	SetPositionW(Vector2(810, 190));
	Identify();
	MakeScale(Vector2(scale, scale), Vector2(470, 470));
	MakeTranslate(Vector2(World_Position));
	MakeTransformMatrix();
	D2DGraphics::GetInstance().SetTransform(TransformMatrix);
	D2DGraphics::GetInstance().DrawImage(ResourceManager::GetInstance().GetImageSheet(ResourceID::PLAY_EFFECT_MAGIC_CIRCLE_ATT_LIGHT), 0, 0);
	Identify();
}


void RSQNote::CalcDistance()
{
	m_Distance.x = m_Src.x - m_Dst.x;
	m_Distance.y = m_Src.y - m_Dst.y;
}

#endif // !RSTOOL

#ifdef RSTOOL
void RSQNote::SetNoteRect(float left, float top, float right, float bottom)
{
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
}

void RSQNote::SetPageNum(int num)
{
	pageNum = num;
}

D2D1_RECT_F RSQNote::GetNoteRectWithPos()
{
	D2D1_RECT_F rt;
	rt.top = rect.top + CurPos.y;
	rt.bottom = rect.bottom + CurPos.y;
	rt.left = rect.left + CurPos.x;
	rt.right = rect.right + CurPos.x;
	return rt;
}

void RSQNote::SetPos(float x, float y)
{
	CurPos.x = x;
	CurPos.y = y;
}

void RSQNote::Draw()
{
	D2D1_RECT_F rt;
	rt.top = rect.top + CurPos.y;
	rt.bottom = rect.bottom + CurPos.y;
	rt.left = rect.left + CurPos.x;
	rt.right = rect.right + CurPos.x;
	D2DGraphics::GetInstance().DrawRectangle(rt, RGB(255, 255, 0), true);
}

void RSQNote::Move(float x, float y)
{
	CurPos.x += x;
	CurPos.y += y;
}

#endif