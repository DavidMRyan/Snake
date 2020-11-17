#include <iostream>
#include <vector>
#include "graphics.hpp";

RECT clientRect{ 0, 0, 800, 600 };

Graphics::Graphics()
{
	/*m_pD2DFactory = NULL;
	m_pRenderTarget = NULL;*/
}

Graphics::~Graphics()
{
	if (m_pD2DFactory) m_pD2DFactory->Release();
	if (m_pRenderTarget) m_pRenderTarget->Release();
}

bool Graphics::Init(HWND hWnd)
{
	ComPtr<IDXGIFactory1> pDXGIFactory1;
	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), &pDXGIFactory1)))
		return false;

	ComPtr<IDXGIAdapter> pDXGIAdapter;
	ComPtr<IDXGIOutput> pDXGIOutput;
	DXGI_RATIONAL rational = { 0 };

	pDXGIFactory1->EnumAdapters(0, &pDXGIAdapter);
	pDXGIAdapter->EnumOutputs(0, &pDXGIOutput);

	UINT outputLength = 0;
	pDXGIOutput->GetDisplayModeList(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&outputLength,
		NULL
	);
	std::vector<DXGI_MODE_DESC> pDescs(outputLength);
	pDXGIOutput->GetDisplayModeList(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_ENUM_MODES_INTERLACED,
		&outputLength,
		pDescs.data()
	);

	if (true) // Check for V-Sync Option Later
	{
		for (const DXGI_MODE_DESC &desc : pDescs)
		{
			if (desc.Width == clientRect.right && desc.Height == clientRect.bottom)
			{
				rational.Numerator = desc.RefreshRate.Numerator;
				rational.Denominator = desc.RefreshRate.Denominator;
				break;
			}
		}
	}



	RECT rect;
	GetClientRect(hWnd, &rect);

	/*hResult = m_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			D2D1::SizeU(rect.right, rect.bottom)),
		&m_pRenderTarget
	);*/

	//m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &m_pWhiteBrush);

	return true;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	m_pRenderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawLine(
	D2D1_POINT_2F p1,
	D2D1_POINT_2F p2,
	float r,
	float g,
	float b,
	float a)
{
	/*float dashes[] = { 1.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f };

	HRESULT hResult = m_pD2DFactory->CreateStrokeStyle(
		D2D1::StrokeStyleProperties(
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_FLAT,
			D2D1_CAP_STYLE_FLAT,
			D2D1_LINE_JOIN_MITER,
			1.0f,
			D2D1_DASH_STYLE_SOLID,
			0.0f),
		dashes,
		ARRAYSIZE(dashes),
		&m_pStrokeStyle
	);*/

	m_pRenderTarget->DrawLine(
		p1,
		p2,
		m_pWhiteBrush,
		1.0f,
		NULL // Maybe use m_pStrokeStyle here? Stroke Width doesn't work but I can probably fix it
	);
}

void Graphics::DrawRectangle(
	D2D1_RECT_F rect,
	float r,
	float g,
	float b,
	float a)
{
	// TODO: Implement custom brush here
	m_pRenderTarget->DrawRectangle(
		rect,
		m_pWhiteBrush,
		1.0f,
		NULL
	);
}