#ifndef SHAPEFILLER_H
#define SHAPEFILLER_H

#include <windows.h>
#include "src/Utilities/Vectors/Vector2D.h"

class ShapeFiller {
public:
    virtual void fillShape(HDC hdc, Vector2D* start, COLORREF targetColor, COLORREF borderColor, int size) = 0;
};

#endif