#include<iostream>
using namespace std;


struct cust
{
   int p;
   //cust() : p(0) {}
   cust(int q) : p(q) {}
};

int main(){
// Works fine, doesn’t require constructor
cust* var1 = new cust;
//cust* var1 = new cust(20);
delete var1;

return 0;
}
