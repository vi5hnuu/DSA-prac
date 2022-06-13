#include<iostream>
using namespace std;


void arrange(long long arr[], int n) {//wrong
       if(n>0)
       {
           int temp=arr[arr[n-1]];
           arrange(arr,n-1);
           arr[n-1]=temp;
       }

}

void arrange(long long arr[], int n) {//correct


       for(int i=0; i<n; i++)
           arr[i]+= (arr[arr[i]]%n)*n;

       for(int i=0; i<n; i++)
           arr[i]/=n;

   }

int main(){
    long long int a[]={1,2,3,4,5,6,7,8,9};
    arrange(a,9);
    for(int i=0;i<9;i++){
        cout<<a[i]<<" ";
    }
}
