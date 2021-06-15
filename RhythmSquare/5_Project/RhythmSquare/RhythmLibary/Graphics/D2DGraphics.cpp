#include "pchLib.h"
#include "D2DGraphics.h"

D2DGraphics::D2DGraphics()
	:hWnd(NULL), hDC(NULL), pDirect2dFactory(NULL), pIDWriteFactory(NULL),
	pRenderTarget(NULL), pBrush(NULL), DpiX(0.0f), DpiY(0.0f), Size({ 0, 0 })
{
	pImageFactory = new ImageFactory();
}

D2DGraphics::~D2DGraphics()
{
}

HWND D2DGraphics::GetHWnd()
{
	return hWnd;
}

HDC D2DGraphics::GetHDC()
{
	return hDC;
}

HRESULT D2DGraphics::Initialize()
{
	HRESULT result = CreateDeviceIndependentResources();
	return result;
}

HRESULT D2DGraphics::Initialize(HWND hwnd, HDC hdc)
{
	HRESULT result = CreateDeviceIndependentResources();
	this->hWnd = hwnd;
	this->hDC = hdc;

	return result;
}

void D2DGraphics::Finalize()
{
	SafeRelease(&pDirect2dFactory);
	SafeRelease(&pIDWriteFactory);
	delete pImageFactory;

	SafeRelease(&pRenderTarget);
	SafeRelease(&pBitmapRenderTarget);
	SafeRelease(&pD2DBitmap);

	SafeRelease(&pBrush);
	SafeRelease(&pTextFormat);
	CoUninitialize();
}

void D2DGraphics::OnResize(UINT width, UINT height)
{
	if (pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		//pRenderTarget->Resize(D2D1::SizeU(width, height));
		pRenderTarget->Resize(D2D1::SizeU(2560, 1440));
	}
}

HRESULT D2DGraphics::CreateDeviceIndependentResources()
{
	HRESULT result;

	result = CoInitialize(NULL);
	result = pImageFactory->Initialize();
	result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pDirect2dFactory);
	result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(pIDWriteFactory), reinterpret_cast<IUnknown * *>(&pIDWriteFactory));

	return result;
}

void D2DGraphics::SettingSystemDPI()
{
	//pDirect2dFactory->GetDesktopDpi(&DpiX, &DpiY);

	//DpiX = static_cast<UINT>(ceil(640.f * DpiX / 96.f));
	//DpiY = static_cast<UINT>(ceil(480.f * DpiY / 96.f));
}

void D2DGraphics::SettingSystemDPI(FLOAT x, FLOAT y, FLOAT* DpiX, FLOAT* DpiY)
{
	//pDirect2dFactory->GetDesktopDpi(&this->DpiX, &this->DpiY);

	//*DpiX = static_cast<UINT>(ceil(x * this->DpiX / 96.f));
	//*DpiY = static_cast<UINT>(ceil(y * this->DpiY / 96.f));
}

void D2DGraphics::SetRenderSize(RECT rc)
{
	Size = D2D1::SizeU((rc.right - rc.left), rc.bottom - rc.top);
}

void D2DGraphics::DrawLine(Vector2 src, Vector2 dst, D2D1::ColorF color)
{
	CreateBrush(color);
	if (pBrush == NULL)
		return;

	pRenderTarget->DrawLine(D2D1::Point2F(src.x, src.y),
		D2D1::Point2F(dst.x, dst.y), pBrush, 1, 0);
	ReleaseBrush();
}

void D2DGraphics::DrawLine(LineVector line, D2D1::ColorF color)
{
	CreateBrush(color);
	if (pBrush == NULL)
		return;

	pRenderTarget->DrawLine(D2D1::Point2F(line.Src.x, line.Src.y),
		D2D1::Point2F(line.Dst.x, line.Dst.y), pBrush, 1, 0);
	ReleaseBrush();
}

void D2DGraphics::DrawRectangle(RECT rt, bool fill)
{
	D2D1_RECT_F d2rc = { (FLOAT)rt.left, (FLOAT)rt.top, (FLOAT)rt.right, (FLOAT)rt.bottom };
	if (pBrush == NULL)
		return;
	if (fill)
	{
		pRenderTarget->FillRectangle(&d2rc, pBrush);
	}
	else
	{
		pRenderTarget->DrawRectangle(&d2rc, pBrush);
	}
}

void D2DGraphics::DrawRectangle(RECT rt, D2D1::ColorF color, bool fill)
{
	D2D1_RECT_F d2rc = { (FLOAT)rt.left, (FLOAT)rt.top, (FLOAT)rt.right, (FLOAT)rt.bottom };
	CreateBrush(color);
	if (pBrush == NULL)
		return;
	if (fill)
	{
		pRenderTarget->FillRectangle(&d2rc, pBrush);
	}
	else
	{
		pRenderTarget->DrawRectangle(&d2rc, pBrush);
	}
	ReleaseBrush();
}

void D2DGraphics::DrawRectangle(Vector2 lt, Vector2 rt, Vector2 lb, Vector2 rb, D2D1::ColorF color)
{
	CreateBrush(color);
	if (pBrush == NULL)
		return;
	pRenderTarget->DrawLine(D2D1::Point2F(lt.x, lt.y),
		D2D1::Point2F(rt.x, rt.y), pBrush, 1, 0);
	pRenderTarget->DrawLine(D2D1::Point2F(rt.x, rt.y),
		D2D1::Point2F(rb.x, rb.y), pBrush, 1, 0);
	pRenderTarget->DrawLine(D2D1::Point2F(rb.x, rb.y),
		D2D1::Point2F(lb.x, lb.y), pBrush, 1, 0);
	pRenderTarget->DrawLine(D2D1::Point2F(lb.x, lb.y),
		D2D1::Point2F(lt.x, lt.y), pBrush, 1, 0);
	ReleaseBrush();
}

void D2DGraphics::DrawRectangle(D2D1_RECT_F d2rc, D2D1::ColorF color, bool fill)
{
	CreateBrush(color);
	if (pBrush == NULL)
		return;
	if (fill)
	{
		pRenderTarget->FillRectangle(&d2rc, pBrush);
	}
	else
	{
		pRenderTarget->DrawRectangle(&d2rc, pBrush);
	}
	ReleaseBrush();
}

void D2DGraphics::DrawRectangle(float left, float top, float right, float bottom, D2D1::ColorF color, bool fill)
{
	CreateBrush(color);
	D2D1_RECT_F d2rc = { left, top, right, bottom };
	if (pBrush == NULL)
		return;

	if (fill)
	{
		pRenderTarget->FillRectangle(&d2rc, pBrush);
	}
	else
	{
		pRenderTarget->DrawRectangle(&d2rc, pBrush);
	}
	ReleaseBrush();
}

void D2DGraphics::DrawRectangle(RectVector rect, D2D1::ColorF color, bool fill)
{
	CreateBrush(color);
	if (pBrush == NULL)
		return;
	pRenderTarget->DrawLine(D2D1::Point2F(rect.LeftTop.x, rect.LeftTop.y),
		D2D1::Point2F(rect.RightTop.x, rect.RightTop.y), pBrush, 1, 0);
	pRenderTarget->DrawLine(D2D1::Point2F(rect.RightTop.x, rect.RightTop.y),
		D2D1::Point2F(rect.RightBottom.x, rect.RightBottom.y), pBrush, 1, 0);
	pRenderTarget->DrawLine(D2D1::Point2F(rect.RightBottom.x, rect.RightBottom.y),
		D2D1::Point2F(rect.LeftBottom.x, rect.LeftBottom.y), pBrush, 1, 0);
	pRenderTarget->DrawLine(D2D1::Point2F(rect.LeftBottom.x, rect.LeftBottom.y),
		D2D1::Point2F(rect.LeftTop.x, rect.LeftTop.y), pBrush, 1, 0);
	ReleaseBrush();
}

void D2DGraphics::DrawRectanglePos(float x, float y, D2D1_RECT_F d2rc, D2D1::ColorF color, bool fill)
{
	CreateBrush(color);
	if (pBrush == NULL)
		return;
	d2rc.top += y;
	d2rc.bottom += y;
	d2rc.left += x;
	d2rc.right += x;
	if (fill)
	{
		pRenderTarget->FillRectangle(&d2rc, pBrush);
	}
	else
	{
		pRenderTarget->DrawRectangle(&d2rc, pBrush);
	}
	ReleaseBrush();
}

void D2DGraphics::DrawEllipse(D2D1_POINT_2F point, FLOAT radiusX, FLOAT radiusY, D2D1::ColorF color, bool fill)
{
	CreateBrush(color);
	D2D1_ELLIPSE ellipse = { point, radiusX, radiusY };
	if (pBrush == NULL)
		return;
	if (fill)
	{
		pRenderTarget->FillEllipse(&ellipse, pBrush);
	}
	else
	{
		pRenderTarget->DrawEllipse(&ellipse, pBrush);
	}
	ReleaseBrush();
}

void D2DGraphics::DrawCircle(CircleVector circle, D2D1::ColorF color, bool fill)
{
	D2D1_POINT_2F point = { circle.Center.x, circle.Center.y };
	D2D1_ELLIPSE ellipse = { point, circle.Radius, circle.Radius };

	CreateBrush(color);
	if (pBrush == NULL)
		return;
	if (fill)
	{
		pRenderTarget->FillEllipse(&ellipse, pBrush);
	}
	else
	{
		pRenderTarget->DrawEllipse(&ellipse, pBrush);
	}
	ReleaseBrush();
}

void D2DGraphics::WriteText(D2D1::ColorF color, D2D1_RECT_F layout, const wchar_t* pch, ...)
{
	wchar_t* buffer;
	int len;

	CreateBrush(color);
	CreateTextFormat();
	if (pBrush == NULL)
		return;
	va_list ap;			// 현재 읽고 있는 번지를 기억

	va_start(ap, pch);
	len = _vscwprintf(pch, ap) + 1;
	buffer = (wchar_t*)malloc(len * sizeof(wchar_t));
	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	pRenderTarget->DrawText(buffer, len, pTextFormat, layout, pBrush);

	ReleaseBrush();
	ReleaseTextFormat();
	free(buffer);
}

void D2DGraphics::WriteTextDebug(D2D1::ColorF color, D2D1_RECT_F layout, const wchar_t* pch, ...)
{
	wchar_t* buffer;
	int len;

	CreateBrush(color);
	CreateTextFormatDebug();
	if (pBrush == NULL)
		return;
	va_list ap;			// 현재 읽고 있는 번지를 기억

	va_start(ap, pch);
	len = _vscwprintf(pch, ap) + 1;
	buffer = (wchar_t*)malloc(len * sizeof(wchar_t));
	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	pRenderTarget->DrawText(buffer, len, pTextFormat, layout, pBrush);

	ReleaseBrush();
	ReleaseTextFormat();
	free(buffer);
}

void D2DGraphics::WriteText(D2D1::ColorF color, D2D1_RECT_F layout, const wchar_t* fontname, const float size, const wchar_t* pch, ...)
{
	wchar_t* buffer;
	int len;

	CreateBrush(color);
	CreateTextFormat(fontname, size);
	if (pBrush == NULL)
		return;
	va_list ap;			// 현재 읽고 있는 번지를 기억

	va_start(ap, pch);
	len = _vscwprintf(pch, ap) + 1;
	buffer = (wchar_t*)malloc(len * sizeof(wchar_t));
	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	pRenderTarget->DrawText(buffer, len, pTextFormat, layout, pBrush);

	ReleaseBrush();
	ReleaseTextFormat();
	free(buffer);
}

void D2DGraphics::WriteTextDebug(D2D1::ColorF color, D2D1_RECT_F layout, const wchar_t* fontname, const float size, const wchar_t* pch, ...)
{
	wchar_t* buffer;
	int len;

	CreateBrush(color);
	CreateTextFormatDebug(fontname, size);
	if (pBrush == NULL)
		return;
	va_list ap;			// 현재 읽고 있는 번지를 기억

	va_start(ap, pch);
	len = _vscwprintf(pch, ap) + 1;
	buffer = (wchar_t*)malloc(len * sizeof(wchar_t));
	vswprintf_s(buffer, len, pch, ap);
	va_end(ap);

	pRenderTarget->DrawText(buffer, len, pTextFormat, layout, pBrush);

	ReleaseBrush();
	ReleaseTextFormat();
	free(buffer);
}

void D2DGraphics::LoadImageFromFile(const wchar_t* filename, ID2D1Bitmap** pBitmap)
{
	HRESULT hr;
	pImageFactory->LoadImageFromFile(filename);
	IWICFormatConverter* pConverter = *(pImageFactory->GetConverterPoint());

	hr = pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, pBitmap);
	pImageFactory->ReleaseDecodingDevice();
}

void D2DGraphics::LoadImageFromFile(const wchar_t* filename, float alpha, ID2D1Bitmap** pBitmap)
{
	IWICFormatConverter* pConverter = *(pImageFactory->GetConverterPoint());

	pImageFactory->LoadImageFromFile(filename, alpha);
	pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, pBitmap);
	pImageFactory->ReleaseDecodingDevice();
}

void D2DGraphics::DrawBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F dstrt, float opacity, D2D1_BITMAP_INTERPOLATION_MODE mode, D2D1_RECT_F srcrt)
{
	pRenderTarget->DrawBitmap(bitmap, dstrt, opacity, mode, srcrt);
}

void D2DGraphics::CreateImage(const wchar_t* filename, ImageSheet* sheet)
{
	if (sheet == nullptr)
		return;

	LoadImageFromFile(filename, &sheet->pBitmap);
	D2D1_SIZE_F size = sheet->pBitmap->GetSize();

	sheet->Height = size.height;
	sheet->Width = size.width;
	sheet->Status = SheetStatus::SHEET_NONE;
	sheet->Level = SheetType::SHEET_IMAGE;
}

void D2DGraphics::CreateImage(const wchar_t* filename, float alpha, ImageSheet* sheet)
{
	D2D1_SIZE_F size = sheet->pBitmap->GetSize();
	LoadImageFromFile(filename, alpha, &sheet->pBitmap);

	sheet->Height = size.height;
	sheet->Width = size.width;
	sheet->Status = SheetStatus::SHEET_NONE;
	sheet->Level = SheetType::SHEET_IMAGE;
}

void D2DGraphics::SettingMotionRatio(MotionSheet* sheet, int motion_index, int sprite_index, Vector2 ratio, float dealyratio)
{
	sheet->Motions[motion_index][sprite_index].CenterX *= ratio.x;
	sheet->Motions[motion_index][sprite_index].CenterY *= ratio.y;
	sheet->Motions[motion_index][sprite_index].DelayFream *= dealyratio;
}

void D2DGraphics::CreateAnimation(MotionSheet* sheet, int motion_count, int sprite_count)
{
	pImageFactory->SettingAnimationData(sheet, motion_count, sprite_count);
}

void D2DGraphics::CreateAnimation(MotionSheet* sheet, int motion_count, int sprite_count, float playcount)
{
	float DelayTime = playcount / sprite_count;
	pImageFactory->SettingAnimationData(sheet, motion_count, sprite_count, DelayTime);
}

void D2DGraphics::CreateAnimation(MotionSheet* sheet, wchar_t* filename)
{
	// motion tool data
}

void D2DGraphics::DrawImage(ImageSheet* image, float startx, float starty)
{
	D2D1_SIZE_F size = image->pBitmap->GetSize();

	pRenderTarget->DrawBitmap(image->pBitmap,
		D2D1::RectF(startx, starty, startx + size.width, starty + size.height),
		1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(startx, starty, startx + size.width, starty + size.height));
}

void D2DGraphics::DrawImage(ImageSheet* image, float startx, float starty, float opacity, D2D1_BITMAP_INTERPOLATION_MODE mode)
{
	D2D1_SIZE_F size = image->pBitmap->GetSize();

	pRenderTarget->DrawBitmap(image->pBitmap,
		D2D1::RectF(startx, starty, startx + size.width, starty + size.height),
		opacity, mode,
		D2D1::RectF(startx, starty, startx + size.width, starty + size.height));
}

void D2DGraphics::DrawImageDebug(ImageSheet* image, float startx, float starty)
{
	D2D1_SIZE_F size = image->pBitmap->GetSize();

	pRenderTarget->DrawBitmap(image->pBitmap,
		D2D1::RectF(startx, starty, startx + (size.width / 2), starty + (size.height / 2)),
		1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(startx, starty, startx + size.width, starty + size.height));
}


Vector2 D2DGraphics::GetMotionCenter(MotionSheet* sheet)
{
	return Vector2(sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].CenterX, sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].CenterY);
}

SpriteInfo D2DGraphics::CurrentSheetInfo(MotionSheet* sheet)
{
	return sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount];
}



void D2DGraphics::AnimateImage(MotionSheet* sheet, float startx, float starty, int motionnumber)
{
	pRenderTarget->DrawBitmap(sheet->pBitmap,
		D2D1::RectF(
			startx,
			starty,
			startx + (sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.right - sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.left),
			starty + (sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.bottom - sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.top)),
		1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.left,
			sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.top,
			sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.right,
			sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.bottom));
	pImageFactory->Animate(sheet);
}

void D2DGraphics::AnimateImage(MotionSheet* sheet, float startx, float starty, float opacity, D2D1_BITMAP_INTERPOLATION_MODE mode, int motionnumber)
{
	pRenderTarget->DrawBitmap(sheet->pBitmap,
		D2D1::RectF(
			startx,
			starty,
			startx + (sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.right - sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.left),
			starty + (sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.bottom - sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.top)),
		opacity, mode,
		D2D1::RectF(sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.left,
			sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.top,
			sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.right,
			sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.bottom));
	pImageFactory->Animate(sheet);
}

void D2DGraphics::AnimateImageDebug(MotionSheet* sheet, float startx, float starty, float opacity, D2D1_BITMAP_INTERPOLATION_MODE mode, int motionnumber)
{
	float right = startx + sheet->Motions[sheet->CurrentMotionCount][0].Layout.right / 2;
	float bottom = starty + sheet->Motions[sheet->CurrentMotionCount][0].Layout.bottom / 2;
	pRenderTarget->DrawBitmap(sheet->pBitmap,
		D2D1::RectF(
			startx,
			starty,
			right,
			bottom),
		opacity, mode,
		D2D1::RectF(sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.left,
			sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.top,
			sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.right,
			sheet->Motions[sheet->CurrentMotionCount][sheet->CurrentSpriteCount].Layout.bottom));
	pImageFactory->Animate(sheet);
}

void D2DGraphics::SetTransform(const D2D1_MATRIX_3X2_F& matrix)
{
	pRenderTarget->SetTransform(matrix);
}

HRESULT D2DGraphics::CreateDeviceTarget()
{
	HRESULT result = S_OK;
	if (pRenderTarget == nullptr)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);
		/*
		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);
		*/
		D2D1_SIZE_U size = { 2560, 1440 };
		result = pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&pRenderTarget);
	}
	/*result = pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, Size),
		&pRenderTarget);*/
	return result;
}

HRESULT D2DGraphics::CreateDeviceTarget(int height, int width)
{
	HRESULT result = S_OK;
	if (pRenderTarget == nullptr)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(width, height);

		//D2D1_SIZE_U size = { 2560, 1440 };
		result = pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&pRenderTarget);
	}
	/*result = pDirect2dFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, Size),
		&pRenderTarget);*/
	return result;
}


void D2DGraphics::DiscardDeviceResources()
{
	SafeRelease(&pRenderTarget);
}

void D2DGraphics::BeginDraw()
{
	HRESULT hr = CreateDeviceTarget();

	if (SUCCEEDED(hr) && !(pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		pRenderTarget->BeginDraw();
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		ScreenClear();
	}
}

void D2DGraphics::EndDraw()
{
	HRESULT hr = pRenderTarget->EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
		DiscardDeviceResources();
	}
}

ID2D1HwndRenderTarget* D2DGraphics::GetRenderTarget()
{
	return pRenderTarget;
}

void D2DGraphics::ScreenClear()
{
	pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
}

void D2DGraphics::DrawAllScreen()
{
	EndDraw();
}

void D2DGraphics::CreateBrush(D2D1::ColorF color)
{
	pRenderTarget->CreateSolidColorBrush(color, &pBrush);
}

void D2DGraphics::ReleaseBrush()
{
	SafeRelease(&pBrush);
}

void D2DGraphics::CreateTextFormat()
{
	static const WCHAR msc_fontName[] = L"Verdana";
	static const FLOAT msc_fontSize = 36;


	pIDWriteFactory->CreateTextFormat(msc_fontName,
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		msc_fontSize,
		L"", //locale
		&pTextFormat);

	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	//pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	//pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
}

void D2DGraphics::CreateTextFormatDebug()
{
	static const WCHAR msc_fontName[] = L"Verdana";
	static const FLOAT msc_fontSize = 36;


	pIDWriteFactory->CreateTextFormat(msc_fontName,
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		msc_fontSize,
		L"", //locale
		&pTextFormat);

	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
}

void D2DGraphics::CreateTextFormatDebug(const wchar_t* fontname, const float size)
{

	pIDWriteFactory->CreateTextFormat(fontname,
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		size,
		L"", //locale
		&pTextFormat);

	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
}

void D2DGraphics::CreateTextFormat(const wchar_t* fontname, const float size)
{
	pIDWriteFactory->CreateTextFormat(fontname,
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		size,
		L"", //locale
		&pTextFormat);

	pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
}

void D2DGraphics::ReleaseTextFormat()
{
	SafeRelease(&pTextFormat);
}

