#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#define big 1000000
using namespace std;
//c=0 d=2 e=4 f=5 g=7 a=9 b=11
//12

class sint{
public:
    ifstream* in; string stroke; int pos = 0;
    int time = 0; int mi = big; int ma = 0;
    int oktava = 0; double temp=0; int length = 0;
    char c; bool status = true;
    map<char, int> notas{
        {'c', 0}, {'d', 2}, {'e', 4}, {'f', 5}, {'g', 7}, {'a', 9}, {'b', 11},
        {'C', 0}, {'D', 2}, {'E', 4}, {'F', 5}, {'G', 7}, {'A', 9}, {'B', 11}
    };
public:
    sint(string path){in = new ifstream(path);}
    char read(){
        if(pos==stroke.size()){
            pos = 0;
            if(in->eof()) return '!';
            else *in>>stroke;
        }
        return stroke[pos];
    }
    void start(){
        c = read();
        while(c!='!'){
            if(isNota(c)) {nota(); continue;}
            if(c=='>') {forv(); continue;}
            if(c=='<') {back(); continue;}
            if(c=='T' || c=='t') {T(); continue;}
            if(c=='O' || c=='o') {O(); continue;}
            if(c=='L' || c=='l') {L(); continue;}
            if(c=='R' || c=='r') {R(); continue;}
            sintax_error();
        }
    }
    void T(){
        pos++;
        c = read();
        int newTemp = 0;
        if(!isNum(c)) sintax_error();
        while(isNum(c)){
            newTemp*=10;
            newTemp+=(int)(c-'0');
            pos++; c=read();
        }
        temp = newTemp;
    }
    void O(){
        pos++;
        if(!isNum(read())) sintax_error();
        oktava = read()-'0';
        pos++;
        c=read();
    }
    void L(){
        pos++;
        c = read();
        int newLength = 0;
        if(!isNum(read())) sintax_error();
        while(isNum(c)){
            newLength*=10;
            newLength+=(int)(c-'0');
            pos++; c=read();
        }
        length = newLength;
    }
    void back(){if(oktava>0)oktava--; pos++;c=read();}
    void forv(){if(oktava<8)oktava++; pos++;c=read();}
    void R(){
        pos++;
        c = read();
        int dopTime = 0;
        if(!isNum(c)) dopTime = length;
        while(isNum(c)){
            dopTime*=10;
            dopTime+=(int)(c-'0');
            pos++; c=read();
        }
        if(c=='.') {dopTime*=1.5; pos++;}
        time+=big/dopTime/(60/temp);
    }
    void nota(){
        int m = (oktava+1)*12+notas[read()];
        pos++;
        c = read();
        int notaTime = 0;
        if(!isNum(c)) notaTime = length;
        while(isNum(c)){
            notaTime*=10;
            notaTime+=(int)(c-'0');
            pos++; c=read();
        }
        if(c=='+') {pos++;m+=6;}
        if(c=='-') {pos++;m-=6;}
        check(m);
        c = read();
        if(c=='.'){time+=big/notaTime*1.5/(60/temp); pos++;}
        else time+=big/notaTime/(60/temp);
        c=read();
    }
    void check(int m){
        mi = min(mi, m);
        ma = max(ma, m);
    }
    bool isNum(char c){
        int c1 = c - '0';
        if(c1>-1&&c1<10) return true;
        else return false;
    }
    bool isNota(char c){
        if(notas.find(c)!=notas.end()) return true;
        else return false;
    }
    void sintax_error(){status = false;}
};

int main()
{
    sint s("/home/ids/projects/qt_workspace/algo_KT3_ex3/input.txt");
    s.start();
    if(!s.status) cout<<"-1"<<endl;
    cout<<s.time<<' '<<s.mi<<' '<<s.ma<<endl;
}


























