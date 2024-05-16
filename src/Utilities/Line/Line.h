#ifndef LINE_H
#define LINE_H

#include "src/Utilities/Vectors/Vector2D.h"

class Line {
    Vector2D* start;
    Vector2D* end;
public:
    Line(Vector2D* start, Vector2D* end);
    ~Line();
    Vector2D* Intersect(Line* line2);
    Vector2D* VerticalIntersect(int X);
    Vector2D* HorizontalIntersect(int Y);

    Vector2D* Start() { return start; }
    Vector2D* End() { return end; }
    void SetStart(Vector2D* start) { this->start = start; }
    void SetEnd(Vector2D* end) { this->end = end; }
};

#endif