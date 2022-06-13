#include<iostream>
using namespace std;


bool subarrayWithGivenSum_naive(int a[],int n,int targetSum){
    for(int i=0;i<n;i++){
    int sum=0;
        for(int j=i;j<n;j++){
            sum+=a[j];
            if(sum==targetSum)
                return true;
        }
    }
    return false;
}

bool subarrayWithGivenSum(int a[],int n,int targetSum){ //like sliding window
    int sum=a[0];
    int k=0;
    for(int i=1;i<n;i++){
         while(sum>targetSum && k<i-1)//k<e-1 means this loop can subtract only upto before current element
            sum-=a[k++];//if number is negative this will further increase the sum instead of decreasing
        if(sum==targetSum){
            return true;
        }
        sum+=a[i];
    }
    return sum==targetSum;
}


int main(){
    int a[]={1,4,20,3,10,500};//non negative integers only in case of subarrayWithGivenSum
    cout<<subarrayWithGivenSum_naive(a,6,23)<<endl;
    cout<<subarrayWithGivenSum(a,6,23)<<endl;

    return 0;
}
