#include<iostream>
using namespace std;


int greyConverter(int n){
    return n ^ (n>>1);
}

int main(){
    cout<<greyConverter(32)<<endl;

    return 0;
}
