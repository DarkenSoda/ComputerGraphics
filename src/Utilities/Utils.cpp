#include "Utils.h"

void Utils::swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

void Utils::swap(double& x, double& y) {
    double temp = x;
    x = y;
    y = temp;
}

void Utils::swap(Vector2D& v1, Vector2D& v2) {
    Vector2D temp = v1;
    v1 = v2;
    v2 = temp;
}

int Utils::round(double x) {
    return int(x + 0.5);
}
