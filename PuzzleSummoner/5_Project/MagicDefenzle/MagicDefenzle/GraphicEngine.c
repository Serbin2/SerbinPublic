#include "stdafx.h"
#include "GraphicEngine.h"

/// 모듈 레벨에서 전역인 변수들

HINSTANCE g_hInst;	// 인스턴스 핸들
HWND g_hWnd;		// 그리기를 할 윈도 (1개라고 가정)
HDC g_hDCMain;		// 메인DC. 화면에 그리는 용도
zzBitmap Backbuffer;// 백버퍼
BLENDFUNCTION BlenFunc;

/// 초기화 관련

// 그래픽스 라이브러리에 필요한 전역 변수들을 얻어온다.
// 이 때, 윈도는 1개라고 가정한다. 그리기 화면도 1개라고 가정함
void zzInitilizeEngine(HINSTANCE hinst, HWND hWnd, HDC hDC, int width, int height)
{
	g_hInst = hinst;
	g_hWnd = hWnd;
	g_hDCMain = hDC;

	if (width == 0)
	{
		width = SCREENWIDTH;
	}
	if (height == 0)
	{
		height = SCREENHEIGHT;
	}


	Backbuffer.hMemDC = CreateCompatibleDC(g_hDCMain);
	Backbuffer.hBitmap = CreateCompatibleBitmap(g_hDCMain, width, height);
	SelectObject(Backbuffer.hMemDC, Backbuffer.hBitmap);
	Backbuffer.Width = width;
	Backbuffer.Height = height;
}

void ClearScreen()
{
	PatBlt(Backbuffer.hMemDC, 0, 0, SCREENWIDTH, SCREENHEIGHT, BLACKNESS);
}

/// 그리기용 가장 하부의 함수들
/// (BitBlt시리즈를 한 번 래핑할 뿐)

// 하나의 스프라이트를 그린다. 블릿 방식은 Solid(SRCCOPY)
void DrawBitmap(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY)
{
	BitBlt(Backbuffer.hMemDC, posX, posY, bitmap->Width, bitmap->Height,
		bitmap->hMemDC, srcX, srcY, SRCCOPY);
}

// 하나의 스프라이트를 그린다. (심플버전)
void DrawBitmap_Simple(int posX, int posY, zzBitmap* bitmap)
{
	DrawBitmap(posX, posY, bitmap, 0, 0);
}

// 화면에 스프라이트 하나를 그린다.
void DrawSprite(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY)
{
	GdiTransparentBlt(Backbuffer.hMemDC, posX, posY, bitmap->Width, bitmap->Height,
		bitmap->hMemDC, srcX, srcY, bitmap->Width, bitmap->Height, bitmap->KeyColor);
}

// 화면에 타일 한칸을 그린다.
void DrawTile(int posX, int posY, zzBitmap* bitmap, int NumofTile, int picktile, int speciality, int numofspec)
{
	int TileWidth = (bitmap->Width / NumofTile);
	int TileHeight = bitmap->Height / numofspec;

	GdiTransparentBlt(Backbuffer.hMemDC, posX, posY, TileWidth, TileHeight,
		bitmap->hMemDC, TileWidth * picktile, TileHeight * speciality, TileWidth, TileHeight, bitmap->KeyColor);
}

// 화면에 스프라이트 하나를 그린다. (심플버전)
void DrawSprite_Simple(int posX, int posY, zzBitmap* bitmap)
{
	DrawSprite(posX, posY, bitmap, 0, 0);
}

// 화면에 알파블렌드를 그린다.
void zzDrawAlphaBlendSprite(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY, int level)
{

	// Blend Function
	BlenFunc.BlendOp = AC_SRC_OVER;
	BlenFunc.BlendFlags = 0;
	BlenFunc.AlphaFormat = AC_SRC_ALPHA;
	BlenFunc.SourceConstantAlpha = level;	// 전체 알파값을 조절하며, pre-multiplied에 반영된다.

	/// 알파블랜딩
	/// 주의! Per-Pixel Alpha Blending을 하려면,
	/// 1. 알파채널이 있어야 함. (32비트)
	/// 2. Pre-Multiplied Alpha Image이어야 함.
	GdiAlphaBlend(Backbuffer.hMemDC,
		posX, posY, bitmap->Width, bitmap->Height,
		bitmap->hMemDC,
		srcX, srcY, bitmap->Width, bitmap->Height,
		BlenFunc); // blend function

}

void zxDrawAlphaBlendSprite(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY, int dstX, int dstY, int level)
{

	// Blend Function
	BlenFunc.BlendOp = AC_SRC_OVER;
	BlenFunc.BlendFlags = 0;
	BlenFunc.AlphaFormat = AC_SRC_ALPHA;
	BlenFunc.SourceConstantAlpha = level;	// 전체 알파값을 조절하며, pre-multiplied에 반영된다.

	/// 알파블랜딩
	/// 주의! Per-Pixel Alpha Blending을 하려면,
	/// 1. 알파채널이 있어야 함. (32비트)
	/// 2. Pre-Multiplied Alpha Image이어야 함.
	GdiAlphaBlend(Backbuffer.hMemDC,
		posX, posY, dstX, dstY,
		bitmap->hMemDC,
		srcX, srcY, dstX, dstY,
		BlenFunc); // blend function

}

void zzDrawAlphaBlendSprite_Simple(int posX, int posY, zzBitmap* bitmap)
{
	zzDrawAlphaBlendSprite(posX, posY, bitmap, 0, 0, 255);
}


/// 아래의 캐릭터 셋팅 메모리를 풀어준다
void FreeCharacterMalloc(zzSummonee* character)
{
	for (int i = 0; i < character->NumofAni; i++)
	{
		free(character->motions[i].sprites);
	}
	free(character->motions);
}

/// 캐릭터 셋팅
void CreateCharacterRes(zzSummonee* character, zzBitmap* sheet, int motions, int frames, int delay)
{
	// 원본 시트
	character->sheet = sheet;

	// 애니의 수를 동적할당한다.
	character->NumofAni = motions;
	character->motions = (OneMotion*)malloc(sizeof(OneMotion) * character->NumofAni);

	// 동적 할당 한 모션 들을 초기화 한다.
	for (int i = 0; i < character->NumofAni; i++)
	{
		// 매 모션을 초기화
		character->motions[i].sheet = sheet;
		character->motions[i].spriteNum = frames;
		character->motions[i].nowFrame = 0;
		character->motions[i].delayFrame = delay;

		// 모션에 다수의 스프라이트들을 동적할당 및 초기화를 해 준다.
		CreateSprites(&character->motions[i], sheet, i, motions);
	}
}

/// 모션을 셋팅해준다. 스프라이트 들을 만들어준다.
void CreateSprites(OneMotion* motion, zzBitmap* sheet, int AniIndex, int NumofAni)
{
	motion->sheet = sheet;

	// 스프라이트 정보를 동적으로 할당한다.
	motion->sprites = (OneSprite*)malloc(sizeof(OneSprite) * motion->spriteNum);

	for (int i = 0; i < motion->spriteNum; i++)
	{
		// 폭은 전체 시트를 스프라이트의 갯수로 나눈 균일한 값
		motion->sprites[i].width = (sheet->Width / motion->spriteNum);
		motion->sprites[i].height = (sheet->Height / NumofAni);

		// 시작 위치는 인덱스별로 폭과 높이를 감안한 위치
		motion->sprites[i].oriX = motion->sprites[i].width * i;
		motion->sprites[i].oriY = (sheet->Height / NumofAni) * AniIndex;
	}
}

/// 애니메이션 함수
void Animate_PickPos(int dstX, int dstY, zzSummonee* character,
	int AnimationIndex, int level)
{
	int nowFrame = character->motions[AnimationIndex].nowFrame / character->motions[AnimationIndex].delayFrame;

	character->motions[AnimationIndex].nowFrame++;

	if (character->motions[AnimationIndex].nowFrame == character->motions[AnimationIndex].spriteNum * character->motions[AnimationIndex].delayFrame)
	{
		character->motions[AnimationIndex].nowFrame = 0;
	}

	int dstW = (int)(((float)character->sheet->Width / 7.f) * character->mySize);

	DrawBitmap_PickPos(dstX, dstY, 
		character->myWidth, character->myHeight,
		character->sheet,
		character->motions[AnimationIndex].sprites[nowFrame].oriX,
		character->motions[AnimationIndex].sprites[nowFrame].oriY,
		character->motions[AnimationIndex].sprites[nowFrame].width,
		character->motions[AnimationIndex].sprites[nowFrame].height,
		level);



}

/// 새로운 그리기 함수
void DrawBitmap_PickPos(int dstX, int dstY, int dstW, int dstH, zzBitmap* sheet, int oriX, int oriY, int width, int height, int level)
{

	BlenFunc.BlendOp = AC_SRC_OVER;
	BlenFunc.BlendFlags = 0;
	BlenFunc.AlphaFormat = AC_SRC_ALPHA;
	BlenFunc.SourceConstantAlpha = level;

	GdiAlphaBlend(Backbuffer.hMemDC, dstX, dstY, dstW, dstH,
		sheet->hMemDC, oriX, oriY, width, height, BlenFunc);
}





// 원하는 좌표에 서식화된 텍스트 출력. MSDN예제를 보고 새로 만듦.
BOOL TextOutp(HDC hdc, int x, int y, const char* pch, ...)
{
	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);		// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscprintf(pch, ap) + 1;
	buffer = (char*)malloc(len * sizeof(char));

	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);

	TextOut(hdc, x, y, buffer, (int)strlen(buffer));

	free(buffer);

	return TRUE;
}

// 원하는 좌표에 서식화된 텍스트 출력. MSDN예제를 보고 새로 만듬.
// 무조건 백버퍼에 글씨를 쏜다. 디버그용.
BOOL _TT(int x, int y, const char* pch, ...)
{
	// 브러시를 투명으로.
	SelectObject(Backbuffer.hMemDC, GetStockObject(NULL_BRUSH));	// 브러시
	SetTextColor(Backbuffer.hMemDC, RGB(0x00, 0xFF, 0x00));			// 텍스트의 색
	SetBkMode(Backbuffer.hMemDC, TRANSPARENT);						// 텍스트의 배경을 투명으로

	HFONT font = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "굴림");
	HFONT oldfont = (HFONT)SelectObject(Backbuffer.hMemDC, font);

	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);		// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	// len을 산출하는 방법?
	// pch는 분명 문자열 상수의 포인터일텐데, strlen으로 크기가 안나오나?
	// _vscprintf doesn't count  .. 라고 MSDN에 나와있음. ;;

	len = _vscprintf(pch, ap) + 1;
	buffer = malloc(len * sizeof(char));

	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);

	TextOut(Backbuffer.hMemDC, x, y, buffer, (int)strlen(buffer));

	free(buffer);


	SelectObject(Backbuffer.hMemDC, oldfont);
	DeleteObject(font);

	return TRUE;
}

void DrawAllToScreen()
{
	BitBlt(g_hDCMain, 0, 0, SCREENWIDTH, SCREENHEIGHT, Backbuffer.hMemDC, 0, 0, SRCCOPY);
}

// 파일에서 비트맵을 로드한다.
void LoadBitmap_FromFile(zzBitmap* bitmap, char* filePath)
{
	BITMAP bit;

	// 메인DC와 호환되는 메모리DC생성, 파일에서 비트맵을 로드
	bitmap->hMemDC = CreateCompatibleDC(g_hDCMain);
	bitmap->hBitmap = MakeDDBFromDIB(g_hDCMain, filePath);

	SelectObject(bitmap->hMemDC, bitmap->hBitmap);

	// 부가 정보를 만들어준다.
	GetObject(bitmap->hBitmap, sizeof(BITMAP), &bit);
	bitmap->Width = bit.bmWidth;
	bitmap->Height = bit.bmHeight;
	bitmap->KeyColor = COLORKEY;

	DeleteObject(bitmap->hBitmap);
}

void LoadBitmap_FromFile2(zzBitmap* bitmap, char* filePath)
{
	BITMAP bit;

	// 메인DC와 호환되는 메모리DC생성, 파일에서 비트맵을 로드
	bitmap->hMemDC = CreateCompatibleDC(g_hDCMain);
	///bitmap->hBitmap = MakeDDBFromDIB(g_hDCMain, filePath);
	bitmap->hBitmap = LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	/// ※
	///SetDIBitsToDevice()

	SelectObject(bitmap->hMemDC, bitmap->hBitmap);

	// 부가 정보를 만들어준다.
	GetObject(bitmap->hBitmap, sizeof(BITMAP), &bit);
	bitmap->Width = bit.bmWidth;
	bitmap->Height = bit.bmHeight;
	bitmap->KeyColor = COLORKEY;

	DeleteObject(bitmap->hBitmap);
}

/// //////////////////////////////////////////////////////////////////////
/// prototype	: HBITMAP MakeDDBFromDIB(HDC hdc, char *FileLocation) ;
/// 기	   능	: DIB -> DDB 전환
/// 리	   턴	: 변환된 비트맵 핸들
/// hdc			: DC 핸들
/// FileLocation : 변환을 원하는 파일 위치
/// //////////////////////////////////////////////////////////////////////
HBITMAP MakeDDBFromDIB(HDC hdc, char* FileLocation)
{
	HANDLE  hFile;
	DWORD   FileSize, dwRead;
	HBITMAP hBit;
	BITMAPFILEHEADER* fh;
	BITMAPINFO* ih;
	BITMAPINFOHEADER* iheader;
	LPBYTE			 lpMemBlock;
	char Path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, Path);
	strcat_s(Path, MAX_PATH, FileLocation);

	/// 파일을 연다
	hFile = CreateFile(Path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return NULL;
	}

	FileSize = GetFileSize(hFile, NULL);

	lpMemBlock = (LPBYTE)malloc(FileSize);
	fh = (BITMAPFILEHEADER*)lpMemBlock;
	ReadFile(hFile, lpMemBlock, FileSize, &dwRead, NULL);
	CloseHandle(hFile);

	ih = (BITMAPINFO*)(lpMemBlock + sizeof(BITMAPFILEHEADER));
	iheader = (BITMAPINFOHEADER*)(lpMemBlock + sizeof(BITMAPFILEHEADER));

	/// DDB로 변환한다.
	hBit = CreateDIBitmap(hdc,		// hdc
		iheader,					// BITMAPINFOHEADER
		CBM_INIT,					// 0 또는 CBM_INIT ( 초기화 )
		lpMemBlock + fh->bfOffBits,	// 래스터 어드래스
		ih,							// BITMAPINFO
		DIB_RGB_COLORS);

	free(lpMemBlock);

	return hBit;
}