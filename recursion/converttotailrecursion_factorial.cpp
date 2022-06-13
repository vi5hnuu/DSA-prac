#include<iostream>
using namespace std;

/*
int fact(int n){
    if(n<=0)
        return 1;
    return n*fact(n-1); //not a tail recursion
    //we have to do computing after function calls
}

int fact(int n){
    if(n<=0)
        return 1;
    return fact(n-1)*n; //not a tail recursion
}
*/
int fact(int n,int res=1){
    if(n<=0)
        return res;
    return fact(n-1,res*n); //tail recursion
}

int main(){
cout<<fact(5)<<endl;
cout<<fact(0)<<endl;
cout<<fact(1)<<endl;

return 0;
}
