#include<iostream>
#include<math.h>
using namespace std;


void printPowerSet(string str){
    int n=str.length();
    int powSetSize=pow(2,n);
    for(int counter=0;counter<powSetSize;counter++){
        for(int j=0;j<n;j++){
            if((counter & (1<<j))!=0){
                cout<<str[j];
            }
        }
        cout<<endl;
    }
}

int main(){
printPowerSet("vishnu");
printPowerSet("abc");

return 0;
}
