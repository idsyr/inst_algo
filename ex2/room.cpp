#include "room.h"

Room::Room(int num):num(num){}
Room::Portal::Portal(){}

//void Room::findVisibles(){
//    std::queue<std::vector<Room::Portal*>> path;
//    for(Portal* p : portals){
//        path.push({p});
//    }
//    while(!path.empty()){
//        if(check(path.front())) visibles.insert(path.front()[path.front().size()-1]->neighbor->num);
//        for(Portal* p : path.front()[path.front().size()-1]->neighbor->portals){
//            std::vector<Room::Portal*> temp{path.front()[path.front().size()-1]};
//            temp.push_back(p); path.push(temp);
//        } path.pop();
//    }
//}
//bool Room::check(std::vector<Room::Portal*> path){
//    if(std::set<int>::iterator it = visibles.find(path[path.size()-1]->neighbor->num); it!=visibles.end()){
//        return true;
//    }
//    bool answer = true;
//    Line a();
//}

