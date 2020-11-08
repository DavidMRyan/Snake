#include "graphics.hpp";

Graphics::Graphics()
{
	m_pD2DFactory = NULL;
	m_pRenderTarget = NULL;
}

Graphics::~Graphics()
{
	if (m_pD2DFactory) m_pD2DFactory->Release();
	if (m_pRenderTarget) m_pRenderTarget->Release();
}

bool Graphics::Init(HWND hWnd)
{
	HRESULT hResult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	if (hResult != S_OK)
		return false;

	RECT rect;
	GetClientRect(hWnd, &rect);

	hResult = m_pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hWnd,
			D2D1::SizeU(rect.right, rect.bottom)),
		&m_pRenderTarget
	);

	return hResult == S_OK;
}

void Graphics::ClearScreen(float r, float g, float b)
{
	m_pRenderTarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphics::DrawLine(D2D1_POINT_2F p1,
						D2D1_POINT_2F p2,
						float r,
						float g,
						float b,
						float a)
{
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b, a), &m_pWhiteBrush);

	float dashes[] = { 1.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f };

	/*HRESULT hResult = m_pD2DFactory->CreateStrokeStyle(
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
		NULL
	);
}