#include<iostream>
using namespace std;

int maxEleIndex_naive(int array[],int n){
    int j=0;
    for(int i=0;i<n;i++){
            bool flag=true;
    for(int j=0;j<n;j++){
        if(array[j]>array[i]){
                flag=false;
                break;
        }
    }
    if(flag){
            return i;
        }
    }
    return -1;
}

int maxEleIndex(int array[],int n){
    int j=0;
    for(int i=1;i<n;i++){
        if(array[j]<array[i]){
            j=i;
        }
    }
    return j;
}

int main(){
    int input[]={1,2,5,8,4,9,6,3,2};
    cout<<input[maxEleIndex_naive(input,9)]<<endl;

    return 0;
}
