#pragma once



class RSPage
{
public:
	RSPage();
	~RSPage();

	std::vector<RSQNote*> m_Note; // ���Ͱ� �¾ƾ� �ϴ� ��Ʈ ����

	void InitMonsterInfo();
	void Render();
	void GoRemove();

	// �Ӽ�
	int m_Type; // 0 ~ 2
	// ����
	int m_Level; // 0 ~ 2

	int m_NoteEa;
	Monster* m_Monster;
	bool isDraw;
	bool onRemove;
	int removeCount;

	// ���Ͱ� ����ִ� ������(��Ʈ ��)
private:
	

};

