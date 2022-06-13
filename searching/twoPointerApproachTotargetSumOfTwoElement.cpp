#include<iostream>
#include<algorithm>
using namespace std;

bool targetSum2ele(int arr[],int n,int x){
    //arr++;//array is received as normal pointer not as array
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]+arr[j]==x){
                cout<<"i : "<<i<<" j: "<<j<<endl;
                return true;
            }
        }
    }
    return false;
}

//two pointer approach for sorted array
bool targetSum2ele_twopointer(int arr[],int n,int x){
    //arr++;//array is received as normal pointer not as array
    int p=0;
    int q=n-1;
    while(p<q){
        if(arr[p]+arr[q]==x){
            cout<<"i : "<<p<<" j: "<<q<<endl;
                return true;
        }
        else if(arr[p]+arr[q]>x){
            q--;
        }
        else{
            p++;
        }
    }
    return false;
}

int main(){
    //int arr[]={3,5,9,2,8,10,11};
    ////////////for two pointer////////////////
    int arr[]={3,5,9,2,8,10,11};
    sort(arr,arr+7);
    //////////////////////////////
    cout<<(targetSum2ele(arr,7,17)==1 ? "Yes" : "No")<<endl;
    cout<<(targetSum2ele_twopointer(arr,7,17)==1 ? "Yes" : "No")<<endl;
}
