#pragma once


class RSSheet 
{
public:
	RSSheet();
	~RSSheet();


	std::vector<RSPage*> m_Page;
	// �ٹ� Ŀ��(ID)
	wchar_t m_SongName;
	wchar_t m_Composer;
	float m_SongLength;
	int m_Level;

	int m_Place; // 0 : none  1: �縷  2 : �ٴ�  3 : ��
	float m_BPM; 
	
#ifndef RSTOOL
public:
	

	// �������� ����� ��Ʈ�� ���δ� ��Ʈ�� ��ȯ
	void RestoreNotePool();

	// input�� 0~7 �� ������ �޴´�
	void GetInput(int input, float inputTime);

	// ��Ʈ�� �׸��� �Լ�
	void RenderNote(float PlayingTime, float TimePerBeat); // ��Ʈ���� �� ����

	int m_Combo;
	int m_Miss;
	int m_Good;
	int m_Perfect;
	int m_Early;
	int m_Late;

private:
	std::vector<RSQNote*> m_Note[8];

	
#endif

public:
	// �̻� ���� ����¿� ��ϵ� ������
	// ���� ���� ����¿� ��� �ȵ� ������
	int m_TotalNote;

};

