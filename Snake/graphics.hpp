#pragma once

#include <Windows.h>
#include <d2d1_1.h>

class Graphics
{
	ID2D1Factory* m_pD2DFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	ID2D1StrokeStyle* m_pStrokeStyle;
	ID2D1SolidColorBrush* m_pWhiteBrush;
	ID2D1SolidColorBrush* m_pRedBrush;

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
};