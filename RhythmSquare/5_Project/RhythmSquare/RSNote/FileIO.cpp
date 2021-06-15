#include "pchTool.h"
#include "FileIO.h"

int RSSaveSheet(LPCTSTR filepath, RSSheet* Sheet)
{
	HANDLE hFile;
	hFile = CreateFile(filepath,		// ���� ���
		GENERIC_READ | GENERIC_WRITE,		// �б�/���� ���
		0,									// ���� ���. �׷��� ����.
		NULL,								// ���� �Ӽ�. ���� ���þ���.
		CREATE_ALWAYS,						// ������ ������ ���ΰ� ��¿ ���ΰ�
		FILE_ATTRIBUTE_NORMAL,				// ���� �Ӽ�
		NULL);								// ���ø� ����?

	if (hFile == INVALID_HANDLE_VALUE) { // ������ �� �� ������.
		return 0;
	}

	DWORD dwWritten;
	size_t tmpSize;

	tmpSize = wcslen(&Sheet->m_SongName);
	WriteFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL);
	WriteFile(hFile, &Sheet->m_SongName, tmpSize, &dwWritten, NULL); // �� ����
	tmpSize = wcslen(&Sheet->m_Composer);
	WriteFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL);
	WriteFile(hFile, &Sheet->m_Composer, tmpSize, &dwWritten, NULL); // �۰
	WriteFile(hFile, &Sheet->m_Level, sizeof(int), &dwWritten, NULL); // level
	WriteFile(hFile, &Sheet->m_SongLength, sizeof(float), &dwWritten, NULL); // �� ����
	WriteFile(hFile, &Sheet->m_Place, sizeof(int), &dwWritten, NULL); // ����
	WriteFile(hFile, &Sheet->m_BPM, sizeof(int), &dwWritten, NULL); // BPM
	


	tmpSize = Sheet->m_Page.size(); // ������ ��
	WriteFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL); 
	// ���⿡ ��Ʈ�� ������ �־�� �մϴ�.

	for (int i = 0; i < Sheet->m_Page.size(); i++)
	{
		// ���⿡ �������� ������ ������ �־�� �մϴ�.
		WriteFile(hFile, &Sheet->m_Page[i]->m_Type, sizeof(int), &dwWritten, NULL); // ���� �Ӽ�
		WriteFile(hFile, &Sheet->m_Page[i]->m_Level, sizeof(int), &dwWritten, NULL); // ���� ����

		// �������� �Ҵ�� ��Ʈ �迭
		tmpSize = Sheet->m_Page[i]->m_Note.size();
		WriteFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL);
		for (int j = 0; j <Sheet->m_Page[i]->m_Note.size(); j++)
		{
			float tmpF = Sheet->m_Page[i]->m_Note[j]->GetTime();
			int tmpK = Sheet->m_Page[i]->m_Note[j]->GetKey();
			WriteFile(hFile, &tmpF, sizeof(float), &dwWritten, NULL); // ��Ʈ ���� �ð�
			WriteFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // ��Ʈ�� Ű
			tmpK = Sheet->m_Page[i]->m_Note[j]->GetPrevKey();
			WriteFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // ���� ��Ʈ�� Ű
			tmpK = Sheet->m_Page[i]->m_Note[j]->GetType();
			WriteFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // ��Ʈ�� Ÿ��

			// ���⿡ ��Ʈ�� ������ �־�� �մϴ�.
		}
	}

	CloseHandle(hFile);

	return 0;
}

int RSLoadSheet(LPCTSTR filepath, RSSheet* Sheet) // ����ִ� ��Ʈ�� �־�� �մϴ�.
{
	HANDLE hFile;
	hFile = CreateFile(filepath,		// ���� ���
		GENERIC_READ | GENERIC_WRITE,		// �б�/���� ���
		0,									// ���� ���. �׷��� ����.
		NULL,								// ���� �Ӽ�. ���� ���þ���.
		OPEN_EXISTING,						// ������ ������ ���ΰ� ��¿ ���ΰ�
		FILE_ATTRIBUTE_NORMAL,				// ���� �Ӽ�
		NULL);								// ���ø� ����?

	if (hFile == INVALID_HANDLE_VALUE) { // ������ �� �� ������.
		return 0;
	}

	DWORD dwWritten; // read�� �Ǿ�� ������ ������...

	size_t tmpSize;

	ReadFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL);
	ReadFile(hFile, &Sheet->m_SongName, tmpSize, &dwWritten, NULL); // �� ����
	ReadFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL);
	ReadFile(hFile, &Sheet->m_Composer, tmpSize, &dwWritten, NULL); // �۰
	ReadFile(hFile, &Sheet->m_Level, sizeof(int), &dwWritten, NULL); // level
	ReadFile(hFile, &Sheet->m_SongLength, sizeof(float), &dwWritten, NULL);
	ReadFile(hFile, &Sheet->m_Place, sizeof(int), &dwWritten, NULL); // ����
	ReadFile(hFile, &Sheet->m_BPM, sizeof(int), &dwWritten, NULL); // BPM


	// ������� ��Ʈ�� ������ �޽��ϴ�

	ReadFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL); // ������ �迭 ũ��
	size_t PageSize = tmpSize;
	for (size_t i = 0; i < PageSize; i++)
	{
		RSPage* tmpPage = new RSPage();
		ReadFile(hFile, &tmpPage->m_Type, sizeof(int), &dwWritten, NULL); // ���� �Ӽ�
		ReadFile(hFile, &tmpPage->m_Level, sizeof(int), &dwWritten, NULL); // ���� ����
		// ������� �������� ������ �޽��ϴ�.
		//Sheet->m_Page.push_back(tmpPage);
		// �������� �Ҵ�� ��Ʈ �迭
		ReadFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL); // ��Ʈ �迭 ũ��
		size_t NoteSize = tmpSize;
		for (size_t j = 0; j < NoteSize; j++)
		{
			RSQNote* tmpNote = new RSQNote();
			float tmpF;
			int tmpK;
			//ReadFile(hFile, &tmpF, sizeof(float), &dwWritten, NULL);
			//ReadFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL);
			//tmpNote.SetTime(tmpF);
			//tmpNote.SetKey(tmpK);

			ReadFile(hFile, &tmpF, sizeof(float), &dwWritten, NULL); // ��Ʈ ���� �ð�
			tmpNote->SetTime(tmpF);
			ReadFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // ��Ʈ�� Ű
			tmpNote->SetKey(tmpK);
			ReadFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // ���� ��Ʈ�� Ű
			tmpNote->SetPrevKey(tmpK);
			ReadFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // ��Ʈ�� Ÿ��
			tmpNote->SetType(tmpK);
			// ������� ��Ʈ�� ������ �޽��ϴ�.

#ifdef RSTOOL
			tmpNote->SetPageNum(i);

#endif


			tmpPage->m_Note.push_back(tmpNote);
			//Sheet->m_Page[i]->m_Note.push_back(tmpNote);
		}
		Sheet->m_Page.push_back(tmpPage);
	}


	CloseHandle(hFile);

	return 0;
}
