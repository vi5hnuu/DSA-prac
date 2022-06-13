#include<iostream>
using namespace std;

void insertionSort(int arr[],int n){
    for(int i=1;i<n;i++){
        int j=i;
        int key=arr[j];
       while(j>0 && key<arr[j-1]){//< and not <=
            arr[j]=arr[j-1];
            j--;
       }
       arr[j]=key;//we do not swap at each iteration
    }
}

int main(){
    int arr[]={10,9,8,7,6,5,4,3,2,1};
    //int arr[]={1,2,3,4,5,6,7,8,9,10};
    insertionSort(arr,10);
    for(int x:arr){
        cout<<x<<" ";
    }
    cout<<endl;
}
