#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

#include "point.h"
#include "field.h"
#include "room.h"

using namespace std;

int main()
{
    ifstream in("/home/ids/projects/qt_workspace/algo_KT3_ex2/input2.txt");
    Field field;
    float x, y;
    int n; in>>n;
    while(n--){
        in>>x; in>>y;
        field.points.push_back(new Point(x,y,true));
    }
    vector<int> portalPieses;
    in>>n; int nn, num; int s = n; s--;
    map<int, vector<int>> m; int msize = 0;
    while(n--){
        portalPieses.clear();
        in>>nn; Room* room = new Room(s-n);
        while(nn--){
            in>>num;
            m.insert({num, {}});
            if(m.size()==msize) {portalPieses.push_back(num);}
            m[num].push_back(s-n);
            room->pointsNums.push_back(num);
            msize=m.size();
        }
        field.rooms.push_back(room);
        if(portalPieses.size()>1){
            for(int k= 0; k<portalPieses.size(); k++) {int i = portalPieses[k]; for(int ii : m[i]){
                    for(int k1 = k; k1<portalPieses.size(); k1++) {int i1 = portalPieses[k1]; for(int ii1 : m[i1]){
                            if(ii==s-n) continue;
                            if(ii1==s-n) continue;
                            if(i==i1) continue;
                            if(ii==ii1){
                                Room::Portal* r1 = new Room::Portal(); r1->PointNum1=i; r1->PointNum2=i1; r1->neighbor=field.rooms[ii];
                                field.rooms[s-n]->portals.push_back(r1);
                                Room::Portal* r2 = new Room::Portal(); r2->PointNum1=i; r2->PointNum2=i1; r2->neighbor=field.rooms[s-n];
                                field.rooms[ii]->portals.push_back(r2);
                            }
                    }}
            }}
        }
    }

    m.clear();

    for(Room* r : field.rooms){
        cout<<r->num<<": ";
        for(Room::Portal* p : r->portals){
            cout<<p->neighbor->num;
        }cout<<endl;
    }
    //find ports
    field.findAllVisibles();
    for(Room* r : field.rooms){
        cout<<r->num<<": ";
        for(int p : r->visibles){
            cout<<p;
        }cout<<endl;
    }

    cout<<endl;
    //cout<<1/-1<<endl;
    //Line l1(new Point(0,0, true), new Point(1,0, true));
    //Line l2(new Point(0,0, true), new Point(0,1, true));
    //cout<<l2.Xkek<<' '<<l2.Dopkek<<' '<<endl;
    //cout<<field.crossPoint(l1, l2)->X<<field.crossPoint(l1, l2)->Y<<endl;

}
