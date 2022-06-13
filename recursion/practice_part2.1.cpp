#include<iostream>
using namespace std;

void bin(int n){
    if(n==0)
    return;
    bin(n/2);
    cout<<(n%2);//16 =>1 0 0 0 0 0 .....
}

int main(){
    bin(16);
    cout<<endl;
    bin(17);

    return 0;
}
