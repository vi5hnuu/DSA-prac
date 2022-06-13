#include<iostream>
using namespace std;
void arrange(long long arr[], int n) {//correct


       for(int i=0; i<n; i++)
           arr[i]+= (arr[arr[i]]%n)*n;

       for(int i=0; i<n; i++)
           arr[i]/=n;

   }

int main(){
    int a[]={4,0,2,1,3};
    arrangeAlternate(a,5);
    for(int i=0;i<5;i++){
        cout<<a[i]<<" ";
    }

    return 0;
}
