#include<iostream>
using namespace std;


void leftRotateArrayBy1(int a[],int n){
    int first=a[0];
    for(int i=1;i<n;i++){
        a[i-1]=a[i];
    }
    a[n-1]=first;
}


int main(){
    int a[]={1,2,3,4,5};
    leftRotateArrayBy1(a,5);

    for(int i=0;i<5;i++){
        cout<<a[i]<<" ";
    }

    return 0;
}
