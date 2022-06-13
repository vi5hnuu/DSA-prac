#include<iostream>
using namespace std;

/*
int optimalBst(int keys[],int frequency[],int n){
int dp[n][n];

for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
    dp[i][j]=0;


for(int g=0;g<n;g++){
    for(int i=0,j=g;j<n;i++,j++){
        if(g==0){
            dp[i][j]=frequency[i];
        }
        else if(g==1){
            int f1=frequency[i];
            int f2=frequency[j];
            dp[i][j]=min(f1*2+f2,f2*2+f1);
        }
        else{
            int min=INT_MAX;
            int fs=0;
            for(int x=i;x<=j;x++){
                fs+=frequency[x];
            }

            for(int k=i;k<=j;k++){
            int left= k==i ? 0 : dp[i][k-1];
            int right=k==j ? 0 : dp[k+1][j];

            if(left+right+fs<min){
                min=left+right+fs;
                    }
                }
            dp[i][j]=min;
            }
        }
    }

    for(int i=0;i<n;i++){
for(int j=0;j<n;j++){
    cout<<dp[i][j]<<"\t";
        }
        cout<<endl;
    }
    return dp[0][n-1];
}
*/

#include<iostream>
using namespace std;


int optimalBst(int keys[],int frequency[],int n){
int dp[n][n];

for(int i=0;i<n;i++)
for(int j=0;j<n;j++)
    dp[i][j]=0;

int psa[n]={0};
for(int i=0;i<n;i++){
    psa[i]=i==0 ?frequency[0] : psa[i-1]+frequency[i];
}

for(int g=0;g<n;g++){
    for(int i=0,j=g;j<n;i++,j++){
        if(g==0){
            dp[i][j]=frequency[i];
        }
        else if(g==1){
            int f1=frequency[i];
            int f2=frequency[j];
            dp[i][j]=min(f1*2+f2,f2*2+f1);
        }
        else{
            int min=INT_MAX;
            int fs=psa[j]- (i==0 ? 0 : psa[i-1]);

            for(int k=i;k<=j;k++){
            int left= k==i ? 0 : dp[i][k-1];
            int right=k==j ? 0 : dp[k+1][j];

            if(left+right+fs<min){
                min=left+right+fs;
                    }
                }
            dp[i][j]=min;
            }
        }
    }

    for(int i=0;i<n;i++){
for(int j=0;j<n;j++){
    cout<<dp[i][j]<<"\t";
        }
        cout<<endl;
    }
    return dp[0][n-1];
}

int main(){
    int keys[]={10,20,30,40};
    int freq[]={3,1,2,1};
    cout<<optimalBst(keys,freq,4);
}

