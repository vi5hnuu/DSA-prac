#include<iostream>
using namespace std;

void merge(int arr[],int low,int mid,int high){ //O(high-low)
    int sizeLeft=mid-low+1;
    int sizeRight=high-mid;
    int left[sizeLeft],right[sizeRight];
    for(int i=low;i<=mid;i++){
        left[i-low]=arr[i];
    }
    for(int i=mid+1;i<=high;i++){
        right[i-(mid+1)]=arr[i];
    }
    int k=low;//start filling res from here
    int i=0,j=0;
    while(i<sizeLeft && j<sizeRight){
        if(left[i]<=right[j]){
            arr[k++]=left[i++];
        }
        else{
            arr[k++]=right[j++];
        }
    }
    while(i<sizeLeft){
            arr[k++]=left[i++];
    }
    while(j<sizeRight){
        arr[k++]=right[j++];
    }
}

void mergeSort(int arr[],int low,int high){
    if(high>low){
        int mid=low+(high-low)/2;
        mergeSort(arr,low,mid);
        mergeSort(arr,mid+1,high);
        merge(arr,low,mid,high);
    }
}
int main(){
int arr[]={10,15,20,11,30};
mergeSort(arr,0,4);
for(int x:arr)
    cout<<x<<" ";

return 0;
}
