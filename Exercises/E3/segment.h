/* 
 * Class Segment: describes a line segment with a start  point and  
 * an end point. getLength computes the length of the line, setToOrigo
 * changes the line to be from origo to origo and has been introduced
 * to give a simple example of a member function that changes the state
 * of the segment.
 *
 * This version uses pointers to Point objects to represent
 * the start point and the end point.
 */

#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

class Segment {
public:
    Segment(double x1, double y1,         // a line from (x1,y1) to (x2,y2)
            double x2, double y2);
    Segment(const Segment& other);            // copy constructor
    Segment& operator=(const Segment& other); // assignment operator
    void setToOrigo();                    // line from (0,0) to (0,0)
    double getLength() const;             // the length of the line
    
private:
    Point p; // pointer to the start point
    Point q; // pointer to the end point
};

#endif
