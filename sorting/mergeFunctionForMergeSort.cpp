#include<iostream>
using namespace std;

void merge_naive(int arr[],int low,int mid,int high){
    int *res=new int[n];//always of size n...waste of memory
    int k=low;//start filling res from here
    int i=low,j=mid+1;
    while(i<=mid && j<=high){
        if(arr[i]<=arr[j]){
            res[k++]=arr[i++];
        }
        else{
            res[k++]=arr[j++];
        }
    }
    while(i<=mid){
            res[k++]=arr[i++];
    }
    while(j<=high){
        res[k++]=arr[j++];
    }
    for(int i=low;i<=high;i++){
        arr[i]=res[i];
    }
    delete[] res;
}

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

int main(){
//low mid high
//0     2   4
//low to mid are sorted
//mid+1 to high are sorted

int arr[]={10,15,20,11,30};
merge(arr,5,0,2,4);

//int arr[]={5,8,12,14,7};
//merge(arr,5,0,3,4);

for(int i=0;i<5;i++){
    cout<<arr[i]<<" ";
}

return 0;
}
