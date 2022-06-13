#include<iostream>
using namespace std;

//find if there is pair a^2+b^2=c^2
bool findIfaSqbSqEQCSq(int arr[],int n){
    for(int i=0;i<n-2;i++){
        int p=i+1;
        int q=n-1;
        int target=arr[i]*arr[i];//target= a^2,p=b,q=c
        while(p<q){
            if(arr[p]*arr[p]+target==arr[q]*arr[q]){
                    cout<<"One of the pair is => i : "<<i<<" j : "<<p<<" k : "<<q<<endl;
                    return true;
            }
            else if(arr[p]*arr[p]+target<arr[q]*arr[q]){
                q--;
            }
            else{
                p++;
            }
        }
    }
    return false;
}

int main(){
    int arr[]={1,2,3,4,5,6,7,8,9,10};
    cout<<findIfaSqbSqEQCSq(arr,10)<<endl;

    return 0;
}
