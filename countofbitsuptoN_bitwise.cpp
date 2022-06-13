#include<iostream>
#include<math.h>
using namespace std;


//naive
 /*
        int arr[256];
        arr[0]=0;
        for(int i=1;i<256;i++){
            arr[i]=(i & 1)+arr[i/2];
        }

        int count=0;
        for(int i=1;i<=n;i++){
            int k=i;
            count+=arr[k & 0xff];
            k>>=8;
            count+=arr[k & 0xff];
            k>>=8;
            count+=arr[k & 0xff];
            k>>=8;
            count+=arr[k & 0xff];
        }
        return count;*/
//////////////////////////////////
int largestPowerOf2inRange(int n){
    /*int x=0;
    while((1<<x)<=n){
        x++;
    }
    return x-1;*/
    return log2(n);
}

int solve(int n){
    if(n==0){
        return 0;
    }

    int x=largestPowerOf2inRange(n);
    int before2X=x*(1<<(x-1)); //x*pow(2,x-1);
    int msb2XtoN=n-(1<<x)+1;
    int rest=n-(1<<x);
    int ans=before2X+msb2XtoN+solve(rest);
    return ans;
}

int main(){
    /*cout<<largestPowerOf2inRange(32)<<endl;
    cout<<largestPowerOf2inRange(17)<<endl;*/

    cout<<solve(18)<<endl;

    return 0;
}
