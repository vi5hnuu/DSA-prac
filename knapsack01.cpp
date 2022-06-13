#include<iostream>
using namespace std;


int main(){
    int n;//weights,value array size
    cin>>n;

    int vals[n]={0};
    int weight[n]={0};

    for(int i=0;i<n;i++)
        cin>>vals[i];

    for(int i=0;i<n;i++)
        cin>>weight[i];

    int cap;
    cin>>cap;

    int dp[n+1][cap+1]={0};
    for(int i=0;i<n+1;i++){
        for(int j=0;j<cap+1;j++){
                dp[i][j]=0;
        }
    }


    for(int i=1;i<n+1;i++){
        for(int j=1;j<cap+1;j++){
            if(j>=weight[i-1]){
                int rcap=j-weight[i-1];
                if(dp[i-1][rcap]+vals[i-1]>dp[i-1][j]){
                    dp[i][j]=dp[i-1][rcap]+vals[i-1];
                }
                else{
                    dp[i][j]=dp[i-1][j];
                }
            }else{
                dp[i][j]=dp[i-1][j];
            }
        }
    }

    cout<<dp[n][cap];
}
/*
5
15 14 10 45 30
2 5 1 3 4
7
*/
