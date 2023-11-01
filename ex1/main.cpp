#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#define MAX 10000.0
using namespace std;

struct Point{float X, Y;};

struct Field{
    int H, W; string mapa;
    Point start, finish;
    int start_cell, finish_cell;
    vector<int> curr; vector<int> newcurr;
    vector<vector<Point>> paths;
    void check(int pos, int step){
        if(mapa[pos]=='#') return;
        if(pos==finish_cell) {mapa[pos]=step+1; return;}
        if(mapa[pos]==' ' || mapa[pos]>step+1) {mapa[pos]=step+1; newcurr.push_back(pos); return;}
    }
    void fcheck(int pos, int step){

    }
    void print(){
        for(int i = 0; i<H; i++){
            for(int k = 0; k<W; k++){
                char c = mapa[k+i*W];
                //if(c==' ')cout<<"  ";
                if(c=='#')cout<<c<<c<<' ';
                else if(c<10) cout<<'0'<<(int)c<<' ';
                else cout<<(int)c<<' ';
            }
            cout<<endl;
        }
        cout<<endl;
    }
    void wave(){
        start_cell = (int)start.X+(int)start.Y*W;
        finish_cell = (int)finish.X+(int)finish.Y*W;
        curr.push_back(start_cell); mapa[start_cell]=41;
        while(curr.size()>0){
            for(int i = 0; i<curr.size(); i++){
                check(curr[i]+1, mapa[curr[i]]);
                check(curr[i]-1, mapa[curr[i]]);
                check(curr[i]+W, mapa[curr[i]]);
                check(curr[i]-W, mapa[curr[i]]);
            }
            //print();
            curr = std::move(newcurr);
            newcurr.clear();
        }
        vector<Point> angles{finish};
        backwave(finish_cell, angles, "finish");
        findShortestLine();
    }
    void backwave(int pos, vector<Point> angles, string direction){
        if(mapa[pos]==41) {angles.push_back(start); paths.push_back(angles);}

        if(mapa[pos]-1==mapa[pos+1]){
            if(direction=="up   "){angles.push_back({(float)(pos%W+1), (float)(pos/W+1)});}
            if(direction=="down "){angles.push_back({(float)(pos%W+1), (float)(pos/W)});}
            direction="right";
            backwave(pos+1, angles, direction);
        }
        if(mapa[pos]-1==mapa[pos-1]){
            if(direction=="up   "){angles.push_back({(float)(pos%W),   (float)(pos/W+1)});}
            if(direction=="down "){angles.push_back({(float)(pos%W),   (float)(pos/W)});}
            direction="left ";
            backwave(pos-1, angles, direction);
        }
        if(mapa[pos]-1==mapa[pos-W]){
            if(direction=="right"){angles.push_back({(float)(pos%W),   (float)(pos/W)});}
            if(direction=="left "){angles.push_back({(float)(pos%W+1), (float)(pos/W)});}
            direction="up   ";
            backwave(pos-W, angles, direction);
        }
        if(mapa[pos]-1==mapa[pos+W]){
            if(direction=="right"){angles.push_back({(float)(pos%W),   (float)(pos/W+1)});}
            if(direction=="left "){angles.push_back({(float)(pos%W+1), (float)(pos/W+1)});}
            direction="down ";
            backwave(pos+W, angles, direction);
        }
    }

    void findShortestLine(){//for every path
        float length = MAX;
        float tec = 0;
        for(vector<Point> path : paths){
            for(int i = 1; i<path.size();i++){
                tec+=pif(path[i-1], path[i]);
            } //cout<<tec<<endl;
            length=min(length, tec);
            tec=0;
        }
        cout<<"shortest way: "<<length<<endl;
        //print();
    }
    float pif(Point a, Point b){
        return sqrt((a.X-b.X)*(a.X-b.X)+(a.Y-b.Y)*(a.Y-b.Y));
    }

};

int main()
{
    Field field;
    ifstream in("/home/ids/projects/qt_workspace/algo_KT3_ex1/input.txt");
    in>>field.W;
    in>>field.H;
    in>>field.start.X;
    in>>field.start.Y;
    in>>field.finish.X;
    in>>field.finish.Y;
    string temp;
    while(!in.eof()){
        getline(in, temp);
        field.mapa+=temp;
    }
    field.wave();
//    for(vector<Point> path : field.paths){
//        for(Point p : path){
//            cout<<p.X<<' '<<p.Y<<endl;
//        } cout<<endl;
//    }
}




























