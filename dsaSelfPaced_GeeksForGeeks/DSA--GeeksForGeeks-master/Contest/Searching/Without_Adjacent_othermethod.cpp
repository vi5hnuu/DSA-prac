#include<iostream>
using namespace std;

int findMaxSumWithoutAdj(vector<int> arr,int N){
    int dp[N][2];
    if(N==1){
        return arr[0];
    }
    dp[0][0]=0;
    dp[0][1]=arr[1];
    for(int i=1;i<N;i++){
        dp[i][1]=dp[i-1][0]+arr[i];
        dp[i][0]=max(dp[i-1][1],dp[i-1][0]);
    }
    return max(dp[N-1][0],dp[N-1][1]);
}
