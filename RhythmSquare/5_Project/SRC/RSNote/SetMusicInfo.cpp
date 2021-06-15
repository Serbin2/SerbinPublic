// SetMusicInfo.cpp: 구현 파일
//

#include "pch.h"
#include "RSNote.h"
#include "SetMusicInfo.h"
#include "afxdialogex.h"


// SetMusicInfo 대화 상자

IMPLEMENT_DYNAMIC(SetMusicInfo, CDialog)

SetMusicInfo::SetMusicInfo(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_BPM(0)
{

}

SetMusicInfo::~SetMusicInfo()
{
}

void SetMusicInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MUBPM, m_BPM);
	DDX_Control(pDX, IDC_FILENAME, Filename);
}


BEGIN_MESSAGE_MAP(SetMusicInfo, CDialog)
	ON_BN_CLICKED(IDOK, &SetMusicInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDC_LOADFILE, &SetMusicInfo::OnBnClickedFileOpen)
END_MESSAGE_MAP()


// SetMusicInfo 메시지 처리기


void SetMusicInfo::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}


void SetMusicInfo::OnBnClickedFileOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strMsg;
	TCHAR fileFilter[] = _T("*.mp3|*.wav");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, fileFilter);

	if (dlg.DoModal() == IDOK)
	{
		strMsg.Format(_T("파일이름:%s\n파일확장자:%s\n파일타이틀:%s\n파일경로:%s"),
			dlg.GetFileName(), dlg.GetFileExt(),
			dlg.GetFileTitle(), dlg.GetFolderPath());

		AfxMessageBox(strMsg);
	}

}
