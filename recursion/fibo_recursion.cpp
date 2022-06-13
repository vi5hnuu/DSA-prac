#include<iostream>
using namespace std;

int fibo(int nth){ // 0 1 1 2 3 5 8
    if(nth==0 || nth==1)
    return nth;

    return fibo(nth-1)+fibo(nth-2);
}

int main(){
    cout<<fibo(5)<<endl;
    cout<<fibo(6)<<endl;
}
