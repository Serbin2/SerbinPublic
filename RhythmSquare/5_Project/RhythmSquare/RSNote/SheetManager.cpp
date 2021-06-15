#include "pchTool.h"
#include "SheetManager.h"

SheetManager::SheetManager() : NowEditNote(0) , NowEditPage(0)
{

}

SheetManager::~SheetManager()
{

}

void ViewManager::SetInfoView(MusicInfo* view)
{
	InfoView = view;
}

void ViewManager::SetMainView(CMainView* view)
{
	MainView = view;
}
