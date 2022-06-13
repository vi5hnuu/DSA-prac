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

        for(int j=arr[0];j<amount+1;j++){
                for(int i=0;i<n;i++){//traverse coins array
            if(j>=arr[i])
            dp[j]+=dp[j-arr[i]];
        }
        }
        for(int i=0;i<=amount;i++)
            cout<<dp[i]<<"\t";
    cout<<endl;
    cout<<dp[amount];
    }
