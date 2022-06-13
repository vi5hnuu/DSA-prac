#include<iostream>
using namespace std;

int partition(int arr[],int low,int high){
//In this partition we take first element as pivot
//pivot may not be at its correct position after partition
//but smaller than pivot will be  on left
// and element greater than pivot in on right side
//this function divide array in two parts

int pivot=arr[low];
int i=low-1;
int j=high+1;
while(true){
    do{
        i++;
    }while(arr[i]<pivot);
    do{
        j--;
    }while(arr[j]>=pivot);
    if(i>=j)
        return j;
    swap(arr[i],arr[j]);
}
}

int main(){
int arr[]={5,3,8,4,2,7,1,5};
cout<<partition(arr,0,7)<<endl;
for(int i=0;i<8;i++){
    cout<<arr[i]<<" ";
}
}
