#ifndef FIELD_H
#define FIELD_H

#include <vector>
#include <iostream>
#include "point.h"
#include "room.h"
#include "line.h"

class Field
{
public:
    std::vector<Point*> points;
    std::vector<Room*> rooms;
public:
    Field();
    void findAllVisibles();
    Point* crossPoint(Line& view, Line& portal);
    bool contact(Line& view, Room::Portal* portal);
    Point* viewPoint(Room::Portal* p1, Room::Portal* p2);
    void findVisibles(Room* r);
    bool check(std::vector<Room::Portal*> path, Room* r);
    bool continueCheck(std::vector<Room::Portal*> path, Room* r);
};

#endif // FIELD_H
