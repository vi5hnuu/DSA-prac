#include<iostream>
using namespace std;


/*
we can do this using 2D [n+1][n+1]
first row all zero
first column except 0,0  is 1
1,1=1
then ncr=n-1cr+n-1cr-1
eg 5c2
0   0   0   0   0   0
1   1   0   0   0   0
1   2   1   0   0   0
1   3   3   1   0   0
1   4   6   4   1   0
1   5   10  10  5   1
*/
//OR
/*
using single array of [r+1]
eg 5c2

_   _   _

1
1   1
1   2   1
1   3   3
1   4   6
1   5   10(ans)
*/

int ncr(int n,int r){
    if(n<r)
    return 0;

    if((n-r)<r)
        r=n-r;

    int mod=1000000007;

    int dp[r+1]={0};
    dp[0]=1;

    for(int i=1;i<=n;i++){//as first array is alredy done
       for(int j=min(r,i);j>0;j--){
            dp[j]=(dp[j]+dp[j-1])%mod;
       }
    }
    return dp[r];
}

//time complexity n*r

int main(){
    cout<<ncr(4,3)<<endl;
    cout<<ncr(4,4)<<endl;
    cout<<ncr(10,5)<<endl;
}
