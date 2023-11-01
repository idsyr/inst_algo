#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

int main()
{
    string info;
    float a, b; bool status = false;
    ifstream in("/home/ids/projects/qt_workspace/algo_KT3_ex4/input.txt");

    int count1 = 0;
    while(!in.eof()){
        in>>a; in>>b;
        if(b>a){count1++;}
        else count1 = 0;
        if(count1==3)break;
    }

    int count2 = 3;
    while(!in.eof()){
        in>>a; in>>b;
        if(b>a){count2++;}
        else break;
    }
    if(count2%6!=0){cout<<"problem: sinhro size not 6x";return -1;}

    for(int i = 0; i<count2*7-1; i++){in>>a; in>>b;}

    int count3 = 0;
    while(!in.eof()){
        in>>a; in>>b;
        in>>a; in>>b;
        in>>a; in>>b; if(a>b) count3++;
        in>>a; in>>b; if(a>b) count3++;
        if(count3==2) break;
        else for(int i = 0; i<count2*2-4; i++){in>>a; in>>b;}
    }
    cout<<a<<' '<<b<<endl;
    int count4 = 0; int count5 = 0; int x = count2/3;
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
//0001001010100110001101100011011011110110
//0001001010100110001101100011011011110110
//011111010001011100101111011001011111011100000



















