#pragma once



class RSPage
{
public:
	RSPage();
	~RSPage();

	std::vector<RSQNote*> m_Note; // 몬스터가 맞아야 하는 노트 묶음

	void InitMonsterInfo();
	void Render();
	void GoRemove();

	// 속성
	int m_Type; // 0 ~ 2
	// 레벨
	int m_Level; // 0 ~ 2

	int m_NoteEa;
	Monster* m_Monster;
	bool isDraw;
	bool onRemove;
	int removeCount;

	// 몬스터가 들고있는 아이템(하트 등)
private:
	

};

