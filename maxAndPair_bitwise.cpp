#include<iostream>
#include<math.h>
using namespace std;


int maxAndPair_naive(int a[],int n){
    int maximum=0;
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            maximum=max(maximum,a[i]&a[j]);
        }
    }
    return maximum;
}

////////////////////////////
int checkBit(int pattern,int arr[],int n){
    int count=0;
    for(int i=0;i<n;i++){
        if((pattern & arr[i])==pattern)
            count++;
    }
    return count;
}
int maxAnd(int arr[],int n){
    int res=0;
    int count;
    for(int bit=31;bit>=0;bit--){
        count=checkBit(res|(1<<bit),arr,n);

        if(count>=2)
            res|=(1<<bit);
    }
    return res;
}

int main(){
int a[]={1,2,7,8,5,3,6,9,1};
    cout<<maxAnd(a,9)<<endl;
}
