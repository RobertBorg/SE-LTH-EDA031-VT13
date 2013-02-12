/*
 * A point class with x and y coordinates.
 */

#ifndef POINT_H
#define POINT_H

class Point {
public:
    Point(double ix, double iy);
    double getX() const;
    double getY() const;
private:
    double x;  // x coordinate
    double y;  // y coordinate
};

#endif
