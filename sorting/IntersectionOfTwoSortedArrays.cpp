#include<iostream>
using namespace std;


void intersectionOfTwoSorted(int arr1[],int n,int arr2[],int m){
    int i=0,j=0;
    while(i<n && j<m){
        if(arr1[i]==arr2[j]){
            if(i==0 || (i>0 && arr1[i-1]!=arr1[i])){
                cout<<arr1[i]<<" ";
            }
            i++;
            j++;
        }else if(arr1[i]<arr2[j]){
            i++;
        }
        else{
            j++;
        }
    }
}

int main(){

    int arr1[]={3,5,10,10,10,15,20};
    int arr2[]={5,10,10,15,30};
    intersectionOfTwoSorted(arr1,7,arr2,5);


    /*
    int arr1[]={1,1,3,3,3};
    int arr2[]={1,1,1,1,3,5,7};
    intersectionOfTwoSorted(arr1,5,arr2,7);
    */

    return 0;
}
