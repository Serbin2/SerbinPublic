#include "pchLib.h"
#include "D2DImage.h"

ImageSheet::ImageSheet()
	:Level(SheetType::SHEET_IMAGE_NONE), Status(SheetStatus::SHEET_NONE), pBitmap(NULL), ImageNumber(0)
{
}

ImageSheet::~ImageSheet()
{
	SafeRelease(&pBitmap);
}

MotionSheet::MotionSheet()
	:ImageSheet(), MaxMotionCount(0), CurrentMotionCount(0), MaxSpriteCount(0), CurrentSpriteCount(0)
{
	Level = SheetType::SHEET_MOTIONS;
}

MotionSheet::~MotionSheet()
{
	SafeRelease(&pBitmap);
	for (int y = 0; y < MaxMotionCount; y++)
	{
		delete Motions[y];
	}
	delete[] Motions;
}

