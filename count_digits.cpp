#include<iostream>
#include<math.h>
using namespace std;

int idigit_count(int num=0){
    int count=0;
    while(num!=0){
        count++;
        num/=10;
    }
    return count;
}

int rdigit_count(int num=0){
    if(num==0){
        return 0;
    }

    return 1+rdigit_count(num/10);
}


int ldigit_count(int num=0){
    if(num==0)
        return 0;
    return floor(log10(num)+1);
}

/*
int main(){
    cout<<idigit_count(123)<<endl;
    cout<<idigit_count()<<endl;

    cout<<rdigit_count(123)<<endl;
    cout<<rdigit_count()<<endl;

    cout<<ldigit_count(123)<<endl;
    cout<<ldigit_count()<<endl;

    return 0;
}
*/
