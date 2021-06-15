// RimEngine.cpp : 정적 라이브러리를 위한 함수를 정의합니다.
#include "RimEngine.h"

RimEngine* RimEngine::m_Instance = nullptr;

RimEngine::RimEngine() :
	m_hWnd(NULL), m_D2d1Factory(nullptr), m_RenderTarget(nullptr),
	m_BlackBrush(nullptr), m_WicImageFactory(nullptr), m_DWriteFactory(nullptr),
	m_DTextFormat(nullptr), m_NowBrush(nullptr), m_TempBrush(nullptr)
{

}

RimEngine::~RimEngine()
{


}

RimEngine* RimEngine::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new RimEngine();
	}
	return m_Instance;
}

HRESULT RimEngine::InitializeEngine(HWND hWnd)
{
	m_hWnd = hWnd;

	HRESULT hr = S_OK;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_D2d1Factory);

	static const WCHAR msc_fontName[] = L"Verdana";
	static const FLOAT msc_fontSize = 50;

	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
			CLSCTX_INPROC_SERVER, IID_IWICImagingFactory,
			reinterpret_cast<void**>(&m_WicImageFactory));
	}
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_DWriteFactory),
			reinterpret_cast<IUnknown**>(&m_DWriteFactory));
	}
	if (SUCCEEDED(hr))
	{
		hr = m_DWriteFactory->CreateTextFormat(
			msc_fontName,
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			msc_fontSize,
			L"",
			&m_DTextFormat);
	}
	if (SUCCEEDED(hr))
	{
		m_DTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		m_DTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	if (SUCCEEDED(hr))
	{
		hr = CreateDeviceResources();
	}


	return hr;
}

HRESULT RimEngine::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	if (m_RenderTarget == nullptr)
	{
		RECT rc = {};
		GetClientRect(m_hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		hr = m_D2d1Factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hWnd, size),
			&m_RenderTarget
		);


		if (SUCCEEDED(hr))
		{
			hr = m_RenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				&m_BlackBrush
			);
		}
		if (SUCCEEDED(hr))
		{
			hr = m_RenderTarget->CreateSolidColorBrush(
				D2D1::ColorF(D2D1::ColorF::Black),
				&m_NowBrush
			);
		}


	}


	return hr;
}

HRESULT RimEngine::LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (SUCCEEDED(hr))
	{

		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}

	if (SUCCEEDED(hr))
	{
		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		// If a new width or height was specified, create an
		// IWICBitmapScaler and use it to resize the image.
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else // Don't scale the image.
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}
	if (SUCCEEDED(hr))
	{
		// Create a Direct2D bitmap from the WIC bitmap.
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pStream);
	SafeRelease(&pConverter);
	SafeRelease(&pScaler);

	return hr;
}

void RimEngine::DiscardDeviceResources()
{
	SafeRelease(&m_RenderTarget);
	SafeRelease(&m_BlackBrush);
}

HRESULT RimEngine::BeginDraw()
{
	HRESULT hr = CreateDeviceResources();

	if (SUCCEEDED(hr) && !(m_RenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		///------------------------------------------
		m_RenderTarget->BeginDraw();
		m_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	}
	return hr;
}

HRESULT RimEngine::EndDraw()
{
	HRESULT hr = S_OK;
	hr = m_RenderTarget->EndDraw();
	///------------------------------------------
	return hr;
}

void RimEngine::SetBrush(float r, float g, float b, float a)
{
	SafeRelease(&m_NowBrush);

	m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &m_NowBrush);

}

void RimEngine::SetBrush(unsigned long dwRGBColor)
{
	SafeRelease(&m_NowBrush);

	m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(dwRGBColor)), &m_NowBrush);
}

void RimEngine::DrawLine(float x1, float y1, float x2, float y2)
{
	m_RenderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), m_NowBrush);
}

void RimEngine::DrawLine(float x1, float y1, float x2, float y2, COLORREF crBrush)
{
	m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(crBrush)), &m_TempBrush);

	if (m_TempBrush != NULL)
	{
		m_RenderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), m_TempBrush);
	}

	SafeRelease(&m_TempBrush);
}

void RimEngine::DrawLine(Vector2 v1, Vector2 v2)
{
	m_RenderTarget->DrawLine(D2D1::Point2F(v1.X, v1.Y), D2D1::Point2F(v2.X, v2.Y), m_NowBrush);
}

void RimEngine::DrawLine(Vector2 v1, Vector2 v2, COLORREF crBrush)
{
	m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(crBrush)), &m_TempBrush);

	if (m_TempBrush != NULL)
	{
		m_RenderTarget->DrawLine(D2D1::Point2F(v1.X, v1.Y), D2D1::Point2F(v2.X, v2.Y), m_TempBrush);
	}

	SafeRelease(&m_TempBrush);
}

void RimEngine::DrawRectangle(float x, float y, float x1, float y1, COLORREF crBrush)
{
	m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(crBrush)), &m_TempBrush);

	if (m_TempBrush != NULL)
	{
		m_RenderTarget->DrawRectangle(D2D1::RectF(x, y, x1, y1), m_TempBrush);
	}

	SafeRelease(&m_TempBrush);
}

void RimEngine::DrawRectangle(float x, float y, float x1, float y1)
{
	m_RenderTarget->DrawRectangle(D2D1::RectF(x, y, x1, y1), m_NowBrush);
}

void RimEngine::DrawRectangle(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4)
{
	DrawLine(v1, v2);
	DrawLine(v2, v3);
	DrawLine(v3, v4);
	DrawLine(v4, v1);
}

void RimEngine::DrawRectangle(Vector2 v1, Vector2 v2, Vector2 v3, Vector2 v4, COLORREF crBrush)
{
	m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(crBrush)), &m_TempBrush);

	if (m_TempBrush != NULL)
	{
		m_RenderTarget->DrawLine(D2D1::Point2F(v1.X, v1.Y), D2D1::Point2F(v2.X, v2.Y), m_TempBrush);
		m_RenderTarget->DrawLine(D2D1::Point2F(v2.X, v2.Y), D2D1::Point2F(v3.X, v3.Y), m_TempBrush);
		m_RenderTarget->DrawLine(D2D1::Point2F(v3.X, v3.Y), D2D1::Point2F(v4.X, v4.Y), m_TempBrush);
		m_RenderTarget->DrawLine(D2D1::Point2F(v4.X, v4.Y), D2D1::Point2F(v1.X, v1.Y), m_TempBrush);
	}

	SafeRelease(&m_TempBrush);
}

void RimEngine::DrawEllipse(float x, float y, float r)
{
	m_RenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), r, r), m_NowBrush);
}

void RimEngine::DrawEllipse(float left, float top, float right, float bottom)
{
	D2D1_ELLIPSE _region;
	_region.point.x = (left + right) / 2.0f;
	_region.point.y = (top + bottom) / 2.0f;
	_region.radiusX = (right - left) / 2.0f;
	_region.radiusY = (bottom - top) / 2.0f;

	m_RenderTarget->DrawEllipse(_region, m_NowBrush);
}

void RimEngine::DrawEllipse(float x, float y, float r, COLORREF crBrush)
{
	m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(crBrush)), &m_TempBrush);

	if (m_TempBrush != NULL)
	{
		m_RenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), r, r), m_TempBrush);
	}

	SafeRelease(&m_TempBrush);
}

void RimEngine::DrawEllipse(float left, float top, float right, float bottom, COLORREF crBrush)
{
	m_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(crBrush)), &m_TempBrush);

	if (m_TempBrush != NULL)
	{
		D2D1_ELLIPSE _region;
		_region.point.x = (left + right) / 2.0f;
		_region.point.y = (top + bottom) / 2.0f;
		_region.radiusX = (right - left) / 2.0f;
		_region.radiusY = (bottom - top) / 2.0f;

		m_RenderTarget->DrawEllipse(_region, m_NowBrush);
	}

	SafeRelease(&m_TempBrush);
}

void RimEngine::DrawText(int x, int y, const char* pch, ...)
{
	// 포맷 스트링 관련 버퍼, 가변인자 처리
	char* buffer;
	int len;

	va_list ap;			// 현재 읽고 있는 번지를 기억
	va_start(ap, pch);	// ap 포인터 변수가 첫번째 가변인수를 가리키도록 초기화

	len = _vscprintf(pch, ap) + 1;
	buffer = new char[len];

	vsprintf_s(buffer, len, pch, ap);
	va_end(ap);


	//int nLen = lstrlenA(pch);
	int nLen = MultiByteToWideChar(CP_ACP, 0, buffer, lstrlen(buffer), NULL, NULL);

	BSTR unicodestr = SysAllocStringLen(NULL, nLen);

	// 당연히 멀티바이트와 유니코드의 문자열 길이 차이가 있다. 2바이트 문자 등
	::MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), unicodestr, nLen);

	if (unicodestr != NULL)
	{
		// 폰트별 차지하는 영역 계산 필요
		m_RenderTarget->DrawText(unicodestr, wcslen(unicodestr), m_DTextFormat,
			//D2D1::RectF(x, y, m_RenderTargetSize.width, m_RenderTargetSize.height),
			D2D1::RectF((float)x, (float)y, (float)(x + 500), (float)(y + 40)),
			m_NowBrush);
	}

	//... when done, free the BSTR
	::SysFreeString(unicodestr);

	// 포맷관련 버퍼 삭제
	delete[] buffer;
}

void RimEngine::Finalize()
{
	SafeRelease(&m_D2d1Factory);
	SafeRelease(&m_RenderTarget);
	SafeRelease(&m_BlackBrush);
	SafeRelease(&m_WicImageFactory);
	SafeRelease(&m_DWriteFactory);
	SafeRelease(&m_DTextFormat);
	SafeRelease(&m_NowBrush);
	SafeRelease(&m_TempBrush);

	CoUninitialize();
}

/*
HRESULT RimEngine::Render()
{
	HRESULT hr = CreateDeviceResources();

	if (SUCCEEDED(hr) && !(m_RenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		///------------------------------------------
		m_RenderTarget->BeginDraw();
		m_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		m_RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));


		hr = m_RenderTarget->EndDraw();
		///------------------------------------------
	}

	return hr;
}
*/