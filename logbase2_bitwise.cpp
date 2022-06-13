#include<iostream>
#include<math.h>
using namespace std;


int log2(int x)
{
    int res = 0;
    while (x >>= 1)
        res++;
    return res;
}

int main(){
cout<<log2(32)<<endl;
cout<<log2(31)<<endl;

return 0;
}
