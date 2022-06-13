#include <iostream>
using namespace std;

/*
int fun(int n){

    if (n == 4)

       return n;

    else return 2*fun(n+1);

}

int main(){
    cout<<fun(2);

    return 0;
}
*/

/*
int fun(int x, int y) {
    if (x == 0)
        return y;

    return fun(x - 1,  x + y);
}

int main(){
    cout<<fun(4,3)<<endl;

    return 0;
}
*/

/*
void fun(int n){
    if (n == 0)
        return;

    cout<<(n%2);//10011
    fun(n/2);
}

int main(){
    fun(25);

    return 0;
}
*/

/*
int fun(int x, int y){

    if (y == 0)
        return 0;

    return (x + fun(x, y-1));
}

int main(){
    cout<<fun(2,5)<<endl;

    return 0;
}
*/

/*
void print(int n){

    if (n > 4000)
        return;

    cout<<n;
    print(2*n);

    cout<<n;
}



int main(){
    print(1000);

    return 0;
}
*/

/*
int fun(unsigned int n){

    if (n == 0 || n == 1)
        return n;

    if (n%3 != 0)
        return 0;

    return fun(n/3);
}

int main(){
    cout<<fun(15)<<endl;//It returns 1 when n is a power of 3, otherwise returns 0

    return 0;
}
*/

/*
int f(int n){
    if(n <= 1)
        return 1;

    if(n%2 == 0)
        return f(n/2);

    return f(n/2) + f(n/2+1);
}

int main(){
    cout<<f(11);
    return 0;
}
*/

 unsigned int foo(unsigned int n, unsigned int r) {

  if (n  > 0)
    return (n%r +  foo (n/r, r ));
  else
    return 0;
}

int main(){
    cout<<foo(345,10)<<endl;//sum of decimal digits
    cout<<foo(513,2)<<endl; //sum of binary digits
}
