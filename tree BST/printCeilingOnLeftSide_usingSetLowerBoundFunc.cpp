#include<iostream>
#include<set>
using namespace std;


void printCeiling_naive(int arr[],int n){//O(N^2)
    cout<<-1<<" ";
    for(int i=1;i<n;i++){
        int diff=INT_MAX;
        for(int j=0;j<i;j++){
            if(arr[j]>=arr[i])
                diff=min(diff,arr[j]-arr[i]);
        }
        if(diff==INT_MAX)
        cout<<-1<<" ";
        else
        cout<<(diff+arr[i])<<" ";
    }
}
void printCeiling(int arr[],int n){//O(N^2)
    cout<<-1<<" ";
    set<int> s;
    s.insert(arr[0]);
    for(int i=1;i<n;i++){
        auto lb=s.lower_bound(arr[i]);
        if(lb!=s.end()){
            cout<<*lb<<" ";
        }
        else
            cout<<-1<<" ";
        s.insert(arr[i]);
    }
}

int main(){
    int arr[]={2,8,30,15,25,12};
    printCeiling(arr,6);

    return 0;
}
