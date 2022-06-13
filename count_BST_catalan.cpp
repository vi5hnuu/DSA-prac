#include<iostream>
using namespace std;

int main(){ //same programm as catalanNumber.cpp
    int n;//no. of nodes given
    cin>>n;
    int catalan[n+1]={0};
    catalan[0]=1;
    catalan[1]=1;

    for(int i=2;i<n+1;i++){
        int leftSubTreeNodes=0;
        int rightSubTreeNodes=i-1;

        while(rightSubTreeNodes>=0){
            catalan[i]+=catalan[leftSubTreeNodes]*catalan[rightSubTreeNodes];
            leftSubTreeNodes++;
            rightSubTreeNodes--;
        }
    }

    for(int i=0;i<n+1;i++)
        cout<<catalan[i]<<" ";
}
