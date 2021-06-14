#include "stdafx.h"
#include "SnL.h"


int zzSaveMap(LPCTSTR filepath, zzList* list)
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
	OneNode* SaveStage;
	OneNode* SaveMonster;

	WriteFile(hFile, &list->count, sizeof(int), &dwWritten, NULL); // �������� ��
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



	ReadFile(hFile, &NumofSavedStage, sizeof(int), &dwWritten, NULL); // �������� ��
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

