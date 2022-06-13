#include<iostream>
using namespace std;

int findmajority_naive(int a[],int n){

    for(int i=0;i<n;i++){
            int count=0;
        for(int j=i+1;j<n;j++){
            if(a[i]==a[j])
                count++;
        }
        if(count>n/2)
            return i;
    }
    return -1;
}


//can be efficiently done using binary search
//[if in majority mid must be that element only in sorted array(but this is not mandatory that ele at mid is majority but yes if there were majority that it must be at mid also)]
int findmajority(int a[],int n){//voting //for sorted and non sorted array
    int res=0,count=1;
    for(int i=1;i<n;i++){
        if(a[i]==a[res])
            count++;
        else
            count--;

        if(count==0){
            res=i;
            count=1;
        }
    }
    count=0;
    for(int i=0;i<n;i++){
        if(a[res]==a[i]){
            count++;
        }
    }
    if(count<=n/2)
        res=-1;

    return res;
}

int main(){
    //int a[]={8,7,6,8,6,6,6,6};
    int a[]={1, 2, 3, 3, 3, 3, 10};
    cout<<findmajority(a,7)<<endl;

    return 0;
}
