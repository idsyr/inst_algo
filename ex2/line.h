#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line
{
public:
    float Xkek;
    float Dopkek;
    bool vertical = false;
public:
    Line(Point* a, Point* b);
};

#endif // LINE_H
