#include "Vector2D.h"
#include "math.h"

Vector2D::Vector2D(int x, int y) : _x(x), _y(y) {}

int Vector2D::X() { return _x; }

int Vector2D::Y() { return _y; }

float Vector2D::Magnitude() const {
    return sqrt(_x * _x + _y * _y);
}

Vector2D Vector2D::Normalize() const {
    float magnitude = Magnitude();
    if (magnitude != 0.0f) {
        return Vector2D(_x / magnitude, _y / magnitude);
    }
    else {
        return Vector2D(0.0f, 0.0f);
    }
}

float Vector2D::Distance(const Vector2D& vec1, const Vector2D& vec2) {
    float dx = vec1._x - vec2._x;
    float dy = vec1._y - vec2._y;
    return sqrt(dx * dx + dy * dy);
}

Vector2D Vector2D::operator+ (const Vector2D& other) const {
    return Vector2D(_x + other._x, _y + other._y);
}

Vector2D Vector2D::operator- (const Vector2D& other) const {
    return Vector2D(_x - other._x, _y - other._y);
}

Vector2D Vector2D::operator* (float scalar) const {
    return Vector2D(_x * scalar, _y * scalar);
}

Vector2D Vector2D::operator/ (float scalar) const {
    if (scalar != 0) {
        return Vector2D(_x / scalar, _y / scalar);
    }
    else {
        return Vector2D(0, 0);
    }
}

Vector2D& Vector2D::operator+= (const Vector2D& other) {
    _x += other._x;
    _y += other._y;
    return *this;
}

Vector2D& Vector2D::operator-= (const Vector2D& other) {
    _x -= other._x;
    _y -= other._y;
    return *this;
}

Vector2D& Vector2D::operator*= (float scalar) {
    _x *= scalar;
    _y *= scalar;
    return *this;
}

Vector2D& Vector2D::operator/= (float scalar) {
    if (scalar != 0.0f) {
        _x /= scalar;
        _y /= scalar;
    }
    else {
        _x = 0;
        _y = 0;
    }
    return *this;
}

bool Vector2D::operator== (const Vector2D& other) const {
    return (_x == other._x) && (_y == other._y);
}

bool Vector2D::operator!=(const Vector2D& other) const {
    return !(*this == other);
}

Vector2D operator* (float scalar, const Vector2D& vec) {
    return vec * scalar;
}

Vector2D::~Vector2D() {}
