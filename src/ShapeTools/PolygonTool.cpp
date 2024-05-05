#include "PolygonTool.h"

void PolygonTool::drawPolygon(HDC hdc, Vector2D* point, int size, COLORREF color) {
    for (int i = 1; i < size; i++) {
        LineDrawer::bresenhamLine(hdc, &point[i - 1], &point[i], color);
    }

    LineDrawer::bresenhamLine(hdc, &point[size - 1], &point[0], color);
}

void PolygonTool::fillPolygon(HDC, Vector2D*, int, COLORREF) {
    
}

void PolygonTool::handleMsg(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lp) {
    switch (uMsg) {
    case WM_LBUTTONDOWN:
        if (polygonExists) {
            pointList.clear();
            polygonExists = false;
        }

        pointList.push_back(Vector2D(LOWORD(lp), HIWORD(lp)));
        if(pointList.size() > 1) {
            LineDrawer::bresenhamLine(GetDC(hwnd), &pointList[pointList.size() - 2], &pointList[pointList.size() - 1], RGB(0, 0, 0));
        }
        break;
    case WM_RBUTTONDOWN:
        if (pointList.size() > 1) {
            polygonExists = true;

            LineDrawer::bresenhamLine(GetDC(hwnd), &pointList[0], &pointList[pointList.size() - 1], RGB(0, 0, 0));
        }

        break;
    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            if (polygonExists) {
                PolygonTool::fillPolygon(GetDC(hwnd), pointList.data(), pointList.size(), RGB(255, 144, 0));

                pointList.clear();
                polygonExists = false;
            }
        }
        break;
    }
}