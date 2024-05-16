#ifndef GENERALPOLYGONFILLER_H
#define GENERALPOLYGONFILLER_H

#include "ShapeFiller.h"
#include "../Utilities/Utils.h"
#include <vector>
#include <algorithm>
#include <math.h>
#include "../ShapeTools/LineDrawer.h"

#define MAXENTRIES 800

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


class GeneralPolygonFiller : public ShapeFiller
{
    void InitializeEdgeTable(EdgeTable&, Vector2D*, int);
    void FillPolygonUtil(HDC, EdgeTable&, COLORREF);
public:
    void fillShape(HDC hdc, Vector2D* start, COLORREF targetColor, COLORREF borderColor, int size) override;
    
};

#endif