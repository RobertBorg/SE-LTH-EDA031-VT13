/*
 * Class Point, implementation.
 */

#include "point.h"

Point::Point(double ix, double iy) {
    x = ix;
    y = iy;
}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}
