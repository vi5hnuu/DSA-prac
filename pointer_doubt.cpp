#include<iostream>
using namespace std;

int main(){
    /*
    int *p[2];//array of two pointer
    p[0]=new int[10];
    p[1]=new int[10];
    //p[1][9]=90;
    //(*(p++))[9]=90;//wrong as p is const
    (*(p+1))[9]=90;//ok
    cout<<(p[1][9]);
    */


    int (*p)[10];//pointer to array of 10 int
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    p=&a;
    //p=new int[9];//wrong as p should point to array of 10 int

    cout<<(*p[0])<<endl;
    cout<<(p[0][3]);

}
