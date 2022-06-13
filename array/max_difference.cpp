#include<iostream>
using namespace std;

int max_Difference_naive(int arr[],int n){//arr[j]-arr[i] = max j>i
    int max=INT_MIN;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
                if(arr[j]-arr[i]>max){
                    max=arr[j]-arr[i];
                }
        }
    }
    return max;
}

int max_Difference(int nums[],int n){//arr[j]-arr[i] = max j>i
    int maxDiff=-1;
        int prev_min_value=INT_MAX;
        for(int i=0;i<n;i++){
            if(nums[i]-prev_min_value>maxDiff && nums[i]!=prev_min_value)
                maxDiff=nums[i]-prev_min_value;

            if(nums[i]<prev_min_value)
                prev_min_value=nums[i];
        }
        return maxDiff;
}

int main(){
    int a[]={2,3,10,6,4,8,1,9};
    //int a[]={7,9,5,6,3,2};
    //int a[]={10,20,30};
    //int a[]={30,20,10};
    cout<<max_Difference(a,8)<<endl;
}
