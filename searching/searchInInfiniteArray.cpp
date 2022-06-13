#include<iostream>
using namespace std;

/*
int search(int arr[],int x){//no size is given
    int i=0;
    while(true){
        if(arr[i]==x) return i;
        if(arr[i]>x) return -1;
        i++;
    }
}
*/
/////////////////////////////////////////////////
int binarySearch(int a[],int target,int low,int high){
    if(low>high)
        return -1;
    int mid=(low+high)/2;
    if(a[mid]==target)
        return mid;
    else if(a[mid]<target)
        return binarySearch(a,target,mid+1,high);
    else
        return binarySearch(a,target,low,mid-1);
}
int search(int arr[],int x){//no size is given //unbounded binary search
    if(arr[0]==x)
        return 0;

    int i=1;
    while(arr[i]<x){
            i*=2;
    }
    if(arr[i]==x)
        return i;

    return binarySearch(arr,x,i/2+1,i-1);
}


int main(){

}
