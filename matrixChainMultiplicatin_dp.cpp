#include<iostream>
using namespace std;


int mcm(int a[],int len){
    int dp[len-1][len-1]={0};

    for(int i=0;i<len-1;i++){
    for(int j=0;j<len-1;j++){
        dp[i][j]=0;
        }
    }

    for(int gap=0;gap<len-1;gap++){
        for(int i=0,j=gap;j<len-1;i++,j++){
            if(gap==0){
                dp[i][j]=0;
            }else if(gap==1){
                dp[i][j]=a[i]*a[j]*a[j+1];
            }else{
                int min=INT_MAX;
                for(int k=i;k<j;k++){
                    int lc=dp[i][k];
                    int rc=dp[k+1][j];
                    int mc=a[i]*a[k+1]*a[j+1];
                    int  tc=lc+rc+mc;
                    if(tc<min){
                        min=tc;
                    }
                }
                dp[i][j]=min;
            }
        }
    }
    for(int i=0;i<len-1;i++){
    for(int j=0;j<len-1;j++){
        cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main(){
//int a[]={10,20,30,40,50,60};
int a[]={2,3,4,2,5,2};
mcm(a,6);
}
