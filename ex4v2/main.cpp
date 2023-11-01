#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
// b>a
// b<a
using namespace std;

int main()
{
    string info;
    float a, b;
    ifstream in("/home/ids/projects/qt_workspace/algo_KT3_ex4/task4-test2.txt");

receiving_block:
    int x = 0;

    while(!in.eof()){
        in>>a; in>>b;
        if(b>a) break;
    } x++;

    while(!in.eof()){
        in>>a; in>>b;
        if(b>a) x++;
        else break;
    } x/=3;

    for(int i = 0; i<x*15-1; i++){in>>a; in>>b;}

    while(!in.eof()){
        for(int i = 0; i<x+1; i++){in>>a; in>>b;}
        if(b<a) break;
        else{for(int i = 0; i<x*5-1; i++){in>>a; in>>b;}}
    }

    for(int i = 0; i<x-1; i++){in>>a; in>>b;}

    int count4 = 0; int count5 = 0;
    while(!in.eof()){
        for(int i = 0; i<x; i++){in>>a; in>>b; }
        for(int i = 0; i<x; i++){in>>a; in>>b; if(a>b) count4++;}
        if(count4==x) info+="0";
        else{
            for(int i = 0; i<x*2; i++){in>>a; in>>b; if(a>b) count5++;}
            if(count5==x)break;
            info+="1";
        }
        count4=0; count5=0;
    }
    if(!in.eof()) goto receiving_block;

    cout<<info<<endl;
    vector<int> info2; int temp = 0;
    for(int i = 0; i<info.size(); i++){
        if(info[i]=='1')temp+=pow(2,i%8);
        if(i%8==7 && i!=0) {info2.push_back(temp); temp = 0;}
    }
    for(int i : info2){
        cout<<i<<' ';
    } cout<<endl;
    for(int i : info2){
        cout<<char(i);
    } cout<<endl;
}

































