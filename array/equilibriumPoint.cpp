#include<iostream>
using namespace std;


int equilibriumPoint_(int a[],int n){//best
    int totalSum=0;
    for(int i=0;i<n;i++){
        totalSum+=a[i];
    }
    int newSum=0;
    for(int i=0;i<n;i++){
        if(newSum*2==totalSum-a[i])//prefix sum technique
            return i;
        newSum+=a[i];
    }
    return -1;
}

//using prefixSum technique
int equilibriumPoint(int a[],int n){
    for(int i=1;i<n;i++){
        a[i]+=a[i-1];//change the actual array
    }
    for(int i=0;i<n;i++){
        if((i!=0 ? a[i-1] : 0) ==(a[n-1]-a[i]))
            return i;
    }
    return -1;
}

int main(){
    //int a[]={3,4,8,-9,20,6};
    //int a[]={4,2,-2};
    int a[]={2,-2,4};
    cout<<equilibriumPoint(a,3)<<endl;

    return 0;
}
