#include<iostream>
using namespace std;

int partition(int arr[],int low,int high){//pivot is always last element
    int pivot=arr[high];
    int i=low-1;//less than <pivot window
    for(int j=low;j<=high-1;j++){
        if(arr[j]<pivot){
            i++;//increase window of less than pivot
            if(i!=j)//optimization
            swap(arr[j],arr[i]);
        }
    }
    swap(arr[i+1],arr[high]);
    return (i+1);
}
//less than pivot ->to left
//greater than or equal to ->to right
int main(){
    int arr[]={10,80,30,90,40,50,70};
    cout<<partition(arr,0,6)<<endl;

    return 0;
}
