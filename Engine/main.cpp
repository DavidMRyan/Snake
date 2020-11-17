#define DW_EX_STYLE (WS_EX_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX)
#define DW_STYLE (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX)

#include <Windows.h>
#include "graphics.hpp";
#include <cstdio>

Graphics* pGraphics = new Graphics();
RECT clientRect{ 0, 0, 800, 600 };

LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	AllocConsole();
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			break;

		case WM_PAINT:
			/*pGraphics->BeginDraw();
			pGraphics->ClearScreen(0.0f, 0.0f, 0.0f);*/

			// ------------ Grid ------------
			// Grid is just for testing and debugging!
			/*for (int x = 0; x < clientRect.right; x += 20)
			{
				pGraphics->DrawLine(
					D2D1::Point2F(x, clientRect.top),
					D2D1::Point2F(x, clientRect.bottom),
					1.0f,
					1.0f,
					1.0f,
					1.0f
				);
			}

			for (int y = 0; y < clientRect.bottom; y += 20)
			{
				pGraphics->DrawLine(
					D2D1::Point2F(clientRect.left, y),
					D2D1::Point2F(clientRect.right, y),
					1.0f,
					1.0f,
					1.0f,
					1.0f
				);
			}*/
			// ------------ End Grid ------------
			
			//pGraphics->EndDraw();
			break;
	}

	DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(WNDCLASSEX));
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WindowProc;
	wClass.lpszClassName = L"Window";
	wClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wClass);

	AdjustWindowRectEx(&clientRect, DW_EX_STYLE, false, DW_STYLE);
	HWND hWnd = CreateWindowEx(
		DW_EX_STYLE,
		L"Window",
		L"Snake",
		DW_STYLE,
		100,
		100,
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top,
		NULL,
		NULL,
		hInstance,
		0
	);

	if (!hWnd) return -1;
	if (!pGraphics->Init(hWnd))
	{
		delete pGraphics;
		return -1;
	}

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);

	delete pGraphics;
	return 0;
}

