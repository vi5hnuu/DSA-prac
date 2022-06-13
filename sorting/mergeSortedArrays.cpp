#include<iostream>
#include<algorithm>
using namespace std;

int* mergeSortedArrays_naive(int arr1[],int n,int arr2[],int m){
    int i=0,j=0;
    int *res=new int[n+m];
    for(int i=0;i<n;i++){
        res[i]=arr1[i];
    }
    for(int i=0;i<m;i++){
        res[n+i]=arr2[i];
    }
    sort(res,res+m+n);
    return res;
}

//unstable
/*
[1*,1**,2,3]
[1***,4]
=>[1*,1***,1**,2,3,4]
*/
int* mergeSortedArrays(int arr1[],int n,int arr2[],int m){
    int i=0,j=0;
    int *res=new int[n+m];
    int k=0;
    while(i<n && j<m){
        if(arr1[i]==arr2[j]){
            res[k++]=arr1[i];
            res[k++]=arr1[i];
            i++;j++;
        }
        else if(arr1[i]<arr2[j]){
            res[k++]=arr1[i++];
        }
        else{
            res[k++]=arr2[j++];
        }
    }
    while(i<n){
        res[k++]=arr1[i++];
    }
    while(j<n){
        res[k++]=arr2[j++];
    }
    return res;
}


//stable
/*
[1*,1**,2,3]
[1***,4]
=>[1*,1**,1***,2,3,4]
*/
int* mergeSortedArrays_stable(int arr1[],int n,int arr2[],int m){
    int i=0,j=0;
    int *res=new int[n+m];
    int k=0;
    while(i<n && j<m){
        if(arr1[i]<=arr2[j]){
            res[k++]=arr1[i];
            i++;
        }
        else{
            res[k++]=arr2[j++];
        }
    }
    while(i<n){
        res[k++]=arr1[i++];
    }
    while(j<n){
        res[k++]=arr2[j++];
    }
    return res;
}


int main(){
    int arr1[]={0,1,1,1,2,3,4,5};
    int arr2[]={0,1,1,2,3,4,5};
    //int *arr=mergeSortedArrays(arr1,8,arr2,7);
    //int *arr=mergeSortedArrays_naive(arr1,8,arr2,7);
    int *arr=mergeSortedArrays_stable(arr1,8,arr2,7);
    for(int i=0;i<15;i++){
        cout<<arr[i]<<" ";
    }

    return 0;
}
