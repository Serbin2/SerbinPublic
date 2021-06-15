#pragma once
#include "D2DMacros.h"
#include "../Util/TimeUtil.h"

struct SpriteInfo
{
	D2D1_RECT_F Layout;
	float CenterX;
	float CenterY;
	float DelayFream;
};

enum class SheetType : unsigned int
{
	SHEET_IMAGE_NONE,
	SHEET_IMAGE = 128,
	SHEET_MOTIONS
};

enum class SheetStatus : unsigned int
{
	SHEET_NONE,
	SHEET_START,
	SHEET_ANIMATE,
	SHEET_PAUSE,
	SHEET_RESTART
};

class ImageSheet
{
public:
	ImageSheet();
	~ImageSheet();
	
	SheetType Level;
	SheetStatus Status;
	ID2D1Bitmap* pBitmap;

	float Height;
	float Width;
	unsigned int ImageNumber;
};

class MotionSheet : public ImageSheet
{
public:
	MotionSheet();
	~MotionSheet();

	SpriteInfo** Motions;
	Flag_Fream Alarm;

	int MaxMotionCount;
	int CurrentMotionCount;
	int MaxSpriteCount;
	int CurrentSpriteCount;
};


