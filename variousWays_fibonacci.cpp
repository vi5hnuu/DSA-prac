#include<iostream>
using namespace std;

/*
int fib(int n){
    if(n<=1)
        return n;
    return fib(n-1)+fib(n-2);
}

int main(){
    int n=9;
    cout<<fib(n);
    return 0;
}
*/


/*
You cannot declare a static array of variable size because its space
is allocated in the Data Segment (or bss segment in case of an
uninitialized variable). Hence the compiler needs to know the size
at the compile time and will complain if the size is not a constant.
*/
/*
int fib(int n){
    cout<<"called"<<endl;
    static int *a=new int[n+1]{0};
    a[0]=0;
    a[1]=1;

    if(n<=1)
        return a[n];

    return (a[n-1]!=0 ? a[n-1] : a[n-1]=fib(n-1))+(a[n-2]!=0 ? a[n-2] : a[n-2]=fib(n-2));
}

int main(){
    int n=9;
    cout<<fib(n);
    return 0;
}
*/

/*
int fib(int n){
    int f[n+1];
    int i;
    f[0]=0;
    f[1]=1;

    for(int i=2;i<=n;i++){
        f[i]=f[i-1]+f[i-2];
    }

    return f[n];
}

int main(){
    int n=9;
    cout<<fib(n);
    return 0;
}
*/

int fib(int n){
    int a=0,b=1;
    if(n<=1)
        return n;
    for(int i=2;i<=n;i++){
        int c=a+b;
        a=b;
        b=c;
    }
    return b;
}

int main(){
    int n=9;
    cout<<fib(n);
    return 0;
}
