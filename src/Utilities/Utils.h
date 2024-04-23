#ifndef UTILS_H
#define UTILS_H

#include "Vectors/Vector2D.h"

namespace Utils {
    void swap(int&, int&);
    void swap(double&, double&);
    void swap(Vector2D&, Vector2D&);
    int round(double);
}

#endif