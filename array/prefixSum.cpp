#include<iostream>
#include<vector>
using namespace std;


void prefixSum_naive(int a[],int n,int low,int high){
    int sum=0;
    for(int i=low;i<n && i<=high;i++){
        sum+=a[i];
    }
    cout<<sum<<" ";
}

////////////////////////////////////////////////////
bool preProcessing=true;
void prefixSum(int a[],int n,int low,int high){
    for(int i=1;i<n && preProcessing;i++){
        a[i]=a[i]+a[i-1];
        if(i==n-1)
            preProcessing=false;
    }
    if(low!=0)
    cout<<(a[high]-a[low-1])<<" ";
    else
    cout<<(a[high])<<" ";
}

int main(){
    int a[]={8,3,9,6,5,4};
    prefixSum(a,6,0,3);
    prefixSum(a,6,2,4);
    prefixSum(a,6,2,5);
    prefixSum(a,6,5,5);
    prefixSum(a,6,6,5);

    return 0;
}
