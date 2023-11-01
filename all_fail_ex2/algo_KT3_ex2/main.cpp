#include <iostream>
#include <fstream>
#include <vector>
#include <set>

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
    void find_visibles(Field& field){
        set<int> visi; visi.insert(num);
        for(Port& i : ports){
            visi.insert(i.nei->num);
        }
        for(Port& p : ports){
            vector<pair<int, int>> strik;
            strik.push_back({p.port1, p.port2});
            p.nei->find(strik, center_point(p.port1, p.port2, field), field, visi);
        }
        cout<<num<<": ";
        for(int i : visi){
            cout<<i<<' ';
        } cout<<endl;
    }
    void find(vector<pair<int, int>> strik, Point start, Field& field, set<int>& visi){
        for(Port& p : ports){
                bool must_skip = false;
                for(pair<int, int> i : strik){
                    if(i.first==p.port1 && i.second==p.port2) must_skip = true;
                }
                if(must_skip) continue;

                strik.push_back({p.port1, p.port2});
                bool allcont = true;
                for(pair<int, int>& pii : strik){
                    if(
                            !field.contact(Line(*field.points[pii.first],*field.points[pii.second]),Line(center_point(p.port1, p.port2, field), start)) //||
                            //!field.contact(Line(*field.points[pii.first],*field.points[pii.second]),Line(*field.points[p.port1], start)) ||
                            //!field.contact(Line(*field.points[pii.first],*field.points[pii.second]),Line(*field.points[p.port2], start))
                            ){allcont=false; break;}
                }
                if(allcont){visi.insert(p.nei->num);}
                else return;
                p.nei->find(strik, start, field, visi);
        }
    }
    Point center_point(int a1, int a2, Field& field){
        return Point((field.points[a1]->X+field.points[a2]->X)/2, (field.points[a1]->Y+field.points[a2]->Y)/2);
    }
    void add(int num){
        vert.push_back(num);
    }
};

int main()
{
    Field fld;
    int V; float X; float Y;
    int S; int N;
    ifstream in("/home/ids/projects/qt_workspace/algo_KT3_ex2/task2-map1.txt");
    //ifstream in("/home/ids/projects/qt_workspace/algo_KT3_ex2/input.txt");
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

    cout<<"visibles:"<<endl;
    for(Polygon* p : fld.figures){
        p->find_visibles(fld);
    }
    ///////////////////////////////////////////////////
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("The time: %f seconds\n", seconds);
}



//0: 0 1 2 3 4 5 6 8 9 16 17 21 22
//1: 0 1 2 3 4 5 6 8 9 16 17 21 22
//2: 0 1 2 3 4 5 6 7 8 9 11 12 15 16 17 21 22 25 28 29
//3: 0 1 2 3 4 5 6 8 9 16 17 21 22
//4: 0 1 2 3 4 5 6 8 9 16 17 21 22
//5: 0 1 2 3 4 5 6 7 8 9 11 12 15 16 17 18 21 22 25 28 29
//6: 0 1 2 3 4 5 6 7 8 9 11 12 15 16 17 21 22 25 28 29
//7: 2 3 4 5 6 7 8 9 11 12 15 16 25 28 29
//8: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 15 16 17 18 21 22 25 28 29
//9: 0 1 2 3 4 5 6 7 8 9 10 12 16 17 21 22
//10: 0 1 2 3 4 5 6 7 8 9 10 12 16 17 21 22
//11: 0 1 2 3 4 5 6 7 8 9 11 12 13 14 15 16 17 21 22 25 28 29
//12: 2 3 5 6 7 8 9 10 11 12 13 15 17 25 28 29
//13: 0 1 2 3 4 5 6 7 8 9 11 12 13 14 15 16 17 21 22
//14: 0 1 2 3 4 5 6 7 8 9 11 12 13 14 15 16 17 21 22
//15: 2 3 5 6 7 8 9 11 12 13 14 15 25 28 29
//16: 0 1 2 3 4 5 6 8 9 16 17 18 19 20 21 22 27
//17: 0 1 2 3 4 5 6 8 9 12 16 17 18 19 20 21 22 27
//18: 5 8 16 17 18 19 20 27
//19: 16 17 18 19 20 27 29
//20: 16 17 18 19 20 22 23 24 26 27 29
//21: 0 1 2 3 4 5 6 8 9 16 17 21 22 23
//22: 0 1 2 3 4 5 6 8 9 16 17 20 21 22 23 24 27
//23: 20 21 22 23 24 25 26 27
//24: 20 22 23 24 25 26 27
//25: 2 5 6 7 8 11 12 15 23 24 25 26 27 28 29
//26: 20 23 24 25 26 27
//27: 16 17 18 19 20 22 23 24 25 26 27
//28: 2 5 6 7 8 11 12 15 24 25 28 29
//29: 2 5 6 7 8 11 12 15 19 20 24 25 28 29


//0: 0 1 2 3 4 5 6 8 9 16 17 21 22
//1: 0 1 2 3 4 5 6 8 9 16 17 21 22
//2: 0 1 2 3 4 5 6 8 9 16 17 21 22
//3: 0 1 2 3 4 5 6 8 9 16 17 21 22
//4: 0 1 2 3 4 5 6 8 9 16 17 21 22
//5: 0 1 2 3 4 5 6 8 9 16 17 21 22
//6: 0 1 2 3 4 5 6 7 8 9 12 16 17 21 22
//7: 3 6 7 9 12
//8: 0 1 2 3 4 5 6 8 9 10 11 12 13 16 17 18 21 22
//9: 0 1 2 3 4 5 6 7 8 9 10 12 16 17 21 22
//10: 0 1 2 3 4 5 6 7 8 9 10 12 16 17 21 22
//11: 0 1 2 3 4 5 6 8 9 11 13 14 15 16 17 21 22
//12: 3 6 7 8 9 10 12 13 15
//13: 0 1 2 3 4 5 6 7 8 9 11 12 13 14 15 16 17 21 22
//14: 0 1 2 3 4 5 6 7 8 9 11 12 13 14 15 16 17 21 22
//15: 3 6 7 9 11 12 13 14 15
//16: 0 1 2 3 4 5 6 8 9 16 17 18 19 20 21 22 27
//17: 0 1 2 3 4 5 6 8 9 12 16 17 18 19 20 21 22 27
//18: 16 17 18 19 20 27
//19: 16 17 18 19 20 27
//20: 16 17 18 19 20 26 27
//21: 0 1 2 3 4 5 6 8 9 16 17 21 22 23
//22: 0 1 2 3 4 5 6 8 9 16 17 21 22 23 24
//23: 21 22 23 24 25
//24: 22 23 24 25 26
//25: 23 24 25 26 27 28 29
//26: 20 24 25 26 27
//27: 16 17 18 19 20 25 26 27
//28: 24 25 28 29
//29: 24 25 28 29


//0: 0 1 2 3 4
//1: 0 1 2 3 4 5
//2: 0 1 2 3 4 5 7
//3: 0 1 2 3 4 5 7
//4: 0 1 2 3 4 5 6 7
//5: 0 1 2 3 4 5 6 8
//6: 4 5 6 8
//7: 0 1 2 3 4 7
//8: 5 6 8


























