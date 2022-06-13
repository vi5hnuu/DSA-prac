#include<bits/stdc++.h>
using namespace std;
int countbits(int n){
    int count=0;

    while(n>0){
        count++;
        n=n & (n-1);
    }
    return count;
}
/*
void printRes_naive(int a[],int n,int k){


    for(int i=0;i<n-k+1;i++){
    int maxBits=0;
    int maxElementIndex;
            for(int j=i;j<i+k;j++){
            int curBits=countbits(a[j]);
            if(curBits>=maxBits){
            maxElementIndex=j;
            maxBits=curBits;
            }
    }
    cout<<a[maxElementIndex]<<" ";

    }

}
*/
void printRes(int a[],int n,int k){
/*
    int maxBits=0;
    int maxElementIndex=-1;
    int secondMaxElementIndex;
    for(int i=0;i<k;i++){
            int curBits=countbits(a[i]);
            if(curBits>=maxBits){
            secondMaxElementIndex=maxElementIndex;
            maxElementIndex=i;
            maxBits=curBits;
            }
    }
        cout<<a[maxElementIndex]<<" ";*/

        vector<int> bitCount(n,0);
        for(int i=0;i<n;i++)
            bitCount[i]=countbits(a[i]);

        cout<<endl;
        for(int i=0;i<n;i++){
            cout<<bitCount[i]<<" ";
        }
        cout<<endl;


}

int main(){
    int N,K;
    cin>>N>>K;
    int a[N];
    for(int i=0;i<N;i++)
        cin>>a[i];

    printRes(a,N,K);
    return 0;
}
