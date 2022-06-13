#include<iostream>
using namespace std;


int main(){
    int *p=new(nothrow) int;
    if(p){
    *p=20;
    cout<<*p<<endl;
    delete p;
    p=NULL;
    }
    p=new(nothrow) int(25);
    if(p){
        cout<<p[0]<<endl;
        delete p;
        p=NULL;
    }

    return 0;
}
