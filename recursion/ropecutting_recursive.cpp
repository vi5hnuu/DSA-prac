#include<iostream>
using namespace std;

int max(int a,int b,int c){
    return a>b ? (a>c ? a:c) : (b>c ? b : c);
}

int ropeCut(int n,int a,int b,int c){
    if(n<0)
        return -1;
    if(n==0)
        return 0;
    int count1=ropeCut(n-a,a,b,c);
    int count2=ropeCut(n-b,a,b,c);
    int count3=ropeCut(n-c,a,b,c);
    int res=max(count1,count2,count3);
    if(res==-1)
        return -1;
    return res+1;
}

int main(){
    cout<<ropeCut(23,12,14,11)<<endl;
    cout<<ropeCut(5,2,5,1)<<endl;
    cout<<ropeCut(9,2,2,2)<<endl;

    return 0;
}
