#pragma once


BOOL ListInit(zzList* list);
BOOL ListIsEmpty(zzList* list);
BOOL ListInsertFirst(zzList* list, zzSummonee value);
BOOL ListInsertLast(zzList* list, zzSummonee value);
BOOL ListInsert(zzList* list, int pos, zzSummonee value);
OneNode* ListFindAtNode(zzList* list, int pos);
BOOL ListRemoveFirst(zzList* list);
BOOL ListRemoveLast(zzList* list);
BOOL ListRemove(zzList* list, int pos);

BOOL stgListInsertFirst(zzList* list, zzOneStage value);
BOOL stgListInsertLast(zzList* list, zzOneStage value);
BOOL stgListInsert(zzList* list, int pos, zzOneStage value);
OneNode* stgListFindAtNode(zzList* list, int pos);
BOOL stgListRemoveFirst(zzList* list);
BOOL stgListRemoveLast(zzList* list);
BOOL stgListRemove(zzList* list, int pos);

BOOL monListInit(zzOneStage* list);
BOOL monListIsEmpty(zzOneStage* list);
BOOL monListInsertFirst(zzOneStage* list, zzOneMonster value);
BOOL monListInsertLast(zzOneStage* list, zzOneMonster value);
BOOL monListInsert(zzOneStage* list, int pos, zzOneMonster value);
OneNode* monListFindAtNode(zzOneStage* list, int pos);
BOOL monListRemoveFirst(zzOneStage* list);
BOOL monListRemoveLast(zzOneStage* list);
BOOL monListRemove(zzOneStage* list, int pos);