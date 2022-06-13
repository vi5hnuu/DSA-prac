#include<iostream>
using namespace std;


void k_string(string &str,int n,int k){
    if(n<1)
    cout<<str<<endl;
    else{
        for(int j=0;j<k;j++){
            str[n-1]='0'+j;
            k_string(str,n-1,k);
        }
    }
}

int main(){
    string str="****";
k_string(str,4,5);
}
