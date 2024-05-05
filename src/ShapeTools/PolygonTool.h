#ifndef POLYGONTOOL_H
#define POLYGONTOOL_H

#include "Tool.h"
#include "vector"
#include "LineDrawer.h"

class PolygonTool : public Tool {
private:
    std::vector<Vector2D> pointList;
    bool polygonExists = false;
    bool canFill = false;
public:
    static void drawPolygon(HDC, Vector2D*, int, COLORREF);
    static void fillPolygon(HDC, Vector2D*, int, COLORREF);
    virtual void handleMsg(HWND, UINT, WPARAM, LPARAM) override;
};

#endif