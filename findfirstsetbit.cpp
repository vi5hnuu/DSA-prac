#include<iostream>
#include<math.h>
using namespace std;


//simple and compact…

unsigned int getFirstSetBit(int n){
    n=n & ~(n-1); //turn off all bit except the last(from lsb) set bit
    return log2(n)+1;//log2(n) return what power of 2 bit is on
}

int main(){
    cout<<getFirstSetBit(12)<<endl;

    return 0;
}
