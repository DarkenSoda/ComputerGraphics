#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include "Tool.h"

class LineDrawer : public Tool {
public:
    static void directLine(HDC, Vector2D*, Vector2D*, COLORREF);
    static void simpleDDA(HDC, Vector2D*, Vector2D*, COLORREF);
    static void bresenhamLine(HDC, Vector2D*, Vector2D*, COLORREF);
    virtual void handleMsg(HWND, UINT, WPARAM, LPARAM) override;
};

#endif