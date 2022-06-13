#include<iostream>
#include<math.h>
using namespace std;


bool checkKthBit(int n, int k){
        return (n & (1<<k))!=0;
}

int main(){
    cout<<checkKthBit(52,4)<<endl;

    return 0;
}
