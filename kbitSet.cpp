#include<iostream>
using namespace std;


bool isKthBitSet(unsigned int n,int k){
   // return (n>>(k-1) & 1 ==1);
    return ((n & (1<<(k-1)))!=0);
}

int main(){
 cout<<isKthBitSet(5,1)<<endl;
 cout<<isKthBitSet(5,2)<<endl;
 cout<<isKthBitSet(5,3)<<endl;
}
