#include "../Headers/LineDrawer.h"
#include "../Headers/Utils.h"

using namespace Utils;

void LineDrawer::directLine(HDC hdc, Vector2D* start, Vector2D* end, COLORREF color) {
    int dx = end->X() - start->X();
    int dy = end->Y() - start->Y();
    double slope;
    if (abs(dy) <= abs(dx)) {
        slope = (double)dy / dx;
        if (start->X() > end->X()) {
            swap(*start, *end);
        }
        for (int x = start->X(); x <= end->X(); x++) {
            double nextY = start->Y() + (x - start->X()) * slope;
            int y = round(nextY);
            SetPixel(hdc, x, y, color);
        }
    }
    else {
        slope = (double)dx / dy;
        if (start->Y() > end->Y()) {
            swap(*start, *end);
        }
        for (int y = start->Y(); y <= end->Y(); y++) {
            double nextX = start->X() + (y - start->Y()) * slope;
            int x = round(nextX);
            SetPixel(hdc, x, y, color);
        }
    }
}

void LineDrawer::simpleDDA(HDC hdc, Vector2D* start, Vector2D* end, COLORREF color) {
    int dx = end->X() - start->X();
    int dy = end->Y() - start->Y();
    SetPixel(hdc, start->X(), start->Y(), color);

    int increment;
    double slope;
    if (abs(dy) <= abs(dx)) {
        int x = start->X();
        double y = start->Y();
        increment = dx > 0 ? 1 : -1;
        slope = (double)dy / dx * increment;
        while (x != end->X()) {
            x += increment;
            y += slope;
            SetPixel(hdc, x, round(y), color);
        }
    }
    else {
        double x = start->X();
        int y = start->Y();
        increment = dy > 0 ? 1 : -1;
        slope = (double)dx / dy * increment;
        while (y != end->Y()) {
            y += increment;
            x += slope;
            SetPixel(hdc, round(x), y, color);
        }
    }
}

void LineDrawer::bresenhamLine(HDC hdc, Vector2D* start, Vector2D* end, COLORREF color) {
}

void LineDrawer::handleMsg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lp) {
    switch (uMsg) {
    case WM_PAINT:
        PAINTSTRUCT ps;
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
    }
}
