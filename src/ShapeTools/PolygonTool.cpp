#include "PolygonTool.h"
#include <tuple>
#include <vector>
#include <set>
#include <Utils.h>

typedef std::vector<std::set<EdgeData>> EdgeTable;

void PolygonTool::drawPolygon(HDC hdc, Vector2D* point, int size, COLORREF color) {
    for (int i = 1; i < size; i++) {
        LineDrawer::bresenhamLine(hdc, &point[i - 1], &point[i], color);
    }

    LineDrawer::bresenhamLine(hdc, &point[size - 1], &point[0], color);
}


void PolygonTool::fillPolygon(HDC hdc, Vector2D* polygonList, int size, COLORREF color) {
    EdgeTable edgeTable(600);
    InitializeEdgeTable(edgeTable, polygonList, size);
    FillPolygonUtil(hdc, edgeTable, color);
    

}

void PolygonTool::FillPolygonUtil(HDC hdc, EdgeTable& edgeTable, COLORREF color) {
    for (int i = 0; i < edgeTable.size(); i++) {
        for (auto it = edgeTable[i].begin(); it != edgeTable[i].end(); it++) {
            int xMin = it->xMin;
            int yMax = it->yMax;
            double slope = it->slope;

            int x1 = xMin;
            it++;
            if (it == edgeTable[i].end()) {
                break;
            }
            int x2 = it->xMin;
            double slope2 = it->slope;

            for (int y = i; y < yMax; y++) {
                LineDrawer::bresenhamLine(hdc, new Vector2D(x1, y), new Vector2D(x2, y), color);
                x1 += slope;
                x2 += slope2;
            }
        }

        for (auto it = edgeTable[i].begin(); it != edgeTable[i].end();) {
            if (it->yMax == i) {
                it = edgeTable[i].erase(it);
            }
            else {
                it++;
            }
        }

        //TODO:
        // Update the vaues of XMin.
        // Append the current Set to the Set in the next Iteration.

    }
    
    
}

void PolygonTool::InitializeEdgeTable(EdgeTable& edgeTable, Vector2D* polygonList, int size) {
    for (int i = 0; i < size; i++) {
        Vector2D start = polygonList[i];
        Vector2D end = polygonList[(i + 1) % size];

        if (start.Y() == end.Y()) {
            continue;
        }
        if (start.Y() > end.Y()) {
            Utils::swap(start, end);
        }

        int dx = end.X() - start.X();
        int dy = end.Y() - start.Y();
        double slope = (double)dx / dy;

        EdgeData edgeData(start.X(), end.Y(), slope);
        edgeTable[start.Y()].insert(edgeData);
    }
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