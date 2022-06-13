#include<iostream>
using namespace std;

int mcm(int arr[],int len){//gap strategy
    int dp[len-1][len-1];
    for(int i=0;i<len-1;i++)
    for(int j=0;j<len-1;j++)
    dp[i][j]=0;

    for(int g=0;g<len-1;g++){
        for(int i=0,j=g;j<len-1;i++,j++){
            if(g==0)
            dp[i][j]=0;
            else if(g==1){
                dp[i][j]=arr[i]*arr[j]*arr[j+1];
            }else{

                int min_cost=INT_MAX;
                for(int k=i;k<j;k++){
                    int left_cost=dp[i][k];
                    int right_cost=dp[k+1][j];
                    int m_cost=left_cost+right_cost+arr[i]*arr[k+1]*arr[j+1];
                    if(m_cost<min_cost)
                    min_cost=m_cost;
                }
                dp[i][j]=min_cost;
            }
        }
    }

    for(int i=0;i<len-1;i++){
    for(int j=0;j<len-1;j++){
        cout<<dp[i][j]<<"\t\t";
        }
        cout<<endl;
        cout<<endl;
    }

}

int main(){
int matrix[]={10,20,30,40,50,60};
mcm(matrix,6);

return 0;
}













