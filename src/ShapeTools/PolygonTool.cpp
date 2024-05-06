#include "PolygonTool.h"

#define MAXENTRIES 800

typedef std::vector<EdgeData> EdgeList;
typedef std::vector<EdgeList> EdgeTable;


void PolygonTool::drawPolygon(HDC hdc, Vector2D* point, int size, COLORREF color) {
    for (int i = 1; i < size; i++) {
        LineDrawer::bresenhamLine(hdc, &point[i - 1], &point[i], color);
    }

    LineDrawer::bresenhamLine(hdc, &point[size - 1], &point[0], color);
}


void PolygonTool::fillPolygon(HDC hdc, Vector2D* polygonList, int size, COLORREF color) {
    EdgeTable edgeTable(MAXENTRIES);
    InitializeEdgeTable(edgeTable, polygonList, size);
    FillPolygonUtil(hdc, edgeTable, color);
}

void PolygonTool::FillPolygonUtil(HDC hdc, EdgeTable& edgeTable, COLORREF color) {
    int y = 0;
    while(y < MAXENTRIES && edgeTable[y].empty()) 
        y++;
    if (y == MAXENTRIES) {
        return;
    }
    EdgeList activeList = edgeTable[y];
    while (activeList.size() > 0) {
        std::sort(activeList.begin(), activeList.end());
        for (auto it = activeList.begin(); it != activeList.end(); it++) {
            int x1 = (int)ceil(it->xMin);
            it++;
            int x2 = (int)floor(it->xMin);
            LineDrawer::bresenhamLine(hdc, new Vector2D(x1, y), new Vector2D(x2, y), color);
        }
        y++;

        for (auto it = activeList.begin(); it != activeList.end();) {
            if (y == it->yMax) {
                activeList.erase(it);
            } else {
                it++;
            }
        }
        for (auto it = activeList.begin(); it != activeList.end(); it++) {
            it->xMin += it->slope;
        }
        activeList.insert(activeList.end(), edgeTable[y].begin(), edgeTable[y].end());
    }
}

void PolygonTool::InitializeEdgeTable(EdgeTable& edgeTable, Vector2D* polygonList, int size) {
    for (int i = 0; i < size; i++) {
        Vector2D V1 = polygonList[i];
        Vector2D V2 = polygonList[(i + 1) % size];

        if (V1.Y() == V2.Y()) {
            continue;
        }
        EdgeData edgeData(V1, V2);
        edgeTable[V1.Y()].push_back(edgeData);
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