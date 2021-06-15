#pragma once



class RSPage
{
public:
	RSPage();
	~RSPage();

	std::vector<RSQNote*> m_Note; // 몬스터가 맞아야 하는 노트 묶음


	

	//Monster m_Monster;
	// 속성
	int m_Type;
	// 레벨
	int m_Level;

	// 스프라이트 및 기타 정보는 함수로 받아오기

	// 몬스터가 들고있는 아이템(하트 등)

	

};

