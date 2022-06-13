#include<iostream>
#include<vector>
#include "isprime.cpp"
using namespace std;

void printPrimes(int n){
    for(int i=2;i<=n;i++){
        if(isPrime(i))
            cout<<i<<" ";
    }
    cout<<endl;
}

//sieve of erat...
void printPrimess(int n){
     vector<bool> isprimes(n+1,true);
    isprimes[0]=isprimes[1]=false;
    for(int i=2;i*i<=n;i++){
        if(isprimes[i]){
            for(int j=2*i;j<=n;j+=i)
                isprimes[j]=false;
        }
    }
    for(int i=2;i<=n;i++){
        if(isprimes[i])
            cout<<i<<" ";
    }
    cout<<endl;
}
//sieve of erat...
void printPrimess_o(int n){ //nloglogn
     vector<bool> isprimes(n+1,true);
    isprimes[0]=isprimes[1]=false;
    for(int i=2;i<=n;i++){
        if(isprimes[i]){
                cout<<i<<" ";//for i>root n => the below for loop will not run....
            for(int j=i*i;j<=n;j+=i)
                isprimes[j]=false;
        }
    }
    cout<<endl;
}

int main(){
printPrimess_o(20);
printPrimess_o(50);
//printPrimess_o(713816);
}
