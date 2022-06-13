#include<iostream>
using namespace std;

int searchInSortedRotated(int arr[],int n,int x){
    for(int i=0;i<n;i++){
        if(arr[i]==x){
            return i;
        }
    }
    return -1;
}

int searchInSortedRotated_binary(int arr[],int n,int x){
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        if(arr[mid]==x)
            return mid;
        else if(arr[mid]>arr[low]){ //left half is sorted
            if(arr[low]<=x && arr[mid]>x){
                high=mid-1;
            }
            else{
                low=mid+1;//go to right half as sorted left hald do not have this element
            }
        }
        else{//right half is sorted
          if(arr[mid]<x && arr[high]>=x){
                low=mid+1;
            }
            else{
                high=mid-1;//go to left half as sorted right hald do noot have this e;ement
            }
        }
    }
    return -1;
}

int main(){
    int arr[]={100,200,300,400,20,30,40};
    //cout<<searchInSortedRotated_binary(arr,7,50)<<endl;
    //cout<<searchInSortedRotated_binary(arr,7,40)<<endl;
    cout<<searchInSortedRotated_binary(arr,7,400)<<endl;
    cout<<searchInSortedRotated_binary(arr,7,200)<<endl;


    return 0;
}
