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

    float Magnitude() const;
    Vector2D Normalize() const;

    // static methods
    static float Distance(const Vector2D&, const Vector2D&);

    // operators
    Vector2D operator+ (const Vector2D&) const;
    Vector2D operator- (const Vector2D&) const;
    Vector2D operator* (float) const;
    Vector2D operator/ (float) const;
    Vector2D& operator+=(const Vector2D&);
    Vector2D& operator-=(const Vector2D&);
    Vector2D& operator*=(float);
    Vector2D& operator/=(float);
    bool operator==(const Vector2D&) const;
    bool operator!=(const Vector2D&) const;
    friend Vector2D operator* (float, const Vector2D&);

    ~Vector2D();
};

#endif
