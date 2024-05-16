#include "GeneralPolygonFiller.h"


typedef std::vector<EdgeData> EdgeList;
typedef std::vector<EdgeList> EdgeTable;

void GeneralPolygonFiller::InitializeEdgeTable(EdgeTable & edgeTable, Vector2D * polygonList, int size)
{
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

void GeneralPolygonFiller::FillPolygonUtil(HDC hdc, EdgeTable & edgeTable, COLORREF color) {
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

void GeneralPolygonFiller::fillShape(HDC hdc, Vector2D *start, COLORREF targetColor, COLORREF borderColor, int size)
{
    EdgeTable edgeTable(MAXENTRIES);
    InitializeEdgeTable(edgeTable, start, size);
    FillPolygonUtil(hdc, edgeTable, targetColor);
}