#include<iostream>
using namespace std;

int search_naive(int a[],int n,int target){
    for(int i=0;i<n;i++){
        if(a[i]==target){
            return i;
        }
    }
    return -1;
}
/////////////////////////////////////////
int binarySearch(int a[],int n,int target){
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(a[mid]==target)
            return mid;
        else if(a[mid]<target)
            low=mid+1;
        else
            high=mid-1;
    }
    return -1;
}
///////////////////////////////////////////
/////////////////////////////////////////
int binaryHelper(int a[],int n,int target,int low,int high){
    if(low>high)
        return -1;
    int mid=(low+high)/2;
    if(a[mid]==target)
        return mid;
    else if(a[mid]<target)
        return binaryHelper(a,n,target,mid+1,high);
    else
        return binaryHelper(a,n,target,low,mid-1);
}
int binarySearch_r(int a[],int n,int target){
    return binaryHelper(a,n,target,0,n-1);
}

int main(){
    int a[]={10,20,30,40,50,60};
    //int a[]={5,15,25};
    //int a[]={5,10,15};
    //int a[]={10,15};
    //int a[]={10,10};
    int size=sizeof(a)/sizeof(int);
    //cout<<search_naive(a,size,10);
    cout<<binarySearch_r(a,size,30);

    return 0;
}
