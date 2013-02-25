/*
 * Class Segment, implementation.
 */

#include <cmath>      // for sqrt
#include "segment.h"

Segment::Segment(double x1, double y1, double x2, double y2)
    : p(x1,y1), q(x2,y2) {}

Segment::Segment(const Segment& other) 
    : p(other.p), 
    q(other.q) {}

Segment& Segment::operator=(const Segment& other) {
    if (&other == this) {
        return *this;
    }

    p = Point(other.p);
    q = Point(other.q);
    return *this;
}

void Segment::setToOrigo() {
    p = Point(0, 0);
    q = Point(0, 0);
}

double Segment::getLength() const {
    double dx = p.getX() - q.getX();
    double dy = p.getY() - q.getY();
    return sqrt(dx*dx + dy*dy);
}
