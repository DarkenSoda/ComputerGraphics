#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <cwchar>
#include "src/Utilities/Vectors/Vector2D.h"
#include "src/ShapeTools/LineDrawer.h"
#include "src/ShapeTools/RectDrawer.h"
#include "src/ShapeTools/CircleDrawer.h"
#include "src/ShapeTools/EllipseDrawer.h"
#include "src/ShapeTools/Tool.h"
#include "src/ShapeTools/PolygonTool.h"

Tool* tool = new PolygonTool;
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

    delete tool;
    return 0;
}

#include<iostream>
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lp) {
    // startegy pattern
    // tool type should change using a custom button that we will create.
    tool->handleMsg(hwnd, uMsg, wParam, lp);

    switch (uMsg) {
    case WM_KEYDOWN:
        if (wParam == VK_F1) {
            // clear window
        }
        // erase window with ESCAPE Key
        // get window rect
        else if (wParam == VK_ESCAPE) {
            RECT rect;
            GetClientRect(hwnd, &rect);
            FillRect(GetDC(hwnd), &rect, (HBRUSH)(COLOR_WINDOW + 1));
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lp);
}
