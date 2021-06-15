
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pchTool.h"
#include "framework.h"
#include "RSNote.h"
#include "ChildView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//static MusicInfo* InfoView;
// CChildView

CChildView::CChildView()
{
	//RimEngine::GetInstance()->InitializeEngine(GetSafeHwnd());
	//RimEngine::GetInstance()->SetBrush(255, 255, 255, 255);

	//  state = 0;
	//OnEdit = true;
}



CChildView::~CChildView()
{
}


//void CChildView::Draw()
//{
//	static LineVector _Line[8];
//	static int tst = 0;
//	static float timeStamp;
//	//static 	std::vector<RSQNote*> Sheet;
//	//static MusicInfo* InfoView;
//	if (tst == 0)
//	{
//		CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
//		HWND hWnd = frame->m_info.GetPane(0, 0)->m_hWnd;
//		//SheetManager::GetInstance().InfoView = (MusicInfo*)frame->m_info.GetPane(0, 1);
//		HDC hdc = ::GetDC(hWnd);
//		D2DGraphics::GetInstance().Initialize(hWnd, hdc);
//		D2DGraphics::GetInstance().CreateDeviceTarget();
//		tst = 25;
//
//		//InfoView = (MusicInfo*)frame->m_info.GetPane(0, 1);
//
//		Vector2 src;
//		Vector2 dst;
//		for (int i = 0; i < 7; i++)
//		{
//			src.x = 100.f * (i + 1);
//			src.y = 0.f;
//			dst.x = 100.f * (i + 1);
//			dst.y = 900.f;
//			_Line[i].Src = src;
//			_Line[i].Dst = dst;
//		}
//		src.x = 0.f;
//		src.y = 600.f;
//		dst.x = 900.f;
//		dst.y = 600.f;
//		_Line[7].Src = src;
//		_Line[7].Dst = dst;
//		  
//		Timer::GetInstance().Start();
//		Timer::GetInstance().Update();
//		timeStamp = Timer::GetInstance().Now();
//		PlayTime = 0;
//		state = 0;
//		//Sheet.clear();
//		//RSPage tmpPage;
//		//SheetManager::GetInstance().m_Sheet.m_Page.push_back(tmpPage);
//	}
//	if (tst > 20)
//	{
//		Timer::GetInstance().Update();
//		Key::GetInstance().Update();
//		D2DGraphics::GetInstance().BeginDraw();
//		switch (state)
//		{
//		case 0: // idle
//			timeStamp = Timer::GetInstance().Now();
//			break;
//		case 1: // play
//			PlayTime += Timer::GetInstance().Delta();
//
//			if (OnEdit)
//			{
//				RSQNote* NoteTmp;
//				unsigned char keyTmp = 0x61;
//				for (keyTmp; keyTmp < 0x6a; keyTmp++)
//				{
//					if (keyTmp == 0x65)
//					{
//						continue;
//					}
//					if (Key::GetInstance().GetKeyState(keyTmp) == KEYDOWN)
//					{
//						NoteTmp = new RSQNote(PlayTime, keyTmp);
//						//NoteTmp->SetNoteRect(0, 0 - (PlayTime * 300), 60, 20 - (PlayTime * 300));
//						//NoteTmp->SetPos((NoteTmp->GetKey() - 1) * 100, (-1) * (PlayTime * 300));
//						//Sheet.push_back(NoteTmp);
//						SheetManager::GetInstance().m_Note.push_back(NoteTmp);
//						ViewManager::GetInstance().InfoView->NoteEaUpdate();
//						//InfoView->NewNote();
//					}
//				}
//			}
//
//
//
//			break;
//		}
//
//
//
//		for (int i = 0; i < 8; i++)
//		{
//			D2DGraphics::GetInstance().DrawLine(_Line[i], RGB(0, 255, 255));
//		}
//
//		for (int i = 0; i < SheetManager::GetInstance().m_Note.size(); i++)
//		{
//			
//			// 초당 300픽셀 내려오는 노트
//			//SheetManager::GetInstance().m_Note[i]->Move(0, Timer::GetInstance().DeltaTime);
//			RSQNote NoteTmp = *SheetManager::GetInstance().m_Note[i];
//			NoteTmp.SetPos((NoteTmp.GetKey() - 1) * 100, ((PlayTime - NoteTmp.GetTime()) * 300) + 600);
//			NoteTmp.Draw();
//
//			//D2DGraphics::GetInstance().DrawRectanglePos((SheetManager::GetInstance().m_Note[i]->GetKey() - 1) * 100, (PlayTime * 300) + 600, SheetManager::GetInstance().m_Note[i]->GetNoteRect(), RGB(255, 255, 0), true);
//
//		}
//
//
//
//		D2DGraphics::GetInstance().WriteText(RGB(0, 255, 0), D2D1::RectF(5, 5, 100, 100), L"%.2f", PlayTime);
//		D2DGraphics::GetInstance().EndDraw();
//	}
//}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	//	ON_WM_PAINT()
	//	ON_WM_CREATE()
	//ON_BN_CLICKED(IDC_BUTTON1, &CChildView::OnBnClickedButtonPlay)
	//ON_BN_CLICKED(IDC_BUTTON2, &CChildView::OnBnClickedButtonStop)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), nullptr);
	//tst = false;
	return TRUE;
}

//void CChildView::OnPaint() 
//{
//	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
//	
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//	
//	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
//	
//}



//int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
//{
//	if (CWnd::OnCreate(lpCreateStruct) == -1)
//		return -1;
//
//	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
//	
//	return 0;
//}


//void CChildView::OnBnClickedButtonPlay()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


//void CChildView::OnBnClickedButtonStop()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}


//void CChildView::SetState(int State)
//{
//	// TODO: 여기에 구현 코드 추가.
//	state = State;
//	if (state == 2)
//	{
//		PlayTime = 0;
//		state = 0;
//	}
//	if (state == 1)
//	{
//		OnEdit = true;
//	}
//	if (state == 3)
//	{
//		OnEdit = false;
//		state = 1;
//	}
//}


//void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	for (int i = 0; i < SheetManager::GetInstance().m_Note.size(); i++)
//	{
//
//		RSQNote NoteTmp = *SheetManager::GetInstance().m_Note[i];
//		NoteTmp.SetPos((NoteTmp.GetKey() - 1) * 100, ((PlayTime - NoteTmp.GetTime()) * 300) + 600);
//		Vector2 mouse;
//		mouse.x = point.x;
//		mouse.y = point.y;
//		if (Colision::CheckRectPoint(NoteTmp.GetNoteRectWithPos(), mouse))
//		{
//			SheetManager::GetInstance().NowEditNote = i;
//			ViewManager::GetInstance().InfoView->NoteEaUpdate();
//			break;
//		}
//	}
//
//
//	CWnd::OnLButtonDown(nFlags, point);
//}
