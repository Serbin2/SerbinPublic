#include "stdafx.h"
#include "SnL.h"


int zzSaveMap(LPCTSTR filepath, zzList* list)
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
	OneNode* SaveStage;
	OneNode* SaveMonster;

	WriteFile(hFile, &list->count, sizeof(int), &dwWritten, NULL); // 스테이지 수
	for (int i = 0; i < list->count; i++)
	{
		SaveStage = stgListFindAtNode(list, i);
		WriteFile(hFile, &SaveStage->d_stg.stageNumber, sizeof(int), &dwWritten, NULL);
		WriteFile(hFile, &SaveStage->d_stg.stageHP, sizeof(int), &dwWritten, NULL);
		WriteFile(hFile, &SaveStage->d_stg.stageTime, sizeof(int), &dwWritten, NULL);
		WriteFile(hFile, &SaveStage->d_stg.stageSpeed, sizeof(int), &dwWritten, NULL);
		WriteFile(hFile, &SaveStage->d_stg.count, sizeof(int), &dwWritten, NULL);
		for (int j = 0; j < SaveStage->d_stg.count; j++)
		{
			SaveMonster = monListFindAtNode(&SaveStage->d_stg, j);
			WriteFile(hFile, &SaveMonster->d_mon.TYPE, sizeof(int), &dwWritten, NULL);
			WriteFile(hFile, &SaveMonster->d_mon.level, sizeof(int), &dwWritten, NULL);
			WriteFile(hFile, &SaveMonster->d_mon.spawntime, sizeof(int), &dwWritten, NULL);
		}
	}

	CloseHandle(hFile);

	return 0;
}

int zzLoadMap(LPCTSTR filepath, zzList* list)
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
	OneNode* SaveStage;
	zzOneStage Loadstagedummy;
	zzOneMonster Loadmonsterdummy;
	int NumofSavedStage = 0;

	for (int i = 0; i < list->count; i)
	{
		SaveStage = stgListFindAtNode(list, list->count - 1);
		while (monListRemoveLast(&SaveStage->d_stg))
		{
		}
		free(SaveStage->d_stg.head);
		stgListRemoveLast(list);
	}



	ReadFile(hFile, &NumofSavedStage, sizeof(int), &dwWritten, NULL); // 스테이지 수
	for (int i = 0; i < NumofSavedStage; i++)
	{

		ReadFile(hFile, &Loadstagedummy.stageNumber, sizeof(int), &dwWritten, NULL);
		ReadFile(hFile, &Loadstagedummy.stageHP, sizeof(int), &dwWritten, NULL);
		ReadFile(hFile, &Loadstagedummy.stageTime, sizeof(int), &dwWritten, NULL);
		ReadFile(hFile, &Loadstagedummy.stageSpeed, sizeof(int), &dwWritten, NULL);
		ReadFile(hFile, &Loadstagedummy.numofMonster, sizeof(int), &dwWritten, NULL);
		stgListInsertLast(list, Loadstagedummy);
		SaveStage = stgListFindAtNode(list, i);
		SaveStage->d_stg.count = 0;
		monListInit(&SaveStage->d_stg);
		for (int j = 0; j < SaveStage->d_stg.numofMonster; j++)
		{
			ReadFile(hFile, &Loadmonsterdummy.TYPE, sizeof(int), &dwWritten, NULL);
			ReadFile(hFile, &Loadmonsterdummy.level, sizeof(int), &dwWritten, NULL);
			ReadFile(hFile, &Loadmonsterdummy.spawntime, sizeof(int), &dwWritten, NULL);
			monListInsertLast(&SaveStage->d_stg, Loadmonsterdummy);
		}
	}

	CloseHandle(hFile);

	return 0;
}

