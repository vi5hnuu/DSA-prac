#include<iostream>
using namespace std;

/*
int amountOfWaterHold(int a[],int n){
    int res=0;
    for(int i=1;i<n-1;i++){
        int lmax=a[i];
        for(int j=0;j<i;j++){
            lmax=max(lmax,a[j]);
        }

        int rmax=a[i];
        for(int j=i+1;j<n;j++){
            lmax=max(rmax,a[j]);
        }
        res+=min(lmax,rmax)-a[i];
    }
    return res;
}
*/
int amountOfWaterHold(int a[],int n){
    int res=0;
    int lmax[n],rmax[n];
    lmax[0]=a[0];
    rmax[n-1]=a[n-1];
    for(int i=1;i<n-1;i++){
        lmax[i]=max(lmax[i-1],a[i]);
    }
     for(int i=n-2;i>=0;i--){
        rmax[i]=max(rmax[i+1],a[i]);
    }
    for(int i=1;i<n-1;i++){
        res+=min(lmax[i],rmax[i])-a[i];
    }
    return res;
}

//for big values
 long long trappingWater(int arr[], int n){
        vector<int> lmax(n,0);
        vector<int> rmax(n,0);
        lmax[0]=arr[0];
        rmax[n-1]=arr[n-1];
        for(int i=1;i<n;i++){
            lmax[i]=max(lmax[i-1],arr[i]);
            rmax[n-1-i]=max(rmax[n-i],arr[n-1-i]);
        }

        long long maxWater=0;
        for(int i=1;i<n-1;i++){
            maxWater+=(min(lmax[i],rmax[i])-arr[i]);
        }
        return maxWater;
    }


int main(){
    int arr[]={5,0,6,2,3};
    //lmax={5,5,6,6,6}
    //lmax={6,6,6,3,3}
    cout<<amountOfWaterHold(arr,5)<<endl;

    return 0;
}
