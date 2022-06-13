#include<iostream>
using namespace std;

int findOddOccuringOne_naive(int input[],int n){

    for(int i=0;i<n;i++){
            int count=0;
    for(int j=0;j<n;j++){
        if(input[i]==input[j])
            count++;

        }
        if(count & 1)
            return input[i];
    }
}

int findOddOccuringOne(int input[],int n){
    int res=0;
    for(int i=0;i<n;i++){
        res^=input[i];
    }
    return res;
}

int main(){
    int input[]={4,3,4,4,4,5,5};
    cout<<findOddOccuringOne_naive(input,7)<<endl;
}
