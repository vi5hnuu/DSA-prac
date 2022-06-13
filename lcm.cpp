#include<iostream>
#include "gcd.cpp"
using namespace std;


int lcm(int a,int b){
    if(a & 1 == 1 && b & 1 == 1)
    return a*b;

    else if(a%b==0 || b%a==0)
    return max(a,b);

    else {
        for(int i=max(a,b);i<=a*b;i++){
            if(i%a==0 && i%b==0)
            return i;
        }
    }
}

int nlcm(int a,int b){
    if(a & 1 == 1 && b & 1 == 1)
    return a*b;

    else {
        for(int i=max(a,b);i<=a*b;i++){
            if(i%a==0 && i%b==0)
            return i;
        }
    }
}

//optimized
int nlcm_o(int a,int b){
    return (a*b)/iEgcd_o(a,b);
}

int main(){
cout<<nlcm_o(4,6)<<endl;
cout<<nlcm_o(12,15)<<endl;
cout<<nlcm_o(2,8)<<endl;
cout<<nlcm_o(3,7)<<endl;

return 0;
}
