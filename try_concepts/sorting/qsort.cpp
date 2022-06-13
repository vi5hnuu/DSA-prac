#include<iostream>
using namespace std;

int partition(int arr[],int start,int end){
    int pivot=arr[start];

    int count=0;
    for(int i=start+1;i<=end;i++){
        if(arr[i]<=pivot){
            count++;
        }
    }

    int pivotIndex=start+count;
    swap(arr[pivotIndex],arr[start]);

    int i=start,j=end;
    while(i<pivotIndex && j>pivotIndex){
        while(i<pivotIndex && arr[i]<=pivot){
            i++;
        }
        while(j>pivotIndex && arr[j]>pivot){
            j--;
        }
        if(i<pivotIndex && j>pivotIndex){//is this condition necessary(yes as all elements before pivot can be less and all ele after pivot can be more and in that case i==j==is at pivot)
            swap(arr[i++],arr[j--]);
        }
    }
    return pivotIndex;
}

void quickSort(int arr[],int start,int end){
    if(start>=end)
        return;

    int p=partition(arr,start,end);
    quickSort(arr,start,p-1);
    quickSort(arr,p+1,end);
}

int main(){
    int arr[]={1,5,8,9,6,7,3,4,2,0};
    int n=10;
    quickSort(arr,0,n-1);
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }

    return 0;
}
