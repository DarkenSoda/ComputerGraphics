#ifndef LINECLIIPPER_H
#define LINECLIIPPER_H

#include "src/Utilities/Vectors/Vector2D.h"
#include "src/Utilities/Line/Line.h"

struct ScreenBoarder {
    int XLeft;
    int XRight;
    int YBottom;
    int YTop;
    ScreenBoarder(int XLeft, int XRight, int YBottom, int YTop) {
        this->XLeft = XLeft;
        this->XRight = XRight;
        this->YBottom = YBottom;
        this->YTop = YTop;
    }
};

class ShapeClipper {
public:
    virtual Line* Clip(Line* line, ScreenBoarder screenBoarder) = 0;
};


#endif