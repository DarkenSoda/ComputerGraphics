#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <cwchar>
#include "Headers/Vector2D.h"
#include "Headers/LineDrawer.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow) {
    // Register the window class.
    LPCWCHAR CLASS_NAME = L"Computer Graphics";

    WNDCLASS wc = { };
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        CLASS_NAME,
        WS_OVERLAPPEDWINDOW,

        // position and size
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

Vector2D* startPoint;
Vector2D* endPoint;
bool canDraw = false;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lp) {
    PAINTSTRUCT ps;
    switch (uMsg) {
    case WM_PAINT:
        BeginPaint(hwnd, &ps);
        if (canDraw) {
            LineDrawer::simpleDDA(ps.hdc, startPoint, endPoint, RGB(255, 0, 0));
            canDraw = false;

            delete startPoint;
            delete endPoint;
        }
        EndPaint(hwnd, &ps);
        break;
    case WM_LBUTTONDOWN:
        startPoint = new Vector2D(LOWORD(lp), HIWORD(lp));
        break;
    case WM_LBUTTONUP:
        endPoint = new Vector2D(LOWORD(lp), HIWORD(lp));
        canDraw = true;
        InvalidateRect(hwnd, NULL, 0);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lp);
}
