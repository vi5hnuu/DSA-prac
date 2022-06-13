#include<iostream>
#include "gcd.cpp"
using namespace std;

bool nisPrime(int n){
    if(n==1)
        return false;
    else if(n==2)
        return true;
    else{
        for(int i=2;i<n;i++){
            if(n%i==0)
                return false;
        }
        return true;
    }
}
bool isPrime(int n){
    if(n==1)
        return false;
    else{
        for(int i=2;i*i<=n;i++){
            if(n%i==0)
                return false;
        }
        return true;
    }
}
bool isPrime_o(int n){
    if(n==1)
        return false;
    if(n==2 || n==3)
        return true;
    if(n%2==0 || n%3==0)
        return false;
    else{
        for(int i=5;i*i<=n;i+=6){
            if(n%i==0 || n%(i+2)==0)
                return false;
        }
        return true;
    }
}
/*
int main(){
cout<<(isPrime_o(2) ? "true" : "false")<<endl;
cout<<(isPrime_o(65) ? "true" : "false")<<endl;
cout<<(isPrime_o(7) ? "true" : "false")<<endl;

return 0;
}
*/
