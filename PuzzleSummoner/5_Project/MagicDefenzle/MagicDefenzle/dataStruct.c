#include "stdafx.h"
#include "dataStruct.h"

/// 이하 캐릭터용
BOOL ListInit(zzList* list)
{
	if (ListIsEmpty(list))
	{
		list->count = 0;
		list->head = (OneNode*)malloc(sizeof(OneNode));
		return TRUE;
	}
	return FALSE;
}

BOOL ListIsEmpty(zzList* list)
{
	if (list->count == 0)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL ListInsertFirst(zzList* list, zzSummonee value)
{
	OneNode* newNode = (OneNode*)malloc(sizeof(OneNode));
	if (newNode)
	{
		ZeroMemory(newNode, sizeof(OneNode));
		newNode->data = value;
		newNode->next = list->head->next;
		list->head->next = newNode;
		list->count++;
		return TRUE;
	}
	return FALSE;
}
BOOL ListInsertLast(zzList* list, zzSummonee value)
{
	if (ListIsEmpty(list))
	{
		return ListInsertFirst(list, value);
	}
	OneNode* newNode = (OneNode*)malloc(sizeof(OneNode));

	if (newNode)
	{
		ZeroMemory(newNode, sizeof(OneNode));
		newNode->data = value;

		OneNode* prev = ListFindAtNode(list, list->count - 1);
		prev->next = newNode;
		list->count++;
		return TRUE;
	}
	return FALSE;
}

BOOL ListInsert(zzList* list, int pos, zzSummonee value)
{
	if (pos <= 0)
	{
		return ListInsertFirst(list, value);
	}
	else if (pos < list->count)
	{
		OneNode* newNode = (OneNode*)malloc(sizeof(OneNode));
		if (newNode)
		{
			ZeroMemory(newNode, sizeof(OneNode));
			newNode->data = value;

			OneNode* prev = ListFindAtNode(list, pos - 1);
			newNode->next = prev->next;
			prev->next = newNode;
			list->count++;
			return TRUE;
		}
		return FALSE;
	}
	else
	{
		return ListInsertLast(list, value);
	}
}

OneNode* ListFindAtNode(zzList* list, int pos)
{
	if (ListIsEmpty(list))
	{
		return NULL;
	}
	else if (pos > list->count)
	{
		return NULL;
	}
	else
	{
		OneNode* tmp = list->head;
		for (int i = 0; i <= pos; i++)
		{
			tmp = tmp->next;
		}
		return tmp;
	}
}

BOOL ListRemoveFirst(zzList* list)
{
	if (!ListIsEmpty(list))
	{
		OneNode* tmp = list->head->next;
		if (tmp != NULL)
		{
			list->head->next = tmp->next;
			list->count--;
			FreeCharacterMalloc(&tmp->data);
			free(tmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL ListRemoveLast(zzList* list)
{
	if (!ListIsEmpty(list))
	{
		OneNode* prev = ListFindAtNode(list, list->count - 2);
		OneNode* tmp = prev->next;
		prev->next = NULL;
		list->count--;
		FreeCharacterMalloc(&tmp->data);
		free(tmp);
		return TRUE;
	}
	return FALSE;
}

BOOL ListRemove(zzList* list, int pos)
{
	if (pos <= 0)
	{
		return ListRemoveFirst(list);
	}
	else if (pos < list->count)
	{
		OneNode* prev = ListFindAtNode(list, pos - 1);
		OneNode* tmp = prev->next;
		prev->next = tmp->next;
		list->count--;
		FreeCharacterMalloc(&tmp->data);
		free(tmp);
		return TRUE;
	}
	else
	{
		return ListRemoveLast(list);
	}
}

///이하 스테이지 빌더용
//이하 스테이지용
BOOL stgListInsertFirst(zzList* list, zzOneStage value)
{
	OneNode* newNode = (OneNode*)malloc(sizeof(OneNode));
	if (newNode)
	{
		ZeroMemory(newNode, sizeof(OneNode));
		newNode->d_stg = value;
		newNode->next = list->head->next;
		list->head->next = newNode;
		list->count++;
		return TRUE;
	}
	return FALSE;
}
BOOL stgListInsertLast(zzList* list, zzOneStage value)
{
	if (ListIsEmpty(list))
	{
		return stgListInsertFirst(list, value);
	}
	OneNode* newNode = (OneNode*)malloc(sizeof(OneNode));

	if (newNode)
	{
		ZeroMemory(newNode, sizeof(OneNode));
		newNode->d_stg = value;

		OneNode* prev = stgListFindAtNode(list, list->count - 1);
		prev->next = newNode;
		list->count++;
		return TRUE;
	}
	return FALSE;
}

BOOL stgListInsert(zzList* list, int pos, zzOneStage value)
{
	if (pos <= 0)
	{
		return stgListInsertFirst(list, value);
	}
	else if (pos < list->count)
	{
		OneNode* newNode = (OneNode*)malloc(sizeof(OneNode));
		if (newNode)
		{
			ZeroMemory(newNode, sizeof(OneNode));
			newNode->d_stg = value;

			OneNode* prev = stgListFindAtNode(list, pos - 1);
			newNode->next = prev->next;
			prev->next = newNode;
			list->count++;
			return TRUE;
		}
		return FALSE;
	}
	else
	{
		return stgListInsertLast(list, value);
	}
}

OneNode* stgListFindAtNode(zzList* list, int pos)
{
	if (ListIsEmpty(list))
	{
		return NULL;
	}
	else if (pos > list->count)
	{
		return NULL;
	}
	else
	{
		OneNode* tmp = list->head;
		for (int i = 0; i <= pos; i++)
		{
			tmp = tmp->next;
		}
		return tmp;
	}
}

BOOL stgListRemoveFirst(zzList* list)
{
	if (!ListIsEmpty(list))
	{
		OneNode* tmp = list->head->next;
		if (tmp != NULL)
		{
			list->head->next = tmp->next;
			list->count--;
			free(tmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL stgListRemoveLast(zzList* list)
{
	if (!ListIsEmpty(list))
	{
		OneNode* prev = stgListFindAtNode(list, list->count - 2);
		OneNode* tmp = prev->next;
		prev->next = NULL;
		list->count--;
		free(tmp);
		return TRUE;
	}
	return FALSE;
}

BOOL stgListRemove(zzList* list, int pos)
{
	if (pos <= 0)
	{
		return stgListRemoveFirst(list);
	}
	else if (pos < list->count)
	{
		OneNode* prev = stgListFindAtNode(list, pos - 1);
		OneNode* tmp = prev->next;
		prev->next = tmp->next;
		list->count--;
		free(tmp);
		return TRUE;
	}
	else
	{
		return stgListRemoveLast(list);
	}
}


// 이하 몬스터용
BOOL monListInit(zzOneStage* list)
{
	if (monListIsEmpty(list))
	{
		list->count = 0;
		list->head = (OneNode*)malloc(sizeof(OneNode));
		return TRUE;
	}
	return FALSE;
}

BOOL monListIsEmpty(zzOneStage* list)
{
	if (list->count == 0)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL monListInsertFirst(zzOneStage* list, zzOneMonster value)
{
	OneNode* newNode = (OneNode*)malloc(sizeof(OneNode));
	if (newNode)
	{
		ZeroMemory(newNode, sizeof(OneNode));
		newNode->d_mon = value;
		newNode->next = list->head->next;
		list->head->next = newNode;
		list->count++;
		return TRUE;
	}
	return FALSE;
}
BOOL monListInsertLast(zzOneStage* list, zzOneMonster value)
{
	if (monListIsEmpty(list))
	{
		return monListInsertFirst(list, value);
	}
	OneNode* newNode = (OneNode*)malloc(sizeof(OneNode));
	if (newNode)
	{
		ZeroMemory(newNode, sizeof(OneNode));
		newNode->d_mon = value;

		OneNode* prev = monListFindAtNode(list, list->count - 1);
		prev->next = newNode;
		list->count++;
		return TRUE;
	}
	return FALSE;
}

BOOL monListInsert(zzOneStage* list, int pos, zzOneMonster value)
{
	if (pos <= 0)
	{
		return monListInsertFirst(list, value);
	}
	else if (pos < list->count)
	{
		OneNode* newNode = (OneNode*)malloc(sizeof(OneNode));
		if (newNode)
		{
			ZeroMemory(newNode, sizeof(OneNode));
			newNode->d_mon = value;

			OneNode* prev = monListFindAtNode(list, pos - 1);
			newNode->next = prev->next;
			prev->next = newNode;
			list->count++;
			return TRUE;
		}
		return FALSE;
	}
	else
	{
		return monListInsertLast(list, value);
	}
}

OneNode* monListFindAtNode(zzOneStage* list, int pos)
{
	if (monListIsEmpty(list))
	{
		return NULL;
	}
	else if (pos > list->count)
	{
		return NULL;
	}
	else
	{
		OneNode* tmp = list->head;
		for (int i = 0; i <= pos; i++)
		{
			tmp = tmp->next;
		}
		return tmp;
	}
}

BOOL monListRemoveFirst(zzOneStage* list)
{
	if (!monListIsEmpty(list))
	{
		OneNode* tmp = list->head->next;
		if (tmp != NULL)
		{
			list->head->next = tmp->next;
			list->count--;
			free(tmp);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL monListRemoveLast(zzOneStage* list)
{
	if (!monListIsEmpty(list))
	{
		OneNode* prev = monListFindAtNode(list, list->count - 2);
		OneNode* tmp = prev->next;
		prev->next = NULL;
		list->count--;
		free(tmp);
		return TRUE;
	}
	return FALSE;
}

BOOL monListRemove(zzOneStage* list, int pos)
{
	if (pos <= 0)
	{
		return monListRemoveFirst(list);
	}
	else if (pos < list->count)
	{
		OneNode* prev = monListFindAtNode(list, pos - 1);
		OneNode* tmp = prev->next;
		prev->next = tmp->next;
		list->count--;
		free(tmp);
		return TRUE;
	}
	else
	{
		return monListRemoveLast(list);
	}
}