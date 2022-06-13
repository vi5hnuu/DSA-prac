#include<iostream>
using namespace std;


int countSetBits_naive(unsigned int n){ //o(no. of bits)
    int count=0;
    while(n>0){
        if(n & 1){
            count++;
        }
        n>>=1;
    }
    return count;
}
int countSetBits(unsigned int n){//o(no. of set bits)
    int count=0;
    while(n>0){
      n=n&(n-1);//turn off last set bit
      count++;
    }
    return count;
}

//using lookUptable (when we want to see no of set bits in many numbers)
int table[256];
void initilize(){
    table[0]=0;
    for(int i=1;i<256;i++){
        table[i]=(i&1)+table[i/2];
    }
}
int count(int n){
    int res=table[n & 0xff];
    n=n>>8;
    res+=table[n & 0xff];
    n=n>>8;
    res+=table[n & 0xff];
    n=n>>8;
    res+=table[n & 0xff];
    return res;
}

int main(){
    initilize();
    cout<<count(2)<<endl;
    cout<<count(3)<<endl;
    cout<<count(15)<<endl;
    cout<<count(7)<<endl;
}
