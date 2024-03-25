#ifndef LINEDRAWER_H
#define LINEDRAWER_H

#include "Vector2D.h"
#include <windows.h>

class LineDrawer {
public:
    static void directLine(HDC hdc, Vector2D* start, Vector2D* end, COLORREF color);
    static void simpleDDA(HDC hdc, Vector2D* start, Vector2D* end, COLORREF color);
    static void bresenhamLine(HDC hdc, Vector2D* start, Vector2D* end, COLORREF color);
};

#endif