#include "Line.h"

Line::Line(Vector2D *start, Vector2D *end)
{
    this->start = start;
    this->end = end;
}

Line::~Line()
{
    delete start;
    delete end;
}

Vector2D *Line::Intersect(Line *line)
{
    if ((this->start->X() == line->start->X() && this->start->Y() == line->start->Y()) ||
        (this->end->X() == line->end->X() && this->end->Y() == line->end->Y())) {
        return nullptr; // Both lines are the same, no intersection
    }

    float slope1, slope2;
    if (this->end->X() != this->start->X()) {
        slope1 = (this->end->Y() - this->start->Y()) / (this->end->X() - this->start->X());
    } else {
        slope1 = __INT_MAX__;
    }
    if (line->end->X() != line->start->X()) {
        slope2 = (line->end->Y() - line->start->Y()) / (line->end->X() - line->start->X());
    } else {
        slope2 = __INT_MAX__;
    }
    if (slope1 == slope2) {
        return nullptr;
    }

    float c1, c2;
    if (slope1 != __INT_MAX__) {
        c1 = this->start->Y() - slope1 * this->start->X();
    } else {
        c1 = this->start->X();
    }
    if (slope2 != __INT_MAX__) {
        c2 = line->start->Y() - slope2 * line->start->X();
    } else {
        c2 = line->start->X();
    }

    float x, y;
    if (slope1 != __INT_MAX__ && slope2 != __INT_MAX__) {
        x = (c2 - c1) / (slope1 - slope2);
        y = slope1 * x + c1;
    } else {
        x = this->start->X();
        y = slope2 * x + c2;
    }

    return new Vector2D(x, y);
}

Vector2D *Line::VerticalIntersect(int X)
{
    if (this->start->X() == this->end->X()) {
        return nullptr; 
    }
    float deltaY = this->end->Y() - this->start->Y();
    float deltaX = this->end->X() - this->start->X();
    
    float slope = deltaY / deltaX;
    float c = this->start->Y() - slope * this->start->X();

    float y = slope * X + c;
    
    return new Vector2D(X, y);
}


Vector2D *Line::HorizontalIntersect(int Y)
{
    if (this->start->Y() == this->end->Y()) {
        return nullptr; 
    }
    float deltaY = this->end->Y() - this->start->Y();
    float deltaX = this->end->X() - this->start->X();
    
    if (deltaX == 0) {
        return new Vector2D(this->start->X(), Y);
    }

    float slope = deltaY / deltaX;
    float c = this->start->Y() - slope * this->start->X();
    float x = (Y - c) / slope;
    
    return new Vector2D(x, Y);
}
