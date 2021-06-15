#pragma once
#include "../RhythmLibary/GameObject/GameObject.h"


class RSQNote : public GameObject
{
public:
	RSQNote();
	RSQNote(float time, int key);
	RSQNote(float time, unsigned char key);
	~RSQNote();

	void SetTime(float time);
	void SetKey(int key);
	int GetKey() { return m_Key; };
	float GetTime() { return m_time; };
	void SetType(int type) { m_Type = type; };
	int GetType() { return m_Type; };
	void SetPrevKey(int key);
	int GetPrevKey() { return m_PrevKey; };

private:

	float m_time;
	int m_Type;

	// 키는 1~8까지 받습니다. 6~9의 키가 5~8로 변환되어야 하니 이점에 주의!
	int m_Key;
	// 이전 노트의 키( 라인 그리기용)
	int m_PrevKey;


#ifndef RSTOOL

public:
	int Judge(float time); // 입력 판정
	int RenderPosition(float playingTime, float TimePerBeat); // 그려질 때의 시간을 받음
	void Draw(float x, float y);
	void CalcDistance();
private:

	D2D1_POINT_2F m_Dst;
	D2D1_POINT_2F m_Src;
	D2D1_POINT_2F m_Distance;

#endif


#ifdef RSTOOL
public:
	void SetNoteRect(float left, float top, float right, float bottom);
	void SetPageNum(int num);
	int GetPageNum() { return pageNum; };
	D2D1_RECT_F GetNoteRect() { return rect; };
	D2D1_RECT_F GetNoteRectWithPos();
	void SetPos(float x, float y);
	D2D1_POINT_2F GetPos() { return CurPos; };
	void Draw();
	void Move(float x, float y);

private:
	D2D1_RECT_F rect;
	int pageNum;
	D2D1_POINT_2F CurPos;
#endif // RSTOOL


};

