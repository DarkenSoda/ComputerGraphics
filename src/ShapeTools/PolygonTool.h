#ifndef POLYGONTOOL_H
#define POLYGONTOOL_H

#include "Tool.h"
#include "vector"
#include "LineDrawer.h"


typedef std::vector<std::set<EdgeData>> EdgeTable;
class PolygonTool : public Tool {
private:
    std::vector<Vector2D> pointList;
    bool polygonExists = false;
    bool canFill = false;
    static void InitializeEdgeTable(EdgeTable&, Vector2D*, int);
    static void FillPolygonUtil(HDC, EdgeTable&, COLORREF);
public:
    static void drawPolygon(HDC, Vector2D*, int, COLORREF);
    static void fillPolygon(HDC, Vector2D*, int, COLORREF);
    virtual void handleMsg(HWND, UINT, WPARAM, LPARAM) override;
};

class EdgeData {
public:
    int xMin;
    int yMax;
    double slope;
    EdgeData(int xMin, int yMax, double slope) : xMin(xMin), yMax(yMax), slope(slope) {}
    int operator<(const EdgeData& other) {
        return xMin < other.xMin;
    }
};

#endif