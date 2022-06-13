#include<iostream>
using namespace std;

/*
 Non-type parameters must be const, so they cannot be modified.
*/

template<class T,int max>
T arrmin(T arr[],int n){
    int m=max;
    for(int i=0;i<n;i++){
        if(arr[i]<max)
         m=arr[i];
    }
    return m;
}

int main(){
    int arr[]={10,20,15,12};
    int n1=sizeof(arr)/sizeof(arr[0]);
    int max=1000;
    cout<<arrmin<int,1000>(arr,n1)<<endl;
//    cout<<arrmin<int,max>(arr,n1)<<endl;

    return 0;
}
