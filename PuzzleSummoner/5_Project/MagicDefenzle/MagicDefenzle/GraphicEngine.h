#pragma once
#include "zzDefiner.h"

void zzInitilizeEngine(HINSTANCE hinst, HWND hWnd, HDC hDC, int width, int height);
void ClearScreen();

/// 그리기용 가장 하부의 함수들
/// (BitBlt시리즈를 한 번 래핑할 뿐)

// 화면에 비트맵을 그린다.
void DrawBitmap(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY);

// 하나의 비트맵을 그린다. (심플버전)
void DrawBitmap_Simple(int posX, int posY, zzBitmap* bitmap);

// 화면에 스프라이트 하나를 그린다.
void DrawSprite(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY);

// 화면에 스프라이트 기반 타일 하나를 그린다.
void DrawTile(int posX, int posY, zzBitmap* bitmap, int NumofTile, int picktile, int speciality, int numofspec);

// 화면에 스프라이트 하나를 그린다. (심플버전)
void DrawSprite_Simple(int posX, int posY, zzBitmap* bitmap);


void zzDrawAlphaBlendSprite(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY, int level);
void zxDrawAlphaBlendSprite(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY, int dstX, int dstY, int level);
void zzDrawAlphaBlendSprite_Simple(int posX, int posY, zzBitmap* bitmap);
void FreeCharacterMalloc(zzSummonee* character);
void CreateCharacterRes(zzSummonee* character, zzBitmap* sheet, int motions, int frames, int delay);
void CreateSprites(OneMotion* motion, zzBitmap* sheet, int AniIndex, int NumofAni);



void Animate_PickPos(int dstX, int dstY, zzSummonee* character, int AnimationIndex, int level);

void DrawBitmap_PickPos(int dstX, int dstY, int dstW, int dstH, zzBitmap* sheet, int oriX, int oriY, int width, int height, int level);


// 화면에 문자를 찍는 함수들
BOOL TextOutp(HDC hdc, int x, int y, const char* pch, ...);
BOOL _TT(int x, int y, const char* pch, ...);


// 화면에 최종적으로 Blit을 한다. (백버퍼->화면)
void DrawAllToScreen();


/// 비트맵 로드 관련

// 파일에서 비트맵을 로드한다.
void LoadBitmap_FromFile(zzBitmap* bitmap, char* filePath);

// 파일에서 비트맵을 로드한다.
void LoadBitmap_FromFile2(zzBitmap* bitmap, char* filePath);

// 파일에서 비트맵을 로드한다.
// ※(DIB -> DDB 전환. LoadImage/LoadBitmap 외 여타 함수들로도 가능)
HBITMAP MakeDDBFromDIB(HDC hdc, char* FileLocation);
