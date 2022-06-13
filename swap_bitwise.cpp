#include<iostream>
#include<math.h>
using namespace std;


void swap(int &a,int &b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}

int main(){
int a=32,b=31;
swap(a,b);
cout<<a<<" "<<b;

return 0;
}

