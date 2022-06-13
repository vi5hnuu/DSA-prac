#include<iostream>
using namespace std;

int floo_log2(int n){
    if(n==1)
        return 0;
    else
        return 1+floo_log2(n/2);
}
int floo_log3(int n){
    if(n<3)
        return 0;
    else
        return 1+floo_log3(n/3);
}

int main(){
   cout<<floo_log2(16)<<endl;
   cout<<floo_log3(16)<<endl;

    return 0;
}
