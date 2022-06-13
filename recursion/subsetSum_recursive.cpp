#include<iostream>
#include<vector>
using namespace std;

int countSubsets(int arr[],int n,int sum){
    if(n==0)
        return (sum==0) ? 1 : 0;

    return countSubsets(arr,n-1,sum)+countSubsets(arr,n-1,sum-arr[n-1]);
}


int main(){
    int input[]={10,20,15};
    cout<<countSubsets(input,3,25);

    return 0;
}
