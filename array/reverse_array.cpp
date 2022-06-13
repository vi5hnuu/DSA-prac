#include<iostream>
using namespace std;

void reverseArray(int arr[],int n){
    for(int i=0;i<n/2;i++){
        if(arr[i]!=arr[n-1-i]){
        int temp=arr[i];
        arr[i]=arr[n-i-1];
        arr[n-i-1]=temp;
        }
    }
}

int main(){
//int input[]={1,2,3,4,5};
int input[]={1,2,3,4,5,6};
reverseArray(input,6);
for(int i=0;i<6;i++){
    cout<<input[i]<<" ";
}

return 0;
}
