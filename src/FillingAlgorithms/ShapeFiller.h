#ifndef SHAPEFILLER_H
#define SHAPEFILLER_H

#include <windows.h>
#include "src/Utilities/Vectors/Vector2D.h"

class ShapeFiller {
public:
    virtual void fillShape(HDC hdc, Vector2D* start, COLORREF borderColor, COLORREF targetColor) = 0;
};

#endif