#pragma once
#include "D2DMacros.h"
#include "ImageFactory.h"
#include "D2DImage.h"
#include "../Util/Singleton.h"	
#include "../Util/Vector2.h"
#include "../Figure/CircleVector.h"
#include "../Figure/LineVector.h"
#include "../Figure/RectVector.h"
#include "../Figure/TriangleVector.h"

class D2DGraphics : public Singleton<D2DGraphics>
{
public:
	D2DGraphics();
	virtual ~D2DGraphics();

public:
	/// D2D1 Setting
	HWND GetHWnd();
	HDC GetHDC();
	HRESULT Initialize();
	HRESULT Initialize(HWND hwnd, HDC hdc);
	void Finalize();
	void OnResize(UINT width, UINT height);
	void SettingSystemDPI();
	void SettingSystemDPI(FLOAT x, FLOAT y, FLOAT* DpiX, FLOAT* DpiY);

	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceTarget();
	HRESULT CreateDeviceTarget(int height, int width);
	void DiscardDeviceResources();

	/// Drawing Default
	void BeginDraw();
	void EndDraw();
	ID2D1HwndRenderTarget* GetRenderTarget();

	void ScreenClear();
	void DrawAllScreen();
	void SetRenderSize(RECT rc);
	
	/// Setting Brush
	void CreateBrush(D2D1::ColorF color);
	void ReleaseBrush();

	/// Writing Text
	void CreateTextFormat();
	void CreateTextFormatDebug();
	void CreateTextFormatDebug(const wchar_t* fontname, const float size);
	void CreateTextFormat(const wchar_t* fontname, const float size);
	void ReleaseTextFormat();
	void WriteText(D2D1::ColorF color, D2D1_RECT_F layout, const wchar_t* pch, ...);
	void WriteTextDebug(D2D1::ColorF color, D2D1_RECT_F layout, const wchar_t* pch, ...);

	void WriteText(D2D1::ColorF color, D2D1_RECT_F layout, const wchar_t* fontname,
		const float size, const wchar_t* pch, ...);

	void WriteTextDebug(D2D1::ColorF color, D2D1_RECT_F layout, const wchar_t* fontname, const float size, const wchar_t* pch, ...);

	/// Drawing Figuare
	void DrawLine(Vector2 src, Vector2 dst, D2D1::ColorF color);
	void DrawLine(LineVector line, D2D1::ColorF color);

	void DrawRectangle(RECT rt, bool fill);
	void DrawRectangle(RECT rt, D2D1::ColorF color, bool fill);
	void DrawRectangle(Vector2 lt, Vector2 rt, Vector2 lb, Vector2 rb, D2D1::ColorF color);
	void DrawRectangle(D2D1_RECT_F d2rc, D2D1::ColorF color, bool fill);
	void DrawRectangle(float left, float right, float top, float bottom, D2D1::ColorF color, bool fill);
	void DrawRectangle(RectVector rect, D2D1::ColorF color, bool fill);
	void DrawRectanglePos(float x, float y, D2D1_RECT_F d2rc, D2D1::ColorF color, bool fill);

	void DrawEllipse(D2D1_POINT_2F point, FLOAT radiusX, FLOAT radiusY, D2D1::ColorF color, bool fill);
	void DrawCircle(CircleVector circle, D2D1::ColorF color, bool fill);

	/// Drawing Bitmap
	void LoadImageFromFile(const wchar_t* filename, ID2D1Bitmap** pBitmap);
	void LoadImageFromFile(const wchar_t* filename, float alpha, ID2D1Bitmap** pBitmap);
	void DrawBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F dstrt, float opacity,
		D2D1_BITMAP_INTERPOLATION_MODE mode, D2D1_RECT_F srcrt);

	/// Drawing Image
	void CreateImage(const wchar_t* filename, ImageSheet* sheet);
	void CreateImage(const wchar_t* filename, float alpha, ImageSheet* sheet);

	// 해당 모션의 중점 데이터를 정정합니다, 코드상의 비율 값 정정.
	void SettingMotionRatio(MotionSheet* sheet, int motion_index, int sprite_index, Vector2 ratio, float dealyratio);

	void CreateAnimation(MotionSheet* sheet, int motion_count, int sprite_count);
	void CreateAnimation(MotionSheet* sheet, int motion_count, int sprite_count, float playcount);
	void CreateAnimation(MotionSheet* sheet, wchar_t* filename);
	void DrawImage(ImageSheet* image, float startx, float starty);
	void DrawImage(ImageSheet* image, float startx, float starty, float opacity, D2D1_BITMAP_INTERPOLATION_MODE mode);
	void DrawImage(ImageSheet* image, float startx, float starty, Vector2 center);
	void DrawImageDebug(ImageSheet* image, float startx, float starty);

	Vector2 GetMotionCenter(MotionSheet* sheet);
	SpriteInfo CurrentSheetInfo(MotionSheet* sheet);

	void AnimateImage(MotionSheet* sheet, float startx, float starty, int motionnumber);
	void AnimateImage(MotionSheet* sheet, float startx, float starty,float opacity, D2D1_BITMAP_INTERPOLATION_MODE mode, int motionnumber);
	void AnimateImageDebug(MotionSheet* sheet, float startx, float starty, float opacity, D2D1_BITMAP_INTERPOLATION_MODE mode, int motionnumber);

	/// Transform
	void SetTransform(const D2D1_MATRIX_3X2_F& matrix);

private:
	HWND hWnd;
	HDC hDC;

	/// Direct2D Default Factory
	ID2D1Factory* pDirect2dFactory;
	IDWriteFactory* pIDWriteFactory;
	
	/// 이미지 시트와 모션을 동시에 관리하기 위한 만든 자체 팩토리
	/// 이미지를 넣으면 디코딩 하고 다시 비트맵으로 변환 후, 
	/// 이미지 시트와 모션 시트로 변환시켜주는 팩토리
	ImageFactory* pImageFactory;

	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1BitmapRenderTarget* pBitmapRenderTarget;

	ID2D1SolidColorBrush* pBrush;
	IDWriteTextFormat* pTextFormat;
	ID2D1Bitmap* pD2DBitmap;

	FLOAT DpiX, DpiY;
	D2D1_SIZE_U Size;
};