#include<iostream>
using namespace std;

int main(){
    int n;
    cout<<"Enter no. of values :";
    cin>>n;
    int values[n];
    for(int i=0;i<n;i++)
    cin>>values[i];

    int  target_sum;
    cout<<"Enter target sum :";
    cin>>target_sum;


    bool dp[n+1][target_sum+1]={false};

    for(int i=0;i<n+1;i++){
    for(int j=0;j<target_sum+1;j++){
            if(i==0 && j==0)
                dp[i][j]=true;
            else if(i==0)
                dp[i][j]=false;
            else if(j==0)
                dp[i][j]=true;
            else{
                if(dp[i-1][j]==true)
                    dp[i][j]=true;
                else{
                    int val=values[i-1];
                    if(j>=val){
                        if(dp[i-1][j-val]==true){
                            dp[i][j]=true;
                        }else{
                        dp[i][j]=false;
                        }
                    }else{
                    dp[i][j]=false;
                    }
                }

            }

    }
    }

    for(int i=0;i<n+1;i++){
    for(int j=0;j<target_sum+1;j++){
    cout<<dp[i][j]<<" ";
    }
    cout<<endl;
    }


}
