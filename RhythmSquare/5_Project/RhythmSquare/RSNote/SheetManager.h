#pragma once



class SheetManager: public Singleton<SheetManager>
{
public:
	SheetManager();
	~SheetManager();

	//MusicInfo* InfoView;
	RSSheet m_Sheet;
	std::vector<RSQNote*> m_Note;
	std::vector<RSPage*> m_Page;
	int NowEditNote;
	int NowEditPage;
};

class ViewManager : public Singleton<ViewManager>
{
public:
	MusicInfo* InfoView;
	CMainView* MainView;


	void SetInfoView(MusicInfo* view);
	void SetMainView(CMainView* view);
};