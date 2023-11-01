#include "field.h"
#include <cmath>

Field::Field(){}

Point* Field::crossPoint(Line& view, Line& portal){
    float Xkek = view.Xkek-portal.Xkek;
    if(Xkek==0) return new Point(0,0,false);
    float Xrealkek = -1 * (view.Dopkek - portal.Dopkek)/Xkek;
    if(view.vertical){Xrealkek = view.Dopkek;}
    float Yrealkek = portal.Xkek*Xrealkek+portal.Dopkek;
    if(portal.vertical){Xrealkek = portal.Dopkek;
    Yrealkek = view.Xkek*Xrealkek+view .Dopkek;}
    return new Point(Xrealkek, Yrealkek, true);
}
bool Field::contact(Line& view, Room::Portal* portal){
    Point* p1 = points[portal->PointNum1];
    Point* p2 = points[portal->PointNum2];
    float leftEdge  = std::min(p1->X,p2->X);
    float rightEdge = std::max(p1->X,p2->X);
    float upEdge    = std::max(p1->Y,p2->Y);
    float downEdge  = std::min(p1->Y,p2->Y);
    Line portalLine(p1, p2);
    Point* contactPoint = crossPoint(view, portalLine);
    if(contactPoint->X > leftEdge  &&
       contactPoint->X < rightEdge &&
       contactPoint->Y > downEdge  &&
       contactPoint->Y < upEdge    &&
       contactPoint->exist)
    {delete contactPoint; return true;}
    else {delete contactPoint; return false;}
}
Point* Field::viewPoint(Room::Portal* p1, Room::Portal* p2){
    Line a1(points[p1->PointNum1], points[p2->PointNum1]);
    Line a2(points[p1->PointNum2], points[p2->PointNum2]);

    Line b1(points[p1->PointNum1], points[p2->PointNum2]);
    Line b2(points[p1->PointNum2], points[p2->PointNum1]);

    if(std::abs(a1.Xkek-a2.Xkek)>std::abs(b1.Xkek-b2.Xkek))
    {std::cout<<crossPoint(a1,a2)->X<<' '; std::cout<<crossPoint(a1,a2)->Y<<std::endl;return crossPoint(a1,a2);}
    else{ std::cout<<crossPoint(b1,b2)->X<<' '; std::cout<<crossPoint(b1,b2)->Y<<std::endl;return crossPoint(b1, b2);}
}
void Field::findAllVisibles(){
    for(Room* r : rooms)
        findVisibles(r);
}
void Field::findVisibles(Room* r){
    r->visibles.insert(r->num);
    std::queue<std::vector<Room::Portal*>> path;
    for(Room::Portal* p : r->portals){
        path.push({p});
    }
    while(!path.empty()){//check must return
        if(check(path.front(), r)) {
            //if(!continueCheck(path.front(), r))
            for(Room::Portal* p : path.front()[path.front().size()-1]->neighbor->portals){
                std::vector<Room::Portal*> temp{path.front()};
                temp.push_back(p); bool pushim = true;
                for(Room::Portal* pp : path.front()){
                    if(pp->PointNum1==p->PointNum1&&pp->PointNum2==p->PointNum2 ||
                       pp->PointNum1==p->PointNum2&&pp->PointNum2==p->PointNum1)
                    {pushim=false; break;}
                }
                if(pushim)path.push(temp);
            }
            r->visibles.insert(path.front()[path.front().size()-1]->neighbor->num);
            path.pop();
        }
        else return;
    }
}
bool Field::check(std::vector<Room::Portal*> path, Room* r){
//    if(std::set<int>::iterator it = r->visibles.find(path[path.size()-1]->neighbor->num); it!=r->visibles.end()){
//        return true;
//    }
    if(path.size()<3) return true;
    Line view(viewPoint(path[0],path[1]), viewPoint(path[path.size()-1], path[path.size()-2]));
    for(int i = 1; i<path.size()-2; i++){
        if(!contact(view, path[i])) return false;
    }
    return true;
}
bool Field::continueCheck(std::vector<Room::Portal*> path, Room* r){
        if(std::set<int>::iterator it = r->visibles.find(path[path.size()-1]->neighbor->num); it!=r->visibles.end()){
            return true;
        } else return false;
}

