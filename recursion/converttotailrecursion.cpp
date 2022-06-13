#include<iostream>
using namespace std;

/*
void print1toN(int n){
    if(n==0)
    return;

    print1toN(n-1);
    cout<<n<<" ";
}
*/
////////////////////
void print1toN(int n,int k=1){
    if(n==0)
    return;

    cout<<k<<" ";
    print1toN(n-1,k+1);
}


int main(){
    print1toN(10);

    return 0;
}
