#include "pchTool.h"
#include "FileIO.h"

int RSSaveSheet(LPCTSTR filepath, RSSheet* Sheet)
{
	HANDLE hFile;
	hFile = CreateFile(filepath,		// 파일 경로
		GENERIC_READ | GENERIC_WRITE,		// 읽기/쓰기 모드
		0,									// 공유 모드. 그런거 없다.
		NULL,								// 보안 속성. 역시 관련없음.
		CREATE_ALWAYS,						// 파일을 생성할 것인가 어쩔 것인가
		FILE_ATTRIBUTE_NORMAL,				// 파일 속성
		NULL);								// 템플릿 파일?

	if (hFile == INVALID_HANDLE_VALUE) { // 파일을 열 때 에러면.
		return 0;
	}

	DWORD dwWritten;
	size_t tmpSize;

	tmpSize = wcslen(&Sheet->m_SongName);
	WriteFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL);
	WriteFile(hFile, &Sheet->m_SongName, tmpSize, &dwWritten, NULL); // 곡 제목
	tmpSize = wcslen(&Sheet->m_Composer);
	WriteFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL);
	WriteFile(hFile, &Sheet->m_Composer, tmpSize, &dwWritten, NULL); // 작곡가
	WriteFile(hFile, &Sheet->m_Level, sizeof(int), &dwWritten, NULL); // level
	WriteFile(hFile, &Sheet->m_SongLength, sizeof(float), &dwWritten, NULL); // 곡 길이
	WriteFile(hFile, &Sheet->m_Place, sizeof(int), &dwWritten, NULL); // 지역
	WriteFile(hFile, &Sheet->m_BPM, sizeof(int), &dwWritten, NULL); // BPM
	


	tmpSize = Sheet->m_Page.size(); // 페이지 수
	WriteFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL); 
	// 여기에 시트의 정보를 넣어야 합니다.

	for (int i = 0; i < Sheet->m_Page.size(); i++)
	{
		// 여기에 페이지당 몬스터의 정보를 넣어야 합니다.
		WriteFile(hFile, &Sheet->m_Page[i]->m_Type, sizeof(int), &dwWritten, NULL); // 몬스터 속성
		WriteFile(hFile, &Sheet->m_Page[i]->m_Level, sizeof(int), &dwWritten, NULL); // 몬스터 레벨

		// 페이지에 할당된 노트 배열
		tmpSize = Sheet->m_Page[i]->m_Note.size();
		WriteFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL);
		for (int j = 0; j <Sheet->m_Page[i]->m_Note.size(); j++)
		{
			float tmpF = Sheet->m_Page[i]->m_Note[j]->GetTime();
			int tmpK = Sheet->m_Page[i]->m_Note[j]->GetKey();
			WriteFile(hFile, &tmpF, sizeof(float), &dwWritten, NULL); // 노트 등장 시간
			WriteFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // 노트의 키
			tmpK = Sheet->m_Page[i]->m_Note[j]->GetPrevKey();
			WriteFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // 이전 노트의 키
			tmpK = Sheet->m_Page[i]->m_Note[j]->GetType();
			WriteFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // 노트의 타입

			// 여기에 노트의 정보를 넣어야 합니다.
		}
	}

	CloseHandle(hFile);

	return 0;
}

int RSLoadSheet(LPCTSTR filepath, RSSheet* Sheet) // 비어있는 시트를 넣어야 합니다.
{
	HANDLE hFile;
	hFile = CreateFile(filepath,		// 파일 경로
		GENERIC_READ | GENERIC_WRITE,		// 읽기/쓰기 모드
		0,									// 공유 모드. 그런거 없다.
		NULL,								// 보안 속성. 역시 관련없음.
		OPEN_EXISTING,						// 파일을 생성할 것인가 어쩔 것인가
		FILE_ATTRIBUTE_NORMAL,				// 파일 속성
		NULL);								// 템플릿 파일?

	if (hFile == INVALID_HANDLE_VALUE) { // 파일을 열 때 에러면.
		return 0;
	}

	DWORD dwWritten; // read가 되어야 하지만 귀찮다...

	size_t tmpSize;

	ReadFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL);
	ReadFile(hFile, &Sheet->m_SongName, tmpSize, &dwWritten, NULL); // 곡 제목
	ReadFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL);
	ReadFile(hFile, &Sheet->m_Composer, tmpSize, &dwWritten, NULL); // 작곡가
	ReadFile(hFile, &Sheet->m_Level, sizeof(int), &dwWritten, NULL); // level
	ReadFile(hFile, &Sheet->m_SongLength, sizeof(float), &dwWritten, NULL);
	ReadFile(hFile, &Sheet->m_Place, sizeof(int), &dwWritten, NULL); // 지역
	ReadFile(hFile, &Sheet->m_BPM, sizeof(int), &dwWritten, NULL); // BPM


	// 여기까지 시트의 정보를 받습니다

	ReadFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL); // 페이지 배열 크기
	size_t PageSize = tmpSize;
	for (size_t i = 0; i < PageSize; i++)
	{
		RSPage* tmpPage = new RSPage();
		ReadFile(hFile, &tmpPage->m_Type, sizeof(int), &dwWritten, NULL); // 몬스터 속성
		ReadFile(hFile, &tmpPage->m_Level, sizeof(int), &dwWritten, NULL); // 몬스터 레벨
		// 여기까지 페이지의 정보를 받습니다.
		//Sheet->m_Page.push_back(tmpPage);
		// 페이지에 할당된 노트 배열
		ReadFile(hFile, &tmpSize, sizeof(size_t), &dwWritten, NULL); // 노트 배열 크기
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

			ReadFile(hFile, &tmpF, sizeof(float), &dwWritten, NULL); // 노트 등장 시간
			tmpNote->SetTime(tmpF);
			ReadFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // 노트의 키
			tmpNote->SetKey(tmpK);
			ReadFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // 이전 노트의 키
			tmpNote->SetPrevKey(tmpK);
			ReadFile(hFile, &tmpK, sizeof(int), &dwWritten, NULL); // 노트의 타입
			tmpNote->SetType(tmpK);
			// 여기까지 노트의 정보를 받습니다.

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
