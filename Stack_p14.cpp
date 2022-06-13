#include<iostream>
#include<stack>
#include<random>
#include<time.h>
using namespace std;

int main(){
    int a[20]={0};
    int top1=-1;
    int top2=20;

    srand(time(0));
    for(int i=1;i<=30;i++){
        if(top1+1==top2 || top1==top2+1){
            cout<<"stacks are full.\n";
            continue;
        }
        int z=rand()%2;
        if(z==0){
            a[++top1]=rand()%50;
        }
        else if(z==1){
            a[--top2]=rand()%50;
        }
    }
    cout<<"Stack 1 :\n";
    for(int i=top1;i>=0;i--)
        cout<<a[i]<<endl;

    cout<<"\nStack 2 :\n";
    for(int i=top2;i<20;i++)
        cout<<a[i]<<endl;
}
