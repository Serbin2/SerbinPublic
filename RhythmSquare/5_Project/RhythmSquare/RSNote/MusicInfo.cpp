// MusicInfo.cpp: 구현 파일
//

#include "pchTool.h"
#include "MusicInfo.h"

#include "RSNote.h"


// MusicInfo

IMPLEMENT_DYNCREATE(MusicInfo, CFormView)

MusicInfo::MusicInfo()
	: CFormView(IDD_DIALOG1)
{


}

MusicInfo::~MusicInfo()
{
}

void MusicInfo::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_EditCheck);
	DDX_Control(pDX, IDC_NOTENUM, m_NoteNumStatic);
	DDX_Control(pDX, IDC_NOTETIME, NowNoteTime);
	//DDX_Control(pDX, IDC_NOTETYPE, NowNoteType);
	DDX_Control(pDX, IDC_NOTEKEY, NowNoteKey);
	DDX_Control(pDX, IDC_NOTEPAGE, NowNotePage);
	DDX_Control(pDX, IDC_MUBPM, NowSheetBPM);
	DDX_Control(pDX, IDC_FILENAME, MusicFileName);
	DDX_Control(pDX, IDC_MUSICLEN, NowMusicLength);
	DDX_Control(pDX, IDC_PAGETYPE, NowPageType);
	DDX_Control(pDX, IDC_PAGELEVEL, NowPageLevel);
	DDX_Control(pDX, IDC_PAGENUM, PageNumStatic);
	DDX_Control(pDX, IDC_COMPOSER, MusicComposer);
	DDX_Control(pDX, IDC_SONGLEVEL, NowMusicLevel);
	DDX_Control(pDX, IDC_MUSICPLACE, NowMusicPlace);
	DDX_Control(pDX, IDC_NOTEKEY2, NowNotePrevKey);
}

BEGIN_MESSAGE_MAP(MusicInfo, CFormView)
	ON_BN_CLICKED(IDC_LOADFILE, &MusicInfo::OnBnClickedLoadfile)
	ON_BN_CLICKED(IDC_BUTTON1, &MusicInfo::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON2, &MusicInfo::OnBnClickedButtonStop)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON3, &MusicInfo::OnBnClickedButtonReset)
	//ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_CHECK1, &MusicInfo::OnBnHotItemChangeCheckEditMode)
	ON_BN_CLICKED(IDC_BUTTON6, &MusicInfo::OnBnClickedButtonPrevNote)
	ON_BN_CLICKED(IDC_BUTTON5, &MusicInfo::OnBnClickedButtonNextNote)
	ON_BN_CLICKED(IDOK, &MusicInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MusicInfo::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON4, &MusicInfo::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_LOADSHEET, &MusicInfo::OnBnClickedLoadsheet)
	ON_WM_SETFOCUS()
	ON_BN_CLICKED(IDOK2, &MusicInfo::OnBnClickedOk2)
	ON_BN_CLICKED(IDCANCEL2, &MusicInfo::OnBnClickedCancel2)
	ON_BN_CLICKED(IDC_ADDPAGE, &MusicInfo::OnBnClickedAddpage)
	ON_BN_CLICKED(IDC_REMOVEPAGE, &MusicInfo::OnBnClickedRemovepage)
	ON_BN_CLICKED(IDC_PREVPAGE, &MusicInfo::OnBnClickedPrevpage)
	ON_BN_CLICKED(IDC_NEXTPAGE, &MusicInfo::OnBnClickedNextpage)
	ON_BN_CLICKED(IDC_NOTEDEL, &MusicInfo::OnBnClickedNotedel)
END_MESSAGE_MAP()


// MusicInfo 진단

#ifdef _DEBUG
void MusicInfo::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void MusicInfo::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// MusicInfo 메시지 처리기


void MusicInfo::OnBnClickedLoadfile()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strMsg;
	TCHAR fileFilter[] = _T("음악 파일(*.WAV, *.MP3) | *.WAV;*.MP3 |모든파일(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, fileFilter);

	//CMainFrame* frame = (CMainFrame*)AfxGetMainWnd();
	//mainview = (CChildView*)frame->m_info.GetPane(0, 0);
	//mainview->Initialize();
	if (dlg.DoModal() == IDOK)
	{

		strMsg.Format(_T("%s\\%s"), dlg.GetFolderPath(), dlg.GetFileName());
		AudioManager->loadFile(strMsg.operator LPCWSTR(), NowPlaying);

		strMsg.Format(_T("파일이름:%s\n파일확장자:%s\n파일타이틀:%s\n파일경로:%s"),
			dlg.GetFileName(), dlg.GetFileExt(),
			dlg.GetFileTitle(), dlg.GetFolderPath());

		AfxMessageBox(strMsg);
		strMsg.Format(_T("%s"), dlg.GetFileName());
		MusicFileName.SetWindowTextW(strMsg);

		AudioManager->SubmitSourceVoice(NowPlaying);
		RSPage* tmp = new RSPage();
		SheetManager::GetInstance().m_Page.push_back(tmp);
		PageEaUpdate();
	}
}

// 선택한 노래를 재생합니다.
void MusicInfo::OnBnClickedButtonPlay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AudioManager->playSoundEvent(NowPlaying);
	if (m_EditCheck.GetCheck())
	{
		//mainview->SetState(1);
		ViewManager::GetInstance().MainView->SetState(1);
	}
	else
	{
		//mainview->SetState(3);
		ViewManager::GetInstance().MainView->SetState(3);
	}
}

// 선택한 노래를 일시 정지합니다.
void MusicInfo::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AudioManager->stopSoundEvent(NowPlaying);
	//mainview->SetState(0);
	ViewManager::GetInstance().MainView->SetState(0);

}


int MusicInfo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	AudioManager = new AudioComponent;
	return 0;
}

// 선택한 노래를 처음부터 재생합니다.
void MusicInfo::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	NowPlaying.sourceVoice->FlushSourceBuffers();
 
	AudioManager->SubmitSourceVoice(NowPlaying);
	//mainview->SetState(2);
	ViewManager::GetInstance().MainView->SetState(2);


}

/*
void MusicInfo::OnBnHotItemChangeCheckEditMode(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 이 기능을 사용하려면 Internet Explorer 6 이상이 필요합니다.
	// _WIN32_IE 기호는 0x0600보다 크거나 같아야 합니다.
	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
*/

//void MusicInfo::NoteSelect(int number)
//{
//	// TODO: 여기에 구현 코드 추가.
//}


//void MusicInfo::NewNote()
//{
//	// TODO: 여기에 구현 코드 추가.
//	
//}


void MusicInfo::NoteEaUpdate()
{
	// TODO: 여기에 구현 코드 추가.
	CString str;
	int a = SheetManager::GetInstance().m_Note.size();
	int b = SheetManager::GetInstance().NowEditNote;
	str.Format(L"%d / %d", b, a);
	m_NoteNumStatic.SetWindowTextW(str);

	RSQNote* tmp = SheetManager::GetInstance().m_Note[b];

	str.Format(L"%.3f", tmp->GetTime());
	NowNoteTime.SetWindowTextW(str);

	str.Format(L"%d", tmp->GetPageNum());
	NowNotePage.SetWindowTextW(str);

	NowNotePrevKey.SetCurSel(tmp->GetPrevKey() - 1);
	NowNoteKey.SetCurSel(tmp->GetKey() - 1);
	Invalidate(false);
}


void MusicInfo::OnBnClickedButtonPrevNote()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (SheetManager::GetInstance().NowEditNote > 0)
	{
		SheetManager::GetInstance().NowEditNote--;
		NoteEaUpdate();
	}
}


void MusicInfo::OnBnClickedButtonNextNote()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (SheetManager::GetInstance().NowEditNote < SheetManager::GetInstance().m_Note.size() - 1)
	{
		SheetManager::GetInstance().NowEditNote++;
		NoteEaUpdate();
	}
}


void MusicInfo::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	RSQNote* tmp = SheetManager::GetInstance().m_Note[SheetManager::GetInstance().NowEditNote];
	NowNoteTime.GetWindowTextW(str);
	tmp->SetTime(_tstof(str));
	tmp->SetPrevKey(NowNotePrevKey.GetCurSel() + 1);
	tmp->SetKey(NowNoteKey.GetCurSel() + 1);
	NowNotePage.GetWindowTextW(str);
	tmp->SetPageNum(_tstoi(str));

}


void MusicInfo::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	NoteEaUpdate();
}


void MusicInfo::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strMsg;
	TCHAR fileFilter[] = _T("Binary File(*.bin) | *.bin; |모든파일(*.*)|*.*||");
	CFileDialog dlg(FALSE, L".bin", NULL, OFN_HIDEREADONLY, fileFilter);
	


	if (dlg.DoModal() == IDOK)
	{
		//float thisNoteTime = 0;
		for (int i = 0; i < SheetManager::GetInstance().m_Sheet.m_Page.size(); i++)
		{
			SheetManager::GetInstance().m_Sheet.m_Page[i]->m_Note.clear();
		}
		SheetManager::GetInstance().m_Sheet.m_Page.clear();

		CString str;
		MusicFileName.GetWindowTextW(str);
		SheetManager::GetInstance().m_Sheet.m_SongName = *str.GetBuffer();
		MusicComposer.GetWindowTextW(str);
		SheetManager::GetInstance().m_Sheet.m_Composer = *str.GetBuffer();
		NowSheetBPM.GetWindowTextW(str);
		SheetManager::GetInstance().m_Sheet.m_BPM = _tstof(str);
		NowMusicLength.GetWindowTextW(str);
		SheetManager::GetInstance().m_Sheet.m_SongLength = _tstof(str);
		NowMusicLevel.GetWindowTextW(str);
		SheetManager::GetInstance().m_Sheet.m_Level = _tstoi(str);
		SheetManager::GetInstance().m_Sheet.m_Place = NowMusicPlace.GetCurSel() + 1;
		for (int i = 0; i < SheetManager::GetInstance().m_Page.size(); i++)
		{
			RSPage* tmpPage = new RSPage();
			tmpPage->m_Type = SheetManager::GetInstance().m_Page[i]->m_Type;
			tmpPage->m_Level = SheetManager::GetInstance().m_Page[i]->m_Level;

			for (int k = 0; k < SheetManager::GetInstance().m_Note.size(); k++)
			{
				RSQNote* tmpNote = nullptr;
				float tmpTime = 10000;
				int pos;
				for (int j = 0; j < SheetManager::GetInstance().m_Note.size(); j++) // 제일 밑의 노트 탐색
				{
					if (SheetManager::GetInstance().m_Note[j]->GetTime() <= tmpTime)
					{
						tmpNote = SheetManager::GetInstance().m_Note[j];
						tmpTime = tmpNote->GetTime();
						pos = j;
					}
				}
				//tmpNote->SetType(0);
				if (tmpNote != nullptr)
				{
					if (tmpNote->GetPageNum() == i)
					{
						tmpPage->m_Note.push_back(tmpNote);
						SheetManager::GetInstance().m_Note.erase(SheetManager::GetInstance().m_Note.begin() + pos); // 탐색된 노트 제거
						k--;
					}
					if (tmpNote->GetPageNum() > i)
					{
						break;
					}
				}
			}
			
			SheetManager::GetInstance().m_Sheet.m_Page.push_back(tmpPage);
		}

		strMsg.Format(_T("%s\\%s"), dlg.GetFolderPath(), dlg.GetFileName());
		RSSaveSheet(strMsg, &SheetManager::GetInstance().m_Sheet);


		strMsg.Format(_T("저장되었습니다."));

		AfxMessageBox(strMsg);


	}
}


void MusicInfo::OnBnClickedLoadsheet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strMsg;
	TCHAR fileFilter[] = _T("Binary File(*.bin) | *.bin; |모든파일(*.*)|*.*||");
	CFileDialog dlg(TRUE, L".bin", NULL, OFN_HIDEREADONLY, fileFilter);

	if (dlg.DoModal() == IDOK)
	{
		//float thisNoteTime = 0;
		for (int i = 0; i < SheetManager::GetInstance().m_Sheet.m_Page.size(); i++)
		{
			SheetManager::GetInstance().m_Sheet.m_Page[i]->m_Note.clear();
		}
		SheetManager::GetInstance().m_Sheet.m_Page.clear();

		strMsg.Format(_T("%s\\%s"), dlg.GetFolderPath(), dlg.GetFileName());
		RSLoadSheet(strMsg, &SheetManager::GetInstance().m_Sheet);

		SheetManager::GetInstance().m_Page.clear();
		SheetManager::GetInstance().m_Note.clear();

		for (int i = 0; i < SheetManager::GetInstance().m_Sheet.m_Page.size(); i++)
		{
			SheetManager::GetInstance().m_Page.push_back(SheetManager::GetInstance().m_Sheet.m_Page[i]);
			for (int j = 0; j < SheetManager::GetInstance().m_Sheet.m_Page[i]->m_Note.size(); j++)
			{
				SheetManager::GetInstance().m_Note.push_back(SheetManager::GetInstance().m_Sheet.m_Page[i]->m_Note[j]);
			}
		}

		SheetManager::GetInstance().NowEditNote = 0;
		SheetManager::GetInstance().NowEditPage = 0;

		NoteEaUpdate();
		PageEaUpdate();
		strMsg.Format(_T("불러왔습니다."));

		AfxMessageBox(strMsg);


	}
}


void MusicInfo::OnSetFocus(CWnd* pOldWnd)
{
	CFormView::OnSetFocus(pOldWnd);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	Invalidate(false);
}


void MusicInfo::OnBnClickedOk2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CString str;
	//RSQNote* tmp = SheetManager::GetInstance().m_Note[SheetManager::GetInstance().NowEditNote];
	//NowNoteTime.GetWindowTextW(str);
	//tmp->SetTime(_tstof(str));
	//tmp->SetPrevKey(NowNotePrevKey.GetCurSel() + 1);
	//tmp->SetKey(NowNoteKey.GetCurSel() + 1);
	//NowNotePage.GetWindowTextW(str);
	//tmp->SetPageNum(_tstoi(str));

	RSPage* tmp = SheetManager::GetInstance().m_Page[SheetManager::GetInstance().NowEditPage];
	tmp->m_Level = NowPageLevel.GetCurSel();
	tmp->m_Type = NowPageType.GetCurSel();
	PageEaUpdate();

}


void MusicInfo::OnBnClickedCancel2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PageEaUpdate();
}


void MusicInfo::OnBnClickedAddpage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	RSPage* tmp = new RSPage();
	SheetManager::GetInstance().m_Page.push_back(tmp);
	PageEaUpdate();
}


void MusicInfo::OnBnClickedRemovepage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (SheetManager::GetInstance().m_Page.size() > 1)
	{
		SheetManager::GetInstance().m_Page.pop_back();
	}
	SheetManager::GetInstance().NowEditPage = 0;
	PageEaUpdate();
}


void MusicInfo::OnBnClickedPrevpage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (SheetManager::GetInstance().NowEditPage > 0)
	{
		SheetManager::GetInstance().NowEditPage--;
		PageEaUpdate();
	}
}


void MusicInfo::OnBnClickedNextpage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (SheetManager::GetInstance().NowEditPage < SheetManager::GetInstance().m_Page.size() - 1)
	{
		SheetManager::GetInstance().NowEditPage++;
		PageEaUpdate();
	}
}


void MusicInfo::PageEaUpdate()
{
	// TODO: 여기에 구현 코드 추가.
	CString str;
	int a = SheetManager::GetInstance().m_Page.size();
	int b = SheetManager::GetInstance().NowEditPage;
	str.Format(L"%d / %d", b, a);
	PageNumStatic.SetWindowTextW(str);

	RSPage* tmp = SheetManager::GetInstance().m_Page[b];

	NowPageType.SetCurSel(tmp->m_Type);
	NowPageLevel.SetCurSel(tmp->m_Level);
	Invalidate(false);
}


void MusicInfo::OnBnClickedNotedel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (SheetManager::GetInstance().m_Note.size() > 1)
	{
		SheetManager::GetInstance().m_Note.erase(SheetManager::GetInstance().m_Note.begin() + SheetManager::GetInstance().NowEditNote);
		SheetManager::GetInstance().NowEditNote--;
		if (SheetManager::GetInstance().NowEditNote < 0)
		{
			SheetManager::GetInstance().NowEditNote = 0;
		}
	}
	NoteEaUpdate();

}
