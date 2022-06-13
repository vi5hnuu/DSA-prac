#include<iostream>
using namespace std;

int removeDuplicates(int arr[],int n){//O(n) time and space
    int temp[n];
    int sizeTemp=0;
    for(int i=1;i<n;i++){
        if(arr[i-1]!=arr[i]){
            temp[sizeTemp++]=arr[i-1];
        }
    }
    int i=0;
    for(i=0;i<sizeTemp;i++){
        arr[i]=temp[i];
    }
    arr[i]=arr[n-1];//last element
    return sizeTemp+1;
}

/*
int removeDuplicates(int arr[],int n){//O(n^2) time,O(1) space
    for(int i=1;i<n;i++){
        if(arr[i-1]==arr[i]){
            for(int j=i;j<n-1;j++){
                arr[j]=arr[j+1];//1 2 3 4 5 5
            }
            n--;
            i--;
        }
    }
    return n;
}
*/

int removeDuplicates_o(int arr[],int n){//O(n) time,O(1) space
    int newSize=1;
    for(int i=1;i<n;i++){
        if(arr[newSize-1]!=arr[i]){
                arr[newSize]=arr[i];
                newSize++;
        }
    }
    return newSize;
}
int main(){
    //int input[]={1,2,3,3,4,5,6,6};//1 2 3 4 5 6 6
    int input[]={1,2,3,3,3,3,3,3,3,3,4,5,5,5,5,5,6,6,6,6,6,6};
    //int input[]={6,6,6,6,6,6};//1 2 3 4 5 6 6
    int newSize=removeDuplicates_o(input,22);
    for(int i=0;i<newSize;i++){
        cout<<input[i]<<" ";
    }

    return 0;
}
