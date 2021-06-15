
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once
//#include "MusicInfo.h"


// CChildView 창

class CChildView : public CWnd 
{
	
public:
	CChildView();

	// 특성입니다.
public:
	// 작업입니다.


public:


	// 재정의입니다.
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// 구현입니다.
public:
	virtual ~CChildView();
//	void Draw();
	// 생성된 메시지 맵 함수
protected:
	//	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//bool tst;
//	afx_msg void OnBnClickedButtonPlay();
//	afx_msg void OnBnClickedButtonStop();
//	void SetState(int State);
protected:
//	int state;
//	float PlayTime;

//	bool OnEdit;
public:
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

