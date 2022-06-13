#include<iostream>
using namespace std;

int main(){
int n;
cout<<"Enter no. of values :";
cin>>n;
cout<<endl;
int vals[n];
int weights[n];
for(int i=0;i<n;i++){
    cin>>vals[i];
}
for(int i=0;i<n;i++){
    cin>>weights[i];
}

int cap=-1;
cin>>cap;

int dp[n+1][cap+1];
for(int i=0;i<=n;i++)
for(int j=0;j<=cap;j++){
dp[i][j]=0;
}

for(int i=0;i<=n;i++){
for(int j=0;j<=cap;j++){
cout<<dp[i][j]<<"\t";
}
cout<<endl;
}
for(int i=1;i<=n;i++)
for(int j=1;j<=cap;j++){
    if(weights[i-1]>j)
        dp[i][j]=dp[i-1][j];
    else if(j>=weights[i-1]){
        if(dp[i-1][j]<vals[i-1]+dp[i-1][j-weights[i-1]]){
           dp[i][j]=vals[i-1]+dp[i-1][j-weights[i-1]];
        }
        else{
            dp[i][j]=dp[i-1][j];
        }
    }

}
for(int i=0;i<=n;i++){
for(int j=0;j<=cap;j++){
cout<<dp[i][j]<<"\t";
}
cout<<endl;
}
cout<<dp[n][cap];

}
