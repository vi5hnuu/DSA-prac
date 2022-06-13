#include<iostream>
using namespace std;

int binarySearch_countOccurances_naive(int a[],int n,int target){
    int count=0;
    for(int i=0;i<n;i++)
        if(a[i]==target)
            return count++;
        else if(a[i]>target)
            break;
    return count;
}
////////////////////////////////////////////////////////////////////////////////////
int binarySearch_firstOccurances(int a[],int n,int target){
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        if( (a[mid]==target) && (mid==0 || (a[mid-1]!=target)))
            return mid;
        else if(a[mid]>=target)
            high=mid-1;
        else
            low=mid+1;
    }
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

int countSorted(int a[],int n,int target){
    int firstOccurance=binarySearch_firstOccurances(a,n,target);
    if(firstOccurance==-1)
        return 0;
    else
        return binarySearch_lastOccurances(a,n,target)-firstOccurance+1;
}
////////////////////////////////////////////////////////////////////////////////////
int binarySearch_countOccurances_r(int a[],int n,int target,int low,int high){
    if(low>high)
        return 0;

    int mid=(low+high)/2;
    if(a[mid]==target)
            return 1+binarySearch_countOccurances_r(a,n,target,low,mid-1)+binarySearch_countOccurances_r(a,n,target,mid+1,high);
    else if(a[mid]>target)
            return 0+binarySearch_countOccurances_r(a,n,target,low,mid-1);
    else
            return 0+binarySearch_countOccurances_r(a,n,target,mid+1,high);

}
int binarySearch_countOccurances_r(int a[],int n,int target){
    return binarySearch_countOccurances_r(a,n,target,0,n-1);
}
////////////////////////////////////////////////////////////////////////////////////

int main(){
    int a[]={10,20,30,30,30,30,30,30,30,30,30,30,30,40,50,60,60};
    int size=sizeof(a)/sizeof(int);
    cout<<countSorted(a,size,60);
    return 0;
}
