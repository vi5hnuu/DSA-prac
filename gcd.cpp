#include<iostream>
using namespace std;


int igcd(int a,int b){
    int b1=a>b ? b : a;

    for(int i=b1;i>=1;i--){
        if(a%i==0 && b%i==0){
        return i;
        }
    }
}
int rEgcd(int a,int b){
    int a1=a>b ? a : b;
    int b1=a>b ? b : a;
    if(a1==b1)
        return a1;

    rEgcd(a1-b1,b1);
}

int iEgcd(int a,int b){
    while(a!=b){
        if(a>b)
            a=a-b;
        else
            b=b-a;
    }
    return a;
}
//optimzed
int iEgcd_o(int a,int b){
    if(b==0)
        return a;

    rEgcd(b,a%b);
}

int iEgcd_o(int a,int b){
    while(b==0){
        long rem=a%b;
        a=b;
        b=rem;
    }
    return a;
}

/*
int main(){
cout<<iEgcd_o(6,4)<<endl;
cout<<iEgcd_o(4,6)<<endl;
cout<<iEgcd_o(100,200)<<endl;
cout<<iEgcd_o(7,3)<<endl;
}
*/
