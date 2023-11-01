#ifndef PORTAL_H
#define PORTAL_H

#include <vector>
#include "room.h"

class Portal
{
public:
    int PointNum1;
    int PointNum2;
    Room* neighbor;
public:
    Portal();
};

#endif // PORTAL_H
