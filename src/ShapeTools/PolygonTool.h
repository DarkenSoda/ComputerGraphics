#ifndef POLYGONTOOL_H
#define POLYGONTOOL_H

#include "Tool.h"
#include "LineDrawer.h"
#include "src/Utilities/Utils.h"
#include <vector>
#include <algorithm>
#include <math.h>


class EdgeData {
public:
    double xMin;
    double yMax;
    double slope;
    EdgeData(Vector2D& V1,Vector2D& V2) {
        if (V1.Y() > V2.Y()) {
            Utils::swap(V1, V2);
        }
        xMin = V1.X();
        yMax = V2.Y();
        slope = (double)(V2.X() - V1.X()) / (V2.Y() - V1.Y());
    }
    bool operator<(const EdgeData& other) const{
        return xMin < other.xMin;
    }
};

typedef std::vector<EdgeData> EdgeList;
typedef std::vector<EdgeList> EdgeTable;

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



#endif