#include "RectDrawer.h"
#include "src/FillingAlgorithms/FloodFiller.h"

void RectDrawer::drawRect(HDC hdc, Vector2D* start, Vector2D* end, COLORREF outlineColor) {
    Vector2D p1(*start);
    Vector2D p3(*end);
    Vector2D p2(p1.X(), p3.Y());
    Vector2D p4(p3.X(), p1.Y());

    LineDrawer::simpleDDA(hdc, &p1, &p2, outlineColor);
    LineDrawer::simpleDDA(hdc, &p2, &p3, outlineColor);
    LineDrawer::simpleDDA(hdc, &p3, &p4, outlineColor);
    LineDrawer::simpleDDA(hdc, &p4, &p1, outlineColor);
}

void RectDrawer::handleMsg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lp) {
    switch (uMsg) {
    case WM_PAINT:
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        if (canDraw) {
            RectDrawer::drawRect(ps.hdc, startPoint, endPoint, RGB(255, 0, 0));

            // fill with fillColor using flood fill
            Vector2D centerPoint((startPoint->X() + endPoint->X()) / 2, (startPoint->Y() + endPoint->Y()) / 2);
            FloodFiller filler;
            filler.fillShape(ps.hdc, &centerPoint, RGB(255, 0, 0), RGB(0, 0, 255));

            delete startPoint;
            delete endPoint;

            canDraw = false;
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
