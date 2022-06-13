#include<iostream>
using namespace std;

bool isSorted_naive(int arr[],int n){
    for(int i=0;i<n-1;i++){
    for(int j=i+1;j<n;j++){
        if(arr[j]<arr[i])
            return false;
        }
    }
    return true;
}

bool isSorted(int arr[],int n){
    for(int i=1;i<n;i++){
        if(arr[i-1]>arr[i])
            return false;
    }
    return true;
}

int main(){
    //int input[]={10,10,10};
    //int input[]={1,2,2,3};
    //int input[]={1,2,2,1};
    int input[]={1};
    cout<<(isSorted(input,1) ? "Yes" : "No")<<endl;

    return 0;
}
