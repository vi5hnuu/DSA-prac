#include<iostream>
using namespace std;



int main(){
    string s1,s2;
    cin>>s1;
    cin>>s2;

    int dp[s1.length()+1][s2.length()+1]={0};
    for(int i=0;i<s1.length()+1;i++){
        for(int j=0;j<s2.length()+1;j++){
           dp[i][j]=0;
        }
    }
    for(int i=s1.length()-1;i>=0;i--){
        for(int j=s2.length()-1;j>=0;j--){
            char c1=s1[i];
            char c2=s2[j];
            if(c1==c2){
                    cout<<c1; //extends from diagonal
                    //watchout for duplicates .look actual ans.
                dp[i][j]=1+dp[i+1][j+1];
            }else{
                dp[i][j]=max(dp[i+1][j],dp[i][j+1]);
            }
        }
    }
    cout<<endl;
    for(int i=0;i<s1.length()+1;i++){
        for(int j=0;j<s2.length()+1;j++){
           cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<dp[0][0]<<endl;
}

//STUDENT VS PLACEMENT => 3 tne
