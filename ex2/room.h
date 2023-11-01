#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <set>
#include <queue>


class Room
{
public:
    class Portal
    {
    public:
        int PointNum1;
        int PointNum2;
        Room* neighbor;
    public:
        Portal();
    };
public:
    std::vector<int> pointsNums;
    std::vector<Portal*> portals;
    std::set<int> visibles;
    int num;
public:
    Room(int num);
//    void findVisibles();
//    bool check(std::vector<Room::Portal*> path);

};

#endif // ROOM_H
