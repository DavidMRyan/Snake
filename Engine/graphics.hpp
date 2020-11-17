#pragma once

#include <Windows.h>
#include <d2d1_1.h>
#include <d3d11.h>
#include <dxgi.h>
#include "shared.hpp"

class Graphics
{
	ComPtr<ID2D1Device>				m_pD2DDevice;
	ComPtr<ID3D11Device>			m_pD3DDevice;
	ComPtr<ID2D1DeviceContext>		m_pD2DContext;
	ComPtr<IDXGISwapChain>			m_pSwapChain;
	DXGI_SWAP_CHAIN_DESC			m_pSwapChainDescription;
	ComPtr<ID3D11Texture2D>			m_pBackBuffer;
	ComPtr<ID2D1Factory1>			m_pD2DFactory1;
	ComPtr<IDXGIFactory>			m_pDXGIFactory;
	ComPtr<ID2D1Factory>			m_pD2DFactory;
	ComPtr<ID2D1HwndRenderTarget>	m_pRenderTarget;
	ComPtr<ID2D1Bitmap1>			m_pTarget;

	//ID2D1StrokeStyle*				m_pStrokeStyle;
	ID2D1SolidColorBrush*			m_pWhiteBrush;
	//ID2D1SolidColorBrush*			m_pRedBrush;

public:
	Graphics();
	~Graphics();

	bool Init(HWND hWnd);
	void BeginDraw() { m_pRenderTarget->BeginDraw(); }
	void EndDraw() { m_pRenderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawLine(
		D2D1_POINT_2F p1,
		D2D1_POINT_2F p2,
		float r,
		float g,
		float b,
		float a
	);
	void DrawRectangle(
		D2D1_RECT_F rect,
		float r,
		float g,
		float b,
		float a
	);
};