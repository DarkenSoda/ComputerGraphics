#ifndef ELLIPSEDRAWER_H
#define ELLIPSEDRAWER_H

#include "Tool.h"

class EllipseDrawer : public Tool {
private:
    bool drawCircle = true;
public:
    static void Draw4Points(HDC, Vector2D*, int, int, COLORREF);
    static void Cartesian(HDC, Vector2D*, int, int, COLORREF);
    static void Polar(HDC, Vector2D*, int, int, COLORREF);
    static void Bresenham(HDC, Vector2D*, int, int, COLORREF);
    virtual void handleMsg(HWND, UINT, WPARAM, LPARAM) override;
};

#endif