#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D {
private:
    /* data */
    int _x, _y;
public:
    Vector2D(int, int);
    int X();
    int Y();
    static float Distance(Vector2D, Vector2D);
    ~Vector2D();
};

#endif