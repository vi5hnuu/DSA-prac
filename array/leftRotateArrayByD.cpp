#include<iostream>
using namespace std;

/*
//sol 1
void leftRotateArrayBy1(int a[],int n){
    int first=a[0];
    for(int i=1;i<n;i++){
        a[i-1]=a[i];
    }
    a[n-1]=first;
}
void leftRotateArrayByD(int a[],int n,int d){ //o(n*d)
    if(n==d)
        return;
    for(int i=0;i<d;i++){
        leftRotateArrayBy1(a,n);
    }
}
*/

/*
void leftRotateArrayByD(int a[],int n,int d){ //o(n) Time complexity , O(d) space complexity
    int temp[n],k=0;//like left rotate by 1(but here temp variable are d)
    for(int i=0;i<d;i++){
        temp[i]=a[i];
    }

    for(int i=0;i<n;i++){
        if(i<n-d){
            a[i]=a[d+i];
        }else{
            a[i]=temp[k++];
        }
    }
}
*/

void reverse(int a[],int low,int high){
    while(low<high){
        swap(a[low],a[high]);
        low++;
        high--;
    }
}

void leftRotateArrayByD(int a[],int n,int d){//O(n) Time ,O(1) space
    reverse(a,0,d-1);
    reverse(a,d,n-1);
    reverse(a,0,n-1);
}


int main(){
    int a[]={1,2,3,6,9,4,5};
    leftRotateArrayByD(a,7,2);
    //leftRotateArrayByD(a,7,4);
    //leftRotateArrayByD(a,7,7);

    for(int i=0;i<7;i++){
        cout<<a[i]<<" ";
    }

    return 0;
}
