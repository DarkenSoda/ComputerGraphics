#include "EllipseDrawer.h"
#include "RectDrawer.h"
#include "CircleDrawer.h"
#include "src/FillingAlgorithms/FloodFiller.h"
#include <math.h>

void EllipseDrawer::Draw4Points(HDC hdc, Vector2D* center, int x, int y, COLORREF color) {
    int xc = center->X();
    int yc = center->Y();

    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc - x, yc - y, color);
}

void EllipseDrawer::Cartesian(HDC hdc, Vector2D* center, int r1, int r2, COLORREF color) {
    int r1square = r1 * r1;
    int r2square = r2 * r2;

    // First Region
    int x = r1;
    int y = 0;
    Draw4Points(hdc, center, x, y, color);
    while (x > 0) {
        x--;
        y = round((double)r2 / r1 * sqrt((double)r1square - x * x));
        Draw4Points(hdc, center, x, y, color);
    }

    // Second Region
    x = 0;
    y = r2;
    Draw4Points(hdc, center, x, y, color);
    while (y > 0) {
        y--;
        x = round((double)r1 / r2 * sqrt((double)r2square - y * y));
        Draw4Points(hdc, center, x, y, color);
    }
}

void EllipseDrawer::Polar(HDC hdc, Vector2D* center, int r1, int r2, COLORREF color) {
}

void EllipseDrawer::Bresenham(HDC hdc, Vector2D* center, int r1, int r2, COLORREF color) {
    int r1square = r1 * r1;
    int r2square = r2 * r2;

    int x = 0;
    int y = r2;
    double d = r2square + r1square * (0.25 - r2);
    Draw4Points(hdc, center, x, y, color);
    while (x <= r1) {
        if (d < 0) {
            d += r2square * (2 * x + 3);
        }
        else {
            d += r2square * (2 * x + 3) + 2 * r1square * (1 - y);
            y--;
        }
        x++;

        Draw4Points(hdc, center, x, y, color);
    }
}

void EllipseDrawer::handleMsg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lp) {
    switch (uMsg) {
    case WM_PAINT:
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        if (canDraw) {
            if (drawCircle) {
                CircleDrawer::DrawCircle(ps.hdc, startPoint, endPoint, RGB(0, 0, 255));
            }
            else {
                int r1 = abs(startPoint->X() - endPoint->X()) / 2;
                int r2 = abs(startPoint->Y() - endPoint->Y()) / 2;

                Vector2D centerPoint((startPoint->X() + endPoint->X()) / 2, (startPoint->Y() + endPoint->Y()) / 2);
                RectDrawer::drawRect(ps.hdc, startPoint, endPoint, RGB(255, 0, 0));
                EllipseDrawer::Cartesian(ps.hdc, &centerPoint, r1, r2, RGB(0, 0, 255));

                // fill with fillColor using flood fill
                // FloodFiller fill;
                // fill.fillShape(ps.hdc, &centerPoint, RGB(0, 0, 255), RGB(0, 255, 0));
            }

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
    case WM_KEYDOWN:
        if (wParam == VK_SHIFT) {
            drawCircle = true;
        }
        break;
    case WM_KEYUP:
        if (wParam == VK_SHIFT) {
            drawCircle = false;
        }
        break;
    }
}
