#pragma once
#include "D2DMacros.h"
#include "D2DImage.h"

class ImageFactory
{
public:
	ImageFactory();
	~ImageFactory();

public:
	HRESULT Initialize();
	HRESULT CreateDecoder(const wchar_t* filename);
	HRESULT CreateFreamDecode();
	HRESULT CreateFormatConverter();
	HRESULT CreateFormatConverter(float alpha);

	void LoadImageFromFile(const wchar_t* filename);
	void LoadImageFromFile(const wchar_t* filename, float alpha);

	void ReleaseDecodingDevice();
	IWICFormatConverter** GetConverterPoint();

	void SettingAnimationData(MotionSheet* sheet, int motionCount, int spriteCount);
	void SettingAnimationData(MotionSheet* sheet, int motionCount, int spriteCount, float delayfream);

	void SettingSprite(MotionSheet* sheet, int motionindex, int spriteindex, float delayfream, float centerx, float centery, D2D1_RECT_F layout);
	void NextSprite(MotionSheet* sheet);
	void Animate(MotionSheet* sheet);

private:
	IWICImagingFactory* pIWICFactory;
	IWICBitmapDecoder* pDecoder;
	IWICBitmapFrameDecode* pFrame;
	IWICStream* pStream;
	IWICFormatConverter* pConverter;
	IWICBitmapScaler* pScaler;
};

