#include<iostream>
#include "isprime.cpp"
using namespace std;


void primeFactors(int n){
    if(n<2){
        cout<<"No prime factors.\n";
        return;
    }

    for(int i=2;i<=n;i++){
        if(isPrime_o(i) && n%i==0){
            cout<<i<<" ";
            n=n/i;
            i=1;
        }
    }
    cout<<endl;
}

void primeFactors_o(int n){
    if(n<2){
        cout<<"No prime factors.\n";
        return;
    }

    for(int i=2;i*i<=n;i++){
        while(n%i==0){
            cout<<i<<" ";
            n=n/i;
        }
    }
    if(n>1)
        cout<<n;
    cout<<endl;
}

void primeFactors_oo(int n){
    if(n<2){
        cout<<"No prime factors.\n";
        return;
    }

    while(n%2==0){
        cout<<2<<" ";
        n=n/2;
    }
     while(n%3==0){
        cout<<3<<" ";
        n=n/3;
    }
    for(int i=5;i*i<=n;i+=6){
        while(n%i==0){
            cout<<i<<" ";
            n=n/i;
        }
        while(n%(i+2)==0){
            cout<<(i+2)<<" ";
            n=n/(i+2);
        }
    }
    if(n>3)//no itself is prime
        cout<<n;
    cout<<endl;
}
int main(){
    primeFactors_oo(1);
    primeFactors_oo(5);
    primeFactors_oo(12);
    primeFactors_oo(13);
    primeFactors_oo(3);
    primeFactors_oo(315);
    primeFactors_oo(525);
    primeFactors_oo(713816);

    return 0;
}
