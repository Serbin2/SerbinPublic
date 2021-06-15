
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "RSNote.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	RimEngine::GetInstance()->InitializeEngine(GetSafeHwnd());
	//RimEngine::GetInstance()->SetBrush(255, 255, 255, 255);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	RimEngine::GetInstance()->BeginDraw();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	/*dc.GetCurrentBrush();
	dc.Rectangle(10, 10, 50, 50);

	test++;
	if (test > 19)
	{
		dc.Rectangle(60, 60, 100, 100);
	}*/

	RimEngine::GetInstance()->DrawRectangle(50, 50, 100, 100);


	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
	RimEngine::GetInstance()->EndDraw();
}

