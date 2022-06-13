#include<iostream>
using namespace std;


//seperate positive one left side and negative on other side
void segregateNegPosOneSide(int a[],int n){
    int start=0;
    int end=n-1;
    while(start<end){
        while(a[start]>=0){start++;}
        while(a[end]<0){end--;}
        if(start<end)
        swap(a[start],a[end]);
    }
}

int main(){
    int a[]={1,2,3,4,5,-5,-6,2,3};
    segregateNegPosOneSide(a,9);
    for(int i=0;i<9;i++)
        cout<<a[i]<<" ";

    return 0;
}
