#include<iostream>
using namespace std;

void bubbleSort(int arr[],int n){
    for(int i=0;i<n-1;i++){
            bool isSwapped=false;//for optimization
        for(int j=1;j<n-i;j++){
            if(arr[j]<arr[j-1]){
                isSwapped=true;
                swap(arr[j],arr[j-1]);
            }
        }
        if(!isSwapped){
                //cout<<"Breaking.\n";
            break;
        }
    }
}

int main(){
    //int arr[]={10,9,8,7,6,5,4,3,2,1};
    int arr[]={1,2,3,4,5,6,7,8,9,10};
    bubbleSort(arr,10);
    for(int x:arr){
        cout<<x<<" ";
    }
    cout<<endl;
}
