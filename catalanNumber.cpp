#include<iostream>
using namespace std;


int main(){
    int n;//which position catalan number is required;
    cin>>n;
    int catalan[n+1]={0};
    catalan[0]=1;
    catalan[1]=1;

    for(int i=2;i<n+1;i++){
        for(int j=0;j<i;j++){
            catalan[i]+=catalan[j]*catalan[i-j-1];
        }
    }
    for(int i=0;i<n+1;i++)
    cout<<catalan[i]<<" ";
}
