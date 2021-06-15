// CMainView.cpp: 구현 파일
//

#include "pchTool.h"
#include "RSNote.h"
#include "CMainView.h"


// CMainView

IMPLEMENT_DYNCREATE(CMainView, CScrollView)

CMainView::CMainView()
{
	PlayTime = 0;
	state = 0;
	OnEdit = true;
	m_Pos = { 0,0 };
}

CMainView::~CMainView()
{
}


BEGIN_MESSAGE_MAP(CMainView, CScrollView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
//	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CMainView 그리기

void CMainView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);

	CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	HWND hWnd = frame->m_info.GetPane(0, 0)->m_hWnd;

	//HWND hWnd = m_hWnd;
	HDC hdc = ::GetDC(hWnd);
	D2DGraphics::GetInstance().Initialize(hWnd, hdc);
	D2DGraphics::GetInstance().CreateDeviceTarget(836,1108);

	Vector2 src;
	Vector2 dst;
	for (int i = 0; i < 7; i++)
	{
		src.x = 100.f * (i + 1);
		src.y = 0.f;
		dst.x = 100.f * (i + 1);
		dst.y = 900.f;
		_Line[i].Src = src;
		_Line[i].Dst = dst;
	}
	src.x = 0.f;
	src.y = 600.f;
	dst.x = 900.f;
	dst.y = 600.f;
	_Line[7].Src = src;
	_Line[7].Dst = dst;

	Timer::GetInstance().Start();
	Timer::GetInstance().Update();

	PlayTime = 0;
	state = 0;
}

void CMainView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
	Timer::GetInstance().Update();
	Key::GetInstance().Update();
	D2DGraphics::GetInstance().BeginDraw();
	switch (state)
	{
	case 0: // idle
		//timeStamp = Timer::GetInstance().Now();
		break;
	case 1: // play
		PlayTime += Timer::GetInstance().Delta();

		if (OnEdit)
		{
			RSQNote* NoteTmp;
			unsigned char keyTmp = 0x61;
			for (keyTmp; keyTmp < 0x6a; keyTmp++)
			{
				if (keyTmp == 0x65)
				{
					continue;
				}
				if (Key::GetInstance().GetKeyState(keyTmp) == KEYDOWN)
				{
					NoteTmp = new RSQNote(PlayTime, keyTmp);
					//NoteTmp->SetNoteRect(0, 0 - (PlayTime * 300), 60, 20 - (PlayTime * 300));
					//NoteTmp->SetPos((NoteTmp->GetKey() - 1) * 100, (-1) * (PlayTime * 300));
					//Sheet.push_back(NoteTmp);
					SheetManager::GetInstance().m_Note.push_back(NoteTmp);
					ViewManager::GetInstance().InfoView->NoteEaUpdate();
					//InfoView->NewNote();
				}
			}

			keyTmp = 0x31;
			for (keyTmp; keyTmp < 0x3a; keyTmp++)
			{
				if (keyTmp == 0x35)
				{
					continue;
				}
				if (Key::GetInstance().GetKeyState(keyTmp) == KEYDOWN)
				{
					NoteTmp = new RSQNote(PlayTime, keyTmp);
					//NoteTmp->SetNoteRect(0, 0 - (PlayTime * 300), 60, 20 - (PlayTime * 300));
					//NoteTmp->SetPos((NoteTmp->GetKey() - 1) * 100, (-1) * (PlayTime * 300));
					//Sheet.push_back(NoteTmp);
					SheetManager::GetInstance().m_Note.push_back(NoteTmp);
					ViewManager::GetInstance().InfoView->NoteEaUpdate();
					//InfoView->NewNote();
				}
			}
		}



		break;
	}


	for (int i = 0; i < 8; i++)
	{
		D2DGraphics::GetInstance().DrawLine(_Line[i], RGB(0, 255, 255));
	}

	for (int i = 0; i < SheetManager::GetInstance().m_Note.size(); i++)
	{

		// 초당 300픽셀 내려오는 노트
		//SheetManager::GetInstance().m_Note[i]->Move(0, Timer::GetInstance().DeltaTime);
		RSQNote NoteTmp = *SheetManager::GetInstance().m_Note[i];
		NoteTmp.SetPos((NoteTmp.GetKey() - 1) * 100, ((PlayTime - NoteTmp.GetTime()) * 300) + 600);
		NoteTmp.Draw();

		//D2DGraphics::GetInstance().DrawRectanglePos((SheetManager::GetInstance().m_Note[i]->GetKey() - 1) * 100, (PlayTime * 300) + 600, SheetManager::GetInstance().m_Note[i]->GetNoteRect(), RGB(255, 255, 0), true);

	}


	D2DGraphics::GetInstance().WriteTextDebug(RGB(0, 255, 0), D2D1::RectF(5, 5, 500, 500), L"%d / %d", m_Pos.x, m_Pos.y);
	D2DGraphics::GetInstance().WriteTextDebug(RGB(0, 255, 0), D2D1::RectF(5, 100, 1000, 1000), L"%.2f", PlayTime);
	D2DGraphics::GetInstance().EndDraw();
}


// CMainView 진단

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainView 메시지 처리기


void CMainView::SetState(int State)
{
	// TODO: 여기에 구현 코드 추가.
	state = State;
	if (state == 2)
	{
		PlayTime = 0;
		state = 0;
	}
	if (state == 1)
	{
		OnEdit = true;
	}
	if (state == 3)
	{
		OnEdit = false;
		state = 1;
	}
}


void CMainView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	for (int i = 0; i < SheetManager::GetInstance().m_Note.size(); i++)
	{

		RSQNote NoteTmp = *SheetManager::GetInstance().m_Note[i];
		NoteTmp.SetPos((NoteTmp.GetKey() - 1) * 100, ((PlayTime - NoteTmp.GetTime()) * 300) + 600);
		Vector2 mouse;
		mouse.x = point.x;
		mouse.y = point.y;
		if (Collision::CheckRectPoint(NoteTmp.GetNoteRectWithPos(), mouse))
		{
			SheetManager::GetInstance().NowEditNote = i;
			ViewManager::GetInstance().InfoView->NoteEaUpdate();
			PlayTime = SheetManager::GetInstance().m_Note[i]->GetTime();
			break;
		}
	}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CMainView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_Pos.x = point.x;
	m_Pos.y = point.y;
	CScrollView::OnMouseMove(nFlags, point);
}


//void CMainView::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// 이 기능을 사용하려면 Windows Vista 이상이 있어야 합니다.
//	// _WIN32_WINNT 기호는 0x0600보다 크거나 같아야 합니다.
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	if (state == 0)
//	{
//		if (zDelta > 0)
//		{
//			PlayTime++;
//		}
//		else
//		{
//			PlayTime--;
//		}
//
//
//
//	}
//
//
//	CScrollView::OnMouseHWheel(nFlags, zDelta, pt);
//}


BOOL CMainView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (state == 0)
	{
		if (zDelta > 0)
		{
			PlayTime += 0.5f;
		}
		else
		{
			PlayTime -= 0.5f;
		}



	}

	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}
