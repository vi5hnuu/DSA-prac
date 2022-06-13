#include<iostream>
using namespace std;


void moveZerosToEnd_naive(int a[],int n){
    for(int i=0;i<n-1;i++){
        if(a[i]==0){
                bool iszerofound=false;
            for(int j=i+1;j<n;j++){
                if(a[j]!=0){
                    iszerofound=true;
                swap(a[i],a[j]);
                    break;
                }
            }
        if(!iszerofound)
            break;
        }
    }
}
/*
void moveZerosToEnd(int a[],int n){
    int start=0;
    for(int i=1;i<n;i++){
        if(a[start]==0){
            if(a[i]!=0){
                //a[start++]=a[i];
                a[start]=a[i];
                a[i]=0;
            }
        }else{
            start++;
        }
    }
}
*/

void moveZerosToEnd(int a[],int n){
    int size=0;
    for(int i=0;i<n;i++){
            if(a[i]!=0){
                if(i!=size){
                    a[size]=a[i];
                    a[i]=0;
                }

                size++;
            }
    }
}
int main(){
    int arr[]={8,5,0,10,0,20};
    //int arr[]={0,0,0,10,0};
    //int arr[]={10,0,0,0,0};
    //int arr[]={10,20};
    moveZerosToEnd(arr,6);

    for(int i=0;i<6;i++){
        cout<<arr[i]<<" ";
    }

    return 0;
}
