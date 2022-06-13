#include<iostream>
using namespace std;

int binarySearch_countOccurances_naive(int a[],int n){
    int startIndex=-1;
    for(int i=0;i<n;i++)
        if(a[i]==1){
            startIndex=i;
            break;
        }
    if(startIndex==-1)//all zeros
        return 0; //01111
    else
        return n-startIndex;
}
////////////////////////////////////////////////////////////////////////////////////
int binarySearch_firstOccurances(int a[],int n){
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        if( (a[mid]==1) && (mid==0 || (a[mid-1]!=1)))
            return mid;
        else if(a[mid]>=1)
            high=mid-1;
        else
            low=mid+1;
    }
    return -1;
}
int countSorted(int a[],int n){
    int firstOccurance=binarySearch_firstOccurances(a,n);
    if(firstOccurance==-1)
        return 0;
    else
        return n-firstOccurance;
}
////////////////////////////////////////////////////////////////////////////////////
int binarySearch_countOccurances_r(int a[],int n,int low,int high){
    if(low>high)
        return 0;

    int mid=(low+high)/2;
    if(a[mid]==1)
            return 1+binarySearch_countOccurances_r(a,n,low,mid-1)+binarySearch_countOccurances_r(a,n,mid+1,high);
    else if(a[mid]>1)
            return 0+binarySearch_countOccurances_r(a,n,low,mid-1);
    else
            return 0+binarySearch_countOccurances_r(a,n,mid+1,high);

}
int binarySearch_countOccurances_r(int a[],int n){
    return binarySearch_countOccurances_r(a,n,0,n-1);
}
////////////////////////////////////////////////////////////////////////////////////

int main(){
    //int a[]={0,0,0,0,0,1,1,1,1,1,1,1};
    int a[]={0,0,0,0,0};
    int size=sizeof(a)/sizeof(int);
    cout<<countSorted(a,size);
    return 0;
}
