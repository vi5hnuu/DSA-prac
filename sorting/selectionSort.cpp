#include<iostream>
using namespace std;

void selectionSort(int arr[],int n){
    for(int i=0;i<n-1;i++){
            int max=0;
        for(int j=1;j<n-i;j++){
            if(arr[j]>arr[max])
                max=j;
        }
        if(arr[n-1-i]!=max){
            swap(arr[n-1-i],arr[max]);
        }
    }
}

int main(){
    int arr[]={10,9,8,7,6,5,4,3,2,1};
    //int arr[]={1,2,3,4,5,6,7,8,9,10};
    selectionSort(arr,10);
    for(int x:arr){
        cout<<x<<" ";
    }
    cout<<endl;
}
