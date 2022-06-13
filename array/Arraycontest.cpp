#include<iostream>
using namespace std;

/*
int f(int n)
{
   static int i = 1;
   if (n >= 5)
      return n;
   n = n+i;
   i++;
   return f(n);
}

int main(){
    cout<<f(1);

    return 0;
}

*/

/*
int fun(int n){
  int x=1,k;
  if(n==1)
    return x;
  for(k=1;k<n;++k)
     x=x+fun(k)*fun(n-k);
  return x;
}

int main(){
    cout<<fun(5)<<endl;

    return 0;
}
*/

/*
unsigned int foo(unsigned int n, unsigned int r) {
  if (n  > 0) return (n%r +  foo (n/r, r ));
  else return 0;
}

int main(){
    cout<<foo(513,2)<<endl;

    return 0;
}
*/

 void f (int n)
{
  if (n <=1)  {
   cout<<n;
  }
  else {
   f(n/2);
   cout<<(n%2);
  }
}

int main(){
    f(173);

    return 0;
}
