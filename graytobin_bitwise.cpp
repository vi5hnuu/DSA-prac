#include<iostream>
using namespace std;

int grayToBinary(int n){
         int res = n;
        while (n > 0)
        {
            n >>= 1;
            res ^= n;
        }
        return res;

    }

int main(){
    cout<<grayToBinary(32)<<endl;

    return 0;
}
