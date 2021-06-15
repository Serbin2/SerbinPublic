#pragma once

#include "MainFrm.h"

// MusicInfo 폼 보기

class MusicInfo : public CFormView
{
	DECLARE_DYNCREATE(MusicInfo)

protected:
	MusicInfo();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~MusicInfo();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoadfile();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonStop();

	SoundEvent NowPlaying;
	AudioComponent* AudioManager;
	//CChildView* mainview;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButtonReset();
	//afx_msg void OnBnHotItemChangeCheckEditMode(NMHDR* pNMHDR, LRESULT* pResult);
	CButton m_EditCheck;
	CStatic m_NoteNumStatic;
//	void NoteSelect(int number);
//	void NewNote();
protected:


public:
	void NoteEaUpdate();
	CEdit NowNoteTime;
//	CComboBox NowNoteType;
	CComboBox NowNoteKey;
	CEdit NowNotePage;
	CEdit NowSheetBPM;
	afx_msg void OnBnClickedButtonPrevNote();
	afx_msg void OnBnClickedButtonNextNote();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit MusicFileName;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedLoadsheet();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	CEdit NowMusicLength;
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedCancel2();
	CComboBox NowPageType;
	CComboBox NowPageLevel;
	CStatic PageNumStatic;
	afx_msg void OnBnClickedAddpage();
	afx_msg void OnBnClickedRemovepage();
	afx_msg void OnBnClickedPrevpage();
	afx_msg void OnBnClickedNextpage();
	void PageEaUpdate();
	CEdit MusicComposer;
	CEdit NowMusicLevel;
	CComboBox NowMusicPlace;
	CComboBox NowNotePrevKey;
	afx_msg void OnBnClickedNotedel();
};


