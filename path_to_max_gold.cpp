#include<iostream>
using namespace std;


int max_ele(int a,int b,int c){
    if(a>b){
        if(a>c)
            return a;
        else
            return c;
    }else{
        if(b>c)
            return b;
        else
            return c;
    }

}

int main(){

    int n,m;
    cin>>n>>m;
    int gold[n][m];
    for(int i=0;i<n;i++)
    for(int j=0;j<m;j++)
        cin>>gold[i][j];


    int dp[n][m];
    for(int i=m-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(i==m-1)
            dp[j][i]=gold[j][i];
            else{
            int m1=0,m2=0,m3=0;

            if(j-1>=0)
            m1=gold[j][i]+dp[j-1][i+1];

            m2=gold[j][i]+dp[j][i+1];

            if(i+1<n)
            m3=gold[j][i]+dp[j+1][i+1];


            dp[j][i]=max_ele(m1,m2,m3);
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout<<dp[i][j]<<"\t";
        }
        cout<<endl;
    }

    int max_val=dp[0][0];
    for(int i=0;i<n;i++)
        if(dp[i][0]>max_val)
        max_val=dp[i][0];
    cout<<"\nMaximum gold that can be extracted is "<<max_val<<endl;
}


/*
6 6
0 1 4 2 8 2
4 3 6 5 0 4
1 2 4 1 4 6
2 0 7 3 2 2
3 1 5 9 2 4
2 7 0 8 5 1
*/
