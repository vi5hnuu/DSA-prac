#include<iostream>
using namespace std;

bool isPowerOfTwo_naive(int n){
    if(n==0)
        return false;
    while(n!=1){
        if(n%2!=0)
            return false;
        n/=2;
    }
    return true;
}

bool isPowerOfTwo(unsigned int n){
    //turn of the last set bit and if then the number become zero then it must have been the power of two number...
    //return n && (!(n & (n-1)));

    if(n==0)
        return false;
    return !(n & (n-1));

    //n && here n is for special case when n is zero..
}

int main(){
    cout<<isPowerOfTwo_naive(4)<<endl;
    cout<<isPowerOfTwo_naive(16)<<endl;
    cout<<isPowerOfTwo_naive(6)<<endl;
    cout<<isPowerOfTwo_naive(17)<<endl;
    return 0;
}
