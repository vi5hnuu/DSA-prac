#include<iostream>
using namespace std;

int main(){
int n;
cout<<"Enter number of coins :";
cin>>n;

int arr[n]={0};//coins array
for(int i=0;i<n;i++)
    cin>>arr[i];

    int amount;
    cout<<"What amount to pay :";
    cin>>amount;

    int dp[amount+1]={0};
    dp[0]=1;

    for(int i=0;i<n;i++){ //traverse coins array
        for(int j=arr[i];j<amount+1;j++){
            dp[j]+=dp[j-arr[i]];
        }
    }
    cout<<dp[amount];
    }
