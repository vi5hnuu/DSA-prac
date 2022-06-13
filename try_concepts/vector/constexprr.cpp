#include<iostream>
using namespace std;

constexpr int product(int x,int y){return (x*y);}

int main(){
constexpr int x=product(10,20);
cout<<x;

return 0;
}
