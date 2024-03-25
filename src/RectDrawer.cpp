#include "../Headers/RectDrawer.h"

void RectDrawer::drawRect(HDC hdc, Vector2D* start, Vector2D* end, COLORREF outlineColor, COLORREF fillColor) {
    Vector2D p1(*start);
    Vector2D p3(*end);
    Vector2D p2(p1.X(), p3.Y());
    Vector2D p4(p3.X(), p1.Y());

    LineDrawer::simpleDDA(hdc, &p1, &p2, outlineColor);
    LineDrawer::simpleDDA(hdc, &p2, &p3, outlineColor);
    LineDrawer::simpleDDA(hdc, &p3, &p4, outlineColor);
    LineDrawer::simpleDDA(hdc, &p4, &p1, outlineColor);

    // fill with fillColor using flood fill
}

void RectDrawer::handleMsg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lp) {
    switch (uMsg) {
    case WM_PAINT:
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        if (canDraw) {
            RectDrawer::drawRect(ps.hdc, startPoint, endPoint, RGB(255, 0, 0), RGB(0, 0, 255));
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
