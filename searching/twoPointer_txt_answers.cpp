#include<iostream>
using namespace std;

//if array has distinct elements

int tripletSum_count(int arr[],int n,int x){
    int count_=0;
    for(int i=0;i<n-2;i++)
    for(int j=i+1;j<n-1;j++)
    for(int k=j+1;k<n;k++)
    if(arr[i]+arr[j]+arr[k]==x){
           count_+=1;
           cout<<"i : "<<i<<" j : "<<j<<" k : "<<k<<endl;
           break;
    }
    return count_;
}

//for unsorted we first sort (nlogn) then apply this method (n^2)
int tripletSum_threepointer_count(int arr[],int n,int x){
    int count=0;
    for(int i=0;i<n-2;i++){
        int p=i+1;
        int q=n-1;
        int targetSum=x-arr[i];
        while(p<q){
            if(arr[p]+arr[q]==targetSum){
                cout<<"i : "<<i<<" j : "<<p<<" k : "<<q<<endl;
                count++;
                break;
            }
            else if(arr[p]+arr[q]>targetSum){
                q--;
            }
            else{
                p++;
            }
        }
    }
    return count;
}

int main(){
    int arr[]={2,3,4,8,9,20,40};
    cout<<tripletSum_count(arr,7,32)<<endl;
    cout<<tripletSum_threepointer_count(arr,7,32)<<endl;

    return 0;
}
