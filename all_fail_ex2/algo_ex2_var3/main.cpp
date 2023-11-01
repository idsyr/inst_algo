#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

struct Polygon;

struct Point{
    double X; double Y;
    Point(double X, double Y):X(X),Y(Y){}
};

struct Port{
    Polygon* nei;
    int port1;
    int port2;
    Port(Polygon* p, int n1, int n2):nei(p),port1(n1),port2(n2){}
};

struct Line{
    double x;
    double y;
    double c;
    double big_x;
    double lit_x;
    double big_y;
    double lit_y;
    bool pointed = false;
    Line(Point a, Point b){
        if(b.X==a.X || b.Y==a.Y) pointed = true;
        x=1/(b.X-a.X);
        y=1/(b.Y-a.Y);
        c=a.X/(b.X-a.X)-a.Y/(b.Y-a.Y);
        if(a.X>b.X){big_x=a.X; lit_x=b.X;}
        else{big_x=b.X; lit_x=a.X;}
        if(a.Y>b.Y){big_y=a.Y; lit_y=b.Y;}
        else{big_y=b.Y; lit_y=a.Y;}
    }
};

struct Field{
    vector<Point*> points;
    vector<Polygon*> figures;
    void add(Point* p){
        points.push_back(p);
    }
    void add(Polygon* p){
        figures.push_back(p);
    }
    bool contact(Line p, Line l){
        if(p.pointed || l.pointed) return true;
        double c1 = p.x/l.x;
        double c2 = p.y/c1-l.y;
        double c3 = p.c/c1-l.c;
        double com_y = -1/c2*c3; //-c3/c2

        double d1 = p.y/l.y;
        double d2 = p.x/d1-l.x;
        double d3 = p.c/d1-l.c;
        double com_x = 1/d2*d3; //d3/d2

        if(c2==0 || d2==0) return true;
        if(com_y<=p.big_y&&com_y>=p.lit_y && com_x<=p.big_x&&com_x>=p.lit_x)
            return true;
        else
            return false;
    }
    void find_visibles(){
        for(Polygon* p : figures){
            p->find_point_view();
        }
    }

};

struct Polygon{
    int num;
    vector<int> vert;
    vector<Port> ports;
    vector<set<int>> visibles;
    Polygon(int num):num(num){}
    void find_ports(Field field){
        for(Polygon* p : field.figures){
            vector<int> port_num;
            for(int v1 : p->vert){
                for(int v2 : vert){
                    if(v1==v2) port_num.push_back(v1);
                }
            }
            if(port_num.size()==2) {
                ports.push_back(Port(p,port_num[0],port_num[1]));
            }
        }
    }



    Point center_point(int a1, int a2, Field& field){
        return Point((field.points[a1]->X+field.points[a2]->X)/2, (field.points[a1]->Y+field.points[a2]->Y)/2);
    }
    void add(int num){
        vert.push_back(num);
    }
    void find_point_view(){

    }
};


int main()
{
    Field fld;
    int V; float X; float Y;
    int S; int N;
    //ifstream in("/home/ids/projects/qt_workspace/algo_KT3_ex2/task2-map1.txt");
    ifstream in("/home/ids/projects/qt_workspace/algo_KT3_ex2/input.txt");
    if(in.is_open()){
        in>>V;
        while(V--){
            in>>X; in>>Y;
            fld.add(new Point(X,Y));
        }
        in>>S; S++; int FS = S;
        while(S--){
            in>>N;
            Polygon* temp = new Polygon(FS-S-1);
            if(N<0) break;
            while(N--){
                in>>X;
                temp->add(X);
            }
            fld.add(temp);
        }
    }
    in.close();
    clock_t start = clock();
    //////////////////////////////////////////////////
    cout<<"ports:"<<endl;
    for(Polygon* p : fld.figures){
        p->find_ports(fld);
        cout<<p->num<<": ";
        for(Port num : p->ports){
            cout<<num.nei->num<<' ';
        } cout<<endl;
    } cout<<endl;

//    cout<<"visibles:"<<endl;
//    for(Polygon* p : fld.figures){
//        p->find_visibles(fld);
//    }
    ///////////////////////////////////////////////////
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);
}
