#include<iostream>
#include<math.h>
using namespace std;


int posOfRightMostDiffBit(int m, int n)
    {
        int res=m^n;
        //52,4 =>110100 ^ 000100 => 110000
        //turnoff all except last bit
        res=res & ~(res-1); //110000 & ~(101111) => 110000 & 010000 => 010000
        return (log2(res)+1)<0 ? -1 :(log2(res)+1) ;

}

int main(){
    cout<<posOfRightMostDiffBit(52,4)<<endl;

    return 0;
}
