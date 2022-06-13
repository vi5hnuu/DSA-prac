#include<iostream>
using namespace std;

void countInversion_naive(int arr[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]>arr[j]){
                cout<<"("<<arr[i]<<" "<<arr[j]<<")"<<endl;
            }
        }
    }
}

//using mergeSort technique to count inversions
int countAndMerge(int arr[],int low,int mid,int high){
    int n1=mid-low+1;
    int n2=high-mid;
    int left[n1],right[n2];
    for(int i=0;i<n1;i++){
        left[i]=arr[low+i];
    }
    for(int i=0;i<n2;i++){
        right[i]=arr[mid+1+i];
    }
    int i=0,j=0,k=low,res=0;
    while(i<n1 && j<n2){
        if(left[i]<=right[j]){
            arr[k++]=left[i++];
        }
        else{
            arr[k++]=right[j++];
            res+=(n1-i);
        }
    }
    while(i<n1){arr[k++]=left[i++];}
    while(j<n2){arr[k++]=right[j++];}
    return res;
}
/*
why
res+=(n1-i);
eg. 3 2 1
no. of inversion = > 2+1 => 3 [(3,2),(3,1),(2,1)]
*/

int countInversion(int arr[],int low,int high){
    int res=0;
    if(low<high){
        int mid=low+(high-low)/2;
        res+=countInversion(arr,low,mid);
        res+=countInversion(arr,mid+1,high);
        res+=countAndMerge(arr,low,mid,high);
    }
    return res;
}

int main(){
    int arr[]={2,4,1,3,5};
    cout<<countInversion(arr,0,4);

    return 0;
}
