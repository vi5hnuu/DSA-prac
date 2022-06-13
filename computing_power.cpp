#include<iostream>
using namespace std;

long pow(int x,int n){
    int calc=1;
    for(int i=1;i<=n;i++)
        calc*=x;

    return calc;
}

long power(int x,int n){
    if(n==0)
        return 1;
    if(n%2==0){
        long result=power(x,n/2);
        return result*result;
    }
    else{
        long result=power(x,(n-1));
        return result*x;
    }
}

//same but compact
long power_r(int x,int n){
    if(n==0)
        return 1;
        long result=power_r(x,n/2);
        result*=result;
        if(n%2==0)
            return result;
        else
            return result*x;

}
long long power_i(int x,int n){//Binary exponentiation
    //The idea is that a decimal number can be represented in its binary form which contain logn bits so iterating thos bits will require logn time

    long long multiplier=x;
    long long result=1;
    while(n!=0){
        if(n&1){
            result*=multiplier;
        }
        n>>=1;
        multiplier*=multiplier;
    }

    return result;
}

int main(){
    cout<<power_i(5,2)<<endl;
    cout<<power_i(5,4)<<endl;
    cout<<power_i(5,5)<<endl;
    cout<<power_i(5,0)<<endl;
    cout<<power_i(5,1)<<endl;
}
