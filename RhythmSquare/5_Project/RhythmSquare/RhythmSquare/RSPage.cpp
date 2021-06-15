#include "pchApp.h"

#include "RSPage.h"

RSPage::RSPage() : m_Type(0), m_Level(0)
{
	m_Monster = nullptr;
	m_NoteEa = 0;
	isDraw = false;
	onRemove = false;
	removeCount = 0;
}

RSPage::~RSPage()
{

}

void RSPage::InitMonsterInfo()
{
	m_NoteEa = m_Note.size();


	if (m_Monster == nullptr)
	{
		m_Monster = new Monster(m_Level, m_Type);
	}
	m_Monster->SetMonsterInfo();
}

void RSPage::Render()
{
	if (isDraw)
	{
		if (onRemove)
		{
			removeCount++;
		}
		if (removeCount > 60)
		{
			isDraw = false;
		}
		m_Monster->OnRender();
	}
}

void RSPage::GoRemove()
{
	onRemove = true;
}
