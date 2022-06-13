#include<iostream>
using namespace std;

int main(){
    unsigned int x=1;
    cout<<~x<<endl;
    x=5;
    cout<<~x<<endl;

    signed int y=1;
    cout<<~y<<endl;
    y=5;
    cout<<~y<<endl;
    y=-1;
    cout<<~y<<endl;
    y=-5;
    cout<<~y<<endl;
}
