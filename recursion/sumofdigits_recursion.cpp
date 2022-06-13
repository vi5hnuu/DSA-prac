#include<iostream>
using namespace std;

int digitSum(int n){
    if(n<=9)
        return n;
    return (n%10)+digitSum(n/10);
}

int main(){
    cout<<digitSum(52)<<endl;
    cout<<digitSum(123456789)<<endl;

    return 0;
}
