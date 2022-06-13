#include<iostream>
using namespace std;

void printLeaders_naive(int a[],int n){
    for(int i=0;i<n;i++){
            int ele=a[i];
            bool foundToPrint=true;
        for(int j=i+1;j<n;j++){
            if(a[j]>=ele){
                    foundToPrint=false;
                break;
            }
        }
        if(foundToPrint)
            cout<<ele<<" ";
    }
}
/////////////////////////
void printLeaders(int a[],int n){
    int cur_leader=a[n-1];
    cout<<cur_leader<<" ";
    for(int i=n-2;i>=0;i--){
        if(a[i]>cur_leader){
            cout<<a[i]<<" ";
            cur_leader=a[i];
        }
    }
    cout<<endl;
}


int main(){
    int a[]={7,10,4,10,6,5,2};
    printLeaders(a,7);

    return 0;
}
