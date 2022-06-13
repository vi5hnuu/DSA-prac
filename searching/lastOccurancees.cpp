#include<iostream>
using namespace std;

int binarySearch_lastOccurances_naive(int a[],int n,int target){
    for(int i=n-1;i>=0;i--)
        if(a[i]==target)
            return i;
    return -1;
}

int binarySearch_lastOccurances(int a[],int n,int target){
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        if( (a[mid]==target) && (mid==n-1 || (a[mid+1]!=target)))
            return mid;
        else if(a[mid]>target)
            high=mid-1;
        else
            low=mid+1;
    }
    return -1;
}

int binarySearch_lastOccurances_r(int a[],int n,int target,int low,int high){
    if(low>high)
        return -1;

    int mid=(low+high)/2;
    if( (a[mid]==target) && (mid==n-1 || (a[mid+1]!=target)))
            return mid;
    else if(a[mid]>target)
            binarySearch_lastOccurances_r(a,n,target,low,mid-1);
    else
            binarySearch_lastOccurances_r(a,n,target,mid+1,high);

}

int main(){
    int a[]={10,20,30,30,30,30,30,30,30,30,30,30,30,40,50,60,60};
    int size=sizeof(a)/sizeof(int);
    cout<<binarySearch_lastOccurances(a,size,10);

    return 0;
}
