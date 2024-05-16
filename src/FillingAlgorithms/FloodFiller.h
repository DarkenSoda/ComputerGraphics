#ifndef FLOODFILLER_H
#define FLOODFILLER_H

#include "ShapeFiller.h"

class FloodFiller : public ShapeFiller {
public:
    void fillShape(HDC hdc, Vector2D* start, COLORREF targetColor,COLORREF borderColor, int size) override;
};

#endif