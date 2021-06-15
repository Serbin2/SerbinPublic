#pragma once


// SetMusicInfo 대화 상자

class SetMusicInfo : public CDialog
{
	DECLARE_DYNAMIC(SetMusicInfo)

public:
	SetMusicInfo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SetMusicInfo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_BPM;
	CEdit Filename;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedFileOpen();
};
