#include<iostream>
using namespace std;


int main(){
    int n;
    cout<<"Which catalan you want :";
    cin>>n;

    int dp[n+1]={0};


    /*
    for(int x:dp)
    cout<<x<<" ";
    cout<<endl;
    */

    dp[0]=dp[1]=1;

    for(int i=2;i<n+1;i++){
        for(int j=0;j<i;j++){
             dp[i]+=dp[j]*dp[i-j-1];
        }
    }
    for(int x:dp)
    cout<<x<<" ";
}
