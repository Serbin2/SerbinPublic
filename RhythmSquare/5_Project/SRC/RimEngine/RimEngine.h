#pragma once
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <stdio.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")	
#pragma comment(lib, "windowscodecs.lib")

#include <d2d1.h>
#include <d2d1_1.h>

#include <dwrite.h>
#include <wincodec.h>

#include "Vector2.h"
#include "CircleCollision.h"
#include "BoxCollision.h"


#include "REMacro.h"



class RimEngine
{
protected:
	static RimEngine* m_Instance;

private:
	RimEngine();
	~RimEngine();

public:
	static RimEngine* GetInstance();

	HRESULT InitializeEngine(HWND hWnd);
	HRESULT CreateDeviceResources();
	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);
	void DiscardDeviceResources();

	HRESULT BeginDraw();
	HRESULT EndDraw();


	void SetBrush(float r, float g, float b, float a);
	void SetBrush(unsigned long dwRGBColor);

	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawLine(float x1, float y1, float x2, float y2, COLORREF crBrush);
	void DrawLine(Vector2 v1, Vector2 v2);
	void DrawLine(Vector2 v1, Vector2 v2, COLORREF crBrush);

	void DrawRectangle(float x, float y, float x1, float y1, COLORREF crBrush);
	void DrawRectangle(float x, float y, float x1, float y1);
	void DrawRectangle(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4);
	void DrawRectangle(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, COLORREF crBrush);
	void DrawEllipse(float x, float y, float r, COLORREF crBrush);
	void DrawEllipse(float x, float y, float r);
	void DrawEllipse(float left, float top, float right, float bottom, COLORREF crBrush);
	void DrawEllipse(float left, float top, float right, float bottom);

	void DrawText(int x, int y, const char* pch, ...);



	void Finalize();
	//HRESULT Render();

private:

	HWND m_hWnd;


	ID2D1Factory* m_D2d1Factory;
	ID2D1HwndRenderTarget* m_RenderTarget;
	IWICImagingFactory* m_WicImageFactory;
	IDWriteFactory* m_DWriteFactory;
	IDWriteTextFormat* m_DTextFormat;

	ID2D1SolidColorBrush* m_BlackBrush;
	ID2D1SolidColorBrush* m_NowBrush;
	ID2D1SolidColorBrush* m_TempBrush;

};

