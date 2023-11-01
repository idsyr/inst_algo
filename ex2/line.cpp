 #include "line.h"

Line::Line(Point* a, Point* b)
{

    Xkek = (b->Y - a->Y)/(b->X - a->X);
    Dopkek = -1 * Xkek * a->X + a->Y;
    if(b->X==a->X){
       vertical = true;
       Dopkek = b->X;
    }

}
