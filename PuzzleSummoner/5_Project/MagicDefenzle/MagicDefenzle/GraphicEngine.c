#include "stdafx.h"
#include "GraphicEngine.h"

/// ��� �������� ������ ������

HINSTANCE g_hInst;	// �ν��Ͻ� �ڵ�
HWND g_hWnd;		// �׸��⸦ �� ���� (1����� ����)
HDC g_hDCMain;		// ����DC. ȭ�鿡 �׸��� �뵵
zzBitmap Backbuffer;// �����
BLENDFUNCTION BlenFunc;

/// �ʱ�ȭ ����

// �׷��Ƚ� ���̺귯���� �ʿ��� ���� �������� ���´�.
// �� ��, ������ 1����� �����Ѵ�. �׸��� ȭ�鵵 1����� ������
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

/// �׸���� ���� �Ϻ��� �Լ���
/// (BitBlt�ø�� �� �� ������ ��)

// �ϳ��� ��������Ʈ�� �׸���. �� ����� Solid(SRCCOPY)
void DrawBitmap(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY)
{
	BitBlt(Backbuffer.hMemDC, posX, posY, bitmap->Width, bitmap->Height,
		bitmap->hMemDC, srcX, srcY, SRCCOPY);
}

// �ϳ��� ��������Ʈ�� �׸���. (���ù���)
void DrawBitmap_Simple(int posX, int posY, zzBitmap* bitmap)
{
	DrawBitmap(posX, posY, bitmap, 0, 0);
}

// ȭ�鿡 ��������Ʈ �ϳ��� �׸���.
void DrawSprite(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY)
{
	GdiTransparentBlt(Backbuffer.hMemDC, posX, posY, bitmap->Width, bitmap->Height,
		bitmap->hMemDC, srcX, srcY, bitmap->Width, bitmap->Height, bitmap->KeyColor);
}

// ȭ�鿡 Ÿ�� ��ĭ�� �׸���.
void DrawTile(int posX, int posY, zzBitmap* bitmap, int NumofTile, int picktile, int speciality, int numofspec)
{
	int TileWidth = (bitmap->Width / NumofTile);
	int TileHeight = bitmap->Height / numofspec;

	GdiTransparentBlt(Backbuffer.hMemDC, posX, posY, TileWidth, TileHeight,
		bitmap->hMemDC, TileWidth * picktile, TileHeight * speciality, TileWidth, TileHeight, bitmap->KeyColor);
}

// ȭ�鿡 ��������Ʈ �ϳ��� �׸���. (���ù���)
void DrawSprite_Simple(int posX, int posY, zzBitmap* bitmap)
{
	DrawSprite(posX, posY, bitmap, 0, 0);
}

// ȭ�鿡 ���ĺ��带 �׸���.
void zzDrawAlphaBlendSprite(int posX, int posY, zzBitmap* bitmap, int srcX, int srcY, int level)
{

	// Blend Function
	BlenFunc.BlendOp = AC_SRC_OVER;
	BlenFunc.BlendFlags = 0;
	BlenFunc.AlphaFormat = AC_SRC_ALPHA;
	BlenFunc.SourceConstantAlpha = level;	// ��ü ���İ��� �����ϸ�, pre-multiplied�� �ݿ��ȴ�.

	/// ���ĺ���
	/// ����! Per-Pixel Alpha Blending�� �Ϸ���,
	/// 1. ����ä���� �־�� ��. (32��Ʈ)
	/// 2. Pre-Multiplied Alpha Image�̾�� ��.
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
	BlenFunc.SourceConstantAlpha = level;	// ��ü ���İ��� �����ϸ�, pre-multiplied�� �ݿ��ȴ�.

	/// ���ĺ���
	/// ����! Per-Pixel Alpha Blending�� �Ϸ���,
	/// 1. ����ä���� �־�� ��. (32��Ʈ)
	/// 2. Pre-Multiplied Alpha Image�̾�� ��.
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


/// �Ʒ��� ĳ���� ���� �޸𸮸� Ǯ���ش�
void FreeCharacterMalloc(zzSummonee* character)
{
	for (int i = 0; i < character->NumofAni; i++)
	{
		free(character->motions[i].sprites);
	}
	free(character->motions);
}

/// ĳ���� ����
void CreateCharacterRes(zzSummonee* character, zzBitmap* sheet, int motions, int frames, int delay)
{
	// ���� ��Ʈ
	character->sheet = sheet;

	// �ִ��� ���� �����Ҵ��Ѵ�.
	character->NumofAni = motions;
	character->motions = (OneMotion*)malloc(sizeof(OneMotion) * character->NumofAni);

	// ���� �Ҵ� �� ��� ���� �ʱ�ȭ �Ѵ�.
	for (int i = 0; i < character->NumofAni; i++)
	{
		// �� ����� �ʱ�ȭ
		character->motions[i].sheet = sheet;
		character->motions[i].spriteNum = frames;
		character->motions[i].nowFrame = 0;
		character->motions[i].delayFrame = delay;

		// ��ǿ� �ټ��� ��������Ʈ���� �����Ҵ� �� �ʱ�ȭ�� �� �ش�.
		CreateSprites(&character->motions[i], sheet, i, motions);
	}
}

/// ����� �������ش�. ��������Ʈ ���� ������ش�.
void CreateSprites(OneMotion* motion, zzBitmap* sheet, int AniIndex, int NumofAni)
{
	motion->sheet = sheet;

	// ��������Ʈ ������ �������� �Ҵ��Ѵ�.
	motion->sprites = (OneSprite*)malloc(sizeof(OneSprite) * motion->spriteNum);

	for (int i = 0; i < motion->spriteNum; i++)
	{
		// ���� ��ü ��Ʈ�� ��������Ʈ�� ������ ���� ������ ��
		motion->sprites[i].width = (sheet->Width / motion->spriteNum);
		motion->sprites[i].height = (sheet->Height / NumofAni);

		// ���� ��ġ�� �ε������� ���� ���̸� ������ ��ġ
		motion->sprites[i].oriX = motion->sprites[i].width * i;
		motion->sprites[i].oriY = (sheet->Height / NumofAni) * AniIndex;
	}
}

/// �ִϸ��̼� �Լ�
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

/// ���ο� �׸��� �Լ�
void DrawBitmap_PickPos(int dstX, int dstY, int dstW, int dstH, zzBitmap* sheet, int oriX, int oriY, int width, int height, int level)
{

	BlenFunc.BlendOp = AC_SRC_OVER;
	BlenFunc.BlendFlags = 0;
	BlenFunc.AlphaFormat = AC_SRC_ALPHA;
	BlenFunc.SourceConstantAlpha = level;

	GdiAlphaBlend(Backbuffer.hMemDC, dstX, dstY, dstW, dstH,
		sheet->hMemDC, oriX, oriY, width, height, BlenFunc);
}





// ���ϴ� ��ǥ�� ����ȭ�� �ؽ�Ʈ ���. MSDN������ ���� ���� ����.
BOOL TextOutp(HDC hdc, int x, int y, const char* pch, ...)
{
	char* buffer;
	int len;

	va_list ap;			// ���� �а� �ִ� ������ ���
	va_start(ap, pch);		// ap ������ ������ ù��° �����μ��� ����Ű���� �ʱ�ȭ

	len = _vscprintf(pch, ap) + 1;
	buffer = (char*)malloc(len * sizeof(char));

	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);

	TextOut(hdc, x, y, buffer, (int)strlen(buffer));

	free(buffer);

	return TRUE;
}

// ���ϴ� ��ǥ�� ����ȭ�� �ؽ�Ʈ ���. MSDN������ ���� ���� ����.
// ������ ����ۿ� �۾��� ���. ����׿�.
BOOL _TT(int x, int y, const char* pch, ...)
{
	// �귯�ø� ��������.
	SelectObject(Backbuffer.hMemDC, GetStockObject(NULL_BRUSH));	// �귯��
	SetTextColor(Backbuffer.hMemDC, RGB(0x00, 0xFF, 0x00));			// �ؽ�Ʈ�� ��
	SetBkMode(Backbuffer.hMemDC, TRANSPARENT);						// �ؽ�Ʈ�� ����� ��������

	HFONT font = CreateFont(12, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, "����");
	HFONT oldfont = (HFONT)SelectObject(Backbuffer.hMemDC, font);

	char* buffer;
	int len;

	va_list ap;			// ���� �а� �ִ� ������ ���
	va_start(ap, pch);		// ap ������ ������ ù��° �����μ��� ����Ű���� �ʱ�ȭ

	// len�� �����ϴ� ���?
	// pch�� �и� ���ڿ� ����� ���������ٵ�, strlen���� ũ�Ⱑ �ȳ�����?
	// _vscprintf doesn't count  .. ��� MSDN�� ��������. ;;

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

// ���Ͽ��� ��Ʈ���� �ε��Ѵ�.
void LoadBitmap_FromFile(zzBitmap* bitmap, char* filePath)
{
	BITMAP bit;

	// ����DC�� ȣȯ�Ǵ� �޸�DC����, ���Ͽ��� ��Ʈ���� �ε�
	bitmap->hMemDC = CreateCompatibleDC(g_hDCMain);
	bitmap->hBitmap = MakeDDBFromDIB(g_hDCMain, filePath);

	SelectObject(bitmap->hMemDC, bitmap->hBitmap);

	// �ΰ� ������ ������ش�.
	GetObject(bitmap->hBitmap, sizeof(BITMAP), &bit);
	bitmap->Width = bit.bmWidth;
	bitmap->Height = bit.bmHeight;
	bitmap->KeyColor = COLORKEY;

	DeleteObject(bitmap->hBitmap);
}

void LoadBitmap_FromFile2(zzBitmap* bitmap, char* filePath)
{
	BITMAP bit;

	// ����DC�� ȣȯ�Ǵ� �޸�DC����, ���Ͽ��� ��Ʈ���� �ε�
	bitmap->hMemDC = CreateCompatibleDC(g_hDCMain);
	///bitmap->hBitmap = MakeDDBFromDIB(g_hDCMain, filePath);
	bitmap->hBitmap = LoadImage(NULL, filePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	/// ��
	///SetDIBitsToDevice()

	SelectObject(bitmap->hMemDC, bitmap->hBitmap);

	// �ΰ� ������ ������ش�.
	GetObject(bitmap->hBitmap, sizeof(BITMAP), &bit);
	bitmap->Width = bit.bmWidth;
	bitmap->Height = bit.bmHeight;
	bitmap->KeyColor = COLORKEY;

	DeleteObject(bitmap->hBitmap);
}

/// //////////////////////////////////////////////////////////////////////
/// prototype	: HBITMAP MakeDDBFromDIB(HDC hdc, char *FileLocation) ;
/// ��	   ��	: DIB -> DDB ��ȯ
/// ��	   ��	: ��ȯ�� ��Ʈ�� �ڵ�
/// hdc			: DC �ڵ�
/// FileLocation : ��ȯ�� ���ϴ� ���� ��ġ
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

	/// ������ ����
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

	/// DDB�� ��ȯ�Ѵ�.
	hBit = CreateDIBitmap(hdc,		// hdc
		iheader,					// BITMAPINFOHEADER
		CBM_INIT,					// 0 �Ǵ� CBM_INIT ( �ʱ�ȭ )
		lpMemBlock + fh->bfOffBits,	// ������ ��巡��
		ih,							// BITMAPINFO
		DIB_RGB_COLORS);

	free(lpMemBlock);

	return hBit;
}