#include "CircleDrawer.h"
#include "EllipseDrawer.h"
#include "RectDrawer.h"
#include "math.h"

void CircleDrawer::Draw8Points(HDC hdc, Vector2D* center, int x, int y, COLORREF color) {
    EllipseDrawer::Draw4Points(hdc, center, x, y, color);
    EllipseDrawer::Draw4Points(hdc, center, y, x, color);
}

void CircleDrawer::Cartesian(HDC hdc, Vector2D* center, int r, COLORREF color) {
    int x = 0, y = r;
    int rsquare = r * r;
    Draw8Points(hdc, center, x, y, color);
    while (x < y) {
        x++;
        y = round(sqrt((double)(rsquare - x * x)));
        Draw8Points(hdc, center, x, y, color);
    }
}

void CircleDrawer::Polar(HDC hdc, Vector2D* center, int r, COLORREF color) {
}

void CircleDrawer::Bresenham(HDC hdc, Vector2D* center, int r, COLORREF color) {
}

void CircleDrawer::DrawCircle(HDC hdc, Vector2D* start, Vector2D* end, COLORREF color) {
    int r1 = abs(start->X() - end->X()) / 2;
    int r2 = abs(start->Y() - end->Y()) / 2;

    r1 = std::min(r1, r2);
    r2 = r1;

    Vector2D newEnd = CircleDrawer::CalculateSquareEndPoint(start, end, r1 + r1);
    end = &newEnd;

    Vector2D centerPoint((start->X() + end->X()) / 2, (start->Y() + end->Y()) / 2);
    RectDrawer::drawRect(hdc, start, end, RGB(255, 0, 0));
    CircleDrawer::Cartesian(hdc, &centerPoint, r1, color);

    // fill with fillColor using flood fill
    // FloodFiller fill;
    // fill.fillShape(ps.hdc, &centerPoint, RGB(0, 0, 255), RGB(0, 255, 0));
}

void CircleDrawer::handleMsg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lp) {
    switch (uMsg) {
    case WM_PAINT:
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        if (canDraw) {
            CircleDrawer::DrawCircle(ps.hdc, startPoint, endPoint, RGB(0, 0, 255));

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

Vector2D CircleDrawer::CalculateSquareEndPoint(Vector2D* start, Vector2D* end, int length) {
    int deltaX = end->X() > start->X() ? length : -length;
    int deltaY = end->Y() > start->Y() ? length : -length;

    return Vector2D(start->X() + deltaX, start->Y() + deltaY);
}