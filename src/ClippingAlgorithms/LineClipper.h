#ifndef LINECLIIPPINGTOOL_H
#define LINECLIIPPINGTOOL_H

#include "src/ClippingAlgorithms/ShapeClipper.h"


union OutCode 
{
    unsigned All : 4;
    struct 
    {
        unsigned Top : 1;
        unsigned Bottom : 1;
        unsigned Right : 1;
        unsigned Left : 1;
    };
};


class LineClipper : public ShapeClipper {
    OutCode ComputeOutCode(Vector2D* point, ScreenBoarder screenBoarder);
    
public:
    Line* Clip(Line* line, ScreenBoarder screenBoarder) override;
};


#endif