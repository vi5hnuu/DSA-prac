#include<iostream>
using namespace std;

bool isSubarraySumExist(int a[],int n,int k,int targetSum){//modified sliding window
    int sum=0;
    for(int i=0;i<k;i++){
       sum+=a[i];
    }

    if(sum==targetSum)
        return true;
    for(int i=k;i<n;i++){
            sum+=a[i];
            sum-=a[i-k];
    if(sum==targetSum)
        return true;

    }
    return false;
}

int main(){
    int a[]={1,8,30,-5,20,7};
    int x;
    cout<<"What sum to search :";
    cin>>x;
    int x1;
    cout<<"What length subarray :";
    cin>>x1;
    cout<<(isSubarraySumExist(a,6,x1,x)==1 ? "Yes" : "No")<<endl;

    return 0;
}
