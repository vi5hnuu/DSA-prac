#include<iostream>
using namespace std;

void printFreqInSortedArray(int a[],int n){
    int count=1;
    for(int i=1;i<n;i++){
        if(a[i-1]==a[i]){
            count++;
        }else{
            cout<<a[i-1]<<" : "<<count<<endl;
            count=1;
        }
    }
    cout<<a[n-1]<<" : "<<count<<endl;
}

int main(){
    //int a[]={10,10,10,25,30,30};
    //int a[]={10,10,10,10};
    //int a[]={10,20,30};
    int a[]={10,10,10,30,30,40};
    printFreqInSortedArray(a,6);
    return 0;
}
