#ifndef CIRCLEDRAWER_H
#define CIRCLEDRAWER_H

#include "Tool.h"

class CircleDrawer : public Tool {
private:
    static void Draw8Points(HDC, Vector2D*, int, int, COLORREF);
    static Vector2D CalculateSquareEndPoint(Vector2D*, Vector2D*, int);
public:
    static void Cartesian(HDC, Vector2D*, int, COLORREF);
    static void Polar(HDC, Vector2D*, int, COLORREF);
    static void Bresenham(HDC, Vector2D*, int, COLORREF);
    static void DrawCircle(HDC, Vector2D*, Vector2D*, COLORREF);
    virtual void handleMsg(HWND, UINT, WPARAM, LPARAM) override;
};

#endif