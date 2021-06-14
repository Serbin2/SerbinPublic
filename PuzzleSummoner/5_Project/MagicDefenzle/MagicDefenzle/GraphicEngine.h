#pragma once
#include "zzDefiner.h"

void zzInitilizeEngine(HINSTANCE hinst, HWND hWnd, HDC hDC, int width, int height);
void ClearScreen();

/// �׸���� ���� �Ϻ��� �Լ���
/// (BitBlt�ø�� �� �� ������ ��)

// ȭ�鿡 ��Ʈ���� �׸���.
void DrawBitmap(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY);

// �ϳ��� ��Ʈ���� �׸���. (���ù���)
void DrawBitmap_Simple(int posX, int posY, zzBitmap* bitmap);

// ȭ�鿡 ��������Ʈ �ϳ��� �׸���.
void DrawSprite(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY);

// ȭ�鿡 ��������Ʈ ��� Ÿ�� �ϳ��� �׸���.
void DrawTile(int posX, int posY, zzBitmap* bitmap, int NumofTile, int picktile, int speciality, int numofspec);

// ȭ�鿡 ��������Ʈ �ϳ��� �׸���. (���ù���)
void DrawSprite_Simple(int posX, int posY, zzBitmap* bitmap);


void zzDrawAlphaBlendSprite(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY, int level);
void zxDrawAlphaBlendSprite(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY, int dstX, int dstY, int level);
void zzDrawAlphaBlendSprite_Simple(int posX, int posY, zzBitmap* bitmap);
void FreeCharacterMalloc(zzSummonee* character);
void CreateCharacterRes(zzSummonee* character, zzBitmap* sheet, int motions, int frames, int delay);
void CreateSprites(OneMotion* motion, zzBitmap* sheet, int AniIndex, int NumofAni);



void Animate_PickPos(int dstX, int dstY, zzSummonee* character, int AnimationIndex, int level);

void DrawBitmap_PickPos(int dstX, int dstY, int dstW, int dstH, zzBitmap* sheet, int oriX, int oriY, int width, int height, int level);


// ȭ�鿡 ���ڸ� ��� �Լ���
BOOL TextOutp(HDC hdc, int x, int y, const char* pch, ...);
BOOL _TT(int x, int y, const char* pch, ...);


// ȭ�鿡 ���������� Blit�� �Ѵ�. (�����->ȭ��)
void DrawAllToScreen();


/// ��Ʈ�� �ε� ����

// ���Ͽ��� ��Ʈ���� �ε��Ѵ�.
void LoadBitmap_FromFile(zzBitmap* bitmap, char* filePath);

// ���Ͽ��� ��Ʈ���� �ε��Ѵ�.
void LoadBitmap_FromFile2(zzBitmap* bitmap, char* filePath);

// ���Ͽ��� ��Ʈ���� �ε��Ѵ�.
// ��(DIB -> DDB ��ȯ. LoadImage/LoadBitmap �� ��Ÿ �Լ���ε� ����)
HBITMAP MakeDDBFromDIB(HDC hdc, char* FileLocation);
