#include<iostream>
using namespace std;

int kconsTermSum_naive(int a[],int n,int k){ //O((n-k)*k)
    int maxSum=0;
    for(int i=0;i<n-k;i++){
        int sum=0;
        for(int j=i;j<i+k;j++){
            sum+=a[j];
        }
        maxSum=max(maxSum,sum);
    }
    return maxSum;
}
/*
int slidingWindow(int a[],int n,int k){
    int maxSum=0;
    int sum=0;
    for(int i=0;i<n;i++){
        maxSum=max(maxSum,sum);//this happen each time
        if(i<k){
            sum+=a[i];
        }
        else{
            sum+=a[i];
            sum-=a[i-k];
            }
    }
    maxSum=max(maxSum,sum);
    return maxSum;
}
*/
int slidingWindow(int a[],int n,int k){
    int maxSum=0;
    int sum=0;
    for(int i=0;i<k;i++){
       sum+=a[i];
    }
    maxSum=sum;
    for(int i=k;i<n;i++){
            sum+=a[i];
            sum-=a[i-k];
            maxSum=max(maxSum,sum);
    }
    return maxSum;
}

int main(){
    int a[]={1,8,30,-5,20,7};
    cout<<slidingWindow(a,6,1)<<endl;

    return 0;
}
