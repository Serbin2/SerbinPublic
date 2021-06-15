#include "pchLib.h"
#include <string>
#include "ImageFactory.h"
#include <tchar.h>

ImageFactory::ImageFactory()
	:pIWICFactory(NULL), pDecoder(NULL), pFrame(NULL), pStream(NULL), pConverter(NULL), pScaler(NULL)
{

}

ImageFactory::~ImageFactory()
{
	SafeRelease(&pIWICFactory);
	SafeRelease(&pDecoder);
	SafeRelease(&pFrame);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);
}

HRESULT ImageFactory::Initialize()
{
	return CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL, CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		reinterpret_cast<void**>(&pIWICFactory));
}

HRESULT ImageFactory::CreateDecoder(const wchar_t* filename)
{
	HRESULT hr;
	PCWSTR path = filename;
	hr = pIWICFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder);
	return hr;
}

HRESULT ImageFactory::CreateFreamDecode()
{
	return pDecoder->GetFrame(0, &pFrame);
}

HRESULT ImageFactory::CreateFormatConverter()
{
	HRESULT hr = pIWICFactory->CreateFormatConverter(&pConverter);
	hr = pConverter->Initialize(
		pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeMedianCut
	);
	return hr;
}

HRESULT ImageFactory::CreateFormatConverter(float alpha)
{
	pIWICFactory->CreateFormatConverter(&pConverter);
	return pConverter->Initialize(
		pFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		alpha,
		WICBitmapPaletteTypeMedianCut
	);
}

void ImageFactory::LoadImageFromFile(const wchar_t* filename)
{
	HRESULT hr;
	hr = CreateDecoder(filename);
	if (SUCCEEDED(hr))
	{
		hr = CreateFreamDecode();
		hr = CreateFormatConverter();
	}
}

void ImageFactory::LoadImageFromFile(const wchar_t* filename, float alpha)
{
	HRESULT hr;
	hr = CreateDecoder(filename);
	if (SUCCEEDED(hr))
	{
		CreateFreamDecode();
		CreateFormatConverter(alpha);
	}
}

void ImageFactory::ReleaseDecodingDevice()
{
	SafeRelease(&pDecoder);
	SafeRelease(&pFrame);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);
}

IWICFormatConverter** ImageFactory::GetConverterPoint()
{
	return &pConverter;
}

void ImageFactory::SettingAnimationData(MotionSheet* sheet, int motionCount, int spriteCount)
{
	sheet->MaxMotionCount = motionCount;
	sheet->MaxSpriteCount = spriteCount;
	sheet->Status = SheetStatus::SHEET_START;
	sheet->Level = SheetType::SHEET_MOTIONS;

	float LayoutHeight = sheet->Height / motionCount;
	float LayoutWidth = sheet->Width / spriteCount;

	sheet->Motions = new SpriteInfo * [sheet->MaxMotionCount];
	for (int y = 0; y < sheet->MaxMotionCount; y++)
	{
		sheet->Motions[y] = new SpriteInfo[sheet->MaxSpriteCount];
		ZeroMemory(sheet->Motions[y], sizeof(sheet->Motions[y]));
	}

	for (int y = 0; y < sheet->MaxMotionCount; y++)
	{
		for (int x = 0; x < sheet->MaxSpriteCount; x++)
		{
			SettingSprite(sheet, y, x, 1.0f, 0, 0, D2D1::RectF(LayoutWidth * x, LayoutHeight * y,
				LayoutWidth * (x + 1), LayoutHeight * (y + 1)));
		}
	}
}

void ImageFactory::SettingAnimationData(MotionSheet* sheet, int motionCount, int spriteCount, float delayfream)
{
	sheet->MaxMotionCount = motionCount;
	sheet->MaxSpriteCount = spriteCount;
	sheet->Status = SheetStatus::SHEET_START;
	sheet->Level = SheetType::SHEET_MOTIONS;

	int LayoutHeight = sheet->Height / motionCount;
	int LayoutWidth = sheet->Width / spriteCount;

	int CenterX = LayoutWidth / 2;
	int CenterY = LayoutHeight / 2;

	sheet->Motions = new SpriteInfo * [sheet->MaxMotionCount];
	for (int y = 0; y < sheet->MaxMotionCount; y++)
	{
		sheet->Motions[y] = new SpriteInfo[sheet->MaxSpriteCount];
		ZeroMemory(sheet->Motions[y], sizeof(sheet->Motions[y]));
	}

	for (int y = 0; y < sheet->MaxMotionCount; y++)
	{
		for (int x = 0; x < sheet->MaxSpriteCount; x++)
		{
			SettingSprite(sheet, y, x, CenterX, CenterY, delayfream,
				D2D1::RectF(
					LayoutWidth * x,
					LayoutHeight * y,
					LayoutWidth * (x + 1),
					LayoutHeight * (y + 1)));
		}
	}
}

void ImageFactory::SettingSprite(MotionSheet* sheet, int motionindex, int spriteindex, float centerx, float centery, float delayfream, D2D1_RECT_F layout)
{
	sheet->Motions[motionindex][spriteindex].DelayFream = delayfream;
	sheet->Motions[motionindex][spriteindex].Layout = layout;
	sheet->Motions[motionindex][spriteindex].CenterX = centerx;
	sheet->Motions[motionindex][spriteindex].CenterY = centery;
}

void ImageFactory::NextSprite(MotionSheet* sheet)
{
	sheet->CurrentSpriteCount++;

	if (sheet->CurrentSpriteCount >= sheet->MaxSpriteCount)
		sheet->CurrentSpriteCount = 0;
}

void ImageFactory::Animate(MotionSheet* sheet)
{
	switch (sheet->Status)
	{
	case SheetStatus::SHEET_NONE:
		sheet->Status = SheetStatus::SHEET_START;
		break;
	case SheetStatus::SHEET_START:
		sheet->Alarm.Set(sheet->Motions[0][0].DelayFream);
		sheet->Status = SheetStatus::SHEET_ANIMATE;
		break;
	case SheetStatus::SHEET_ANIMATE:
		if (sheet->Alarm.Check())
		{
			sheet->Alarm.Set(sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].DelayFream);
			NextSprite(sheet);
		}
		break;
	case SheetStatus::SHEET_PAUSE:
		break;
	case SheetStatus::SHEET_RESTART:
		break;
	default:
		break;
	}
}


