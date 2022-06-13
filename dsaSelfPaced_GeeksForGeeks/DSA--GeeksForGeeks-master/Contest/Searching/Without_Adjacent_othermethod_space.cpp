#include<iostream>
using namespace std;

int findMaxSumWithoutAdj(vector<int> arr,int N){
    int incl=arr[0];
    int excl=0;
    int excl_new;
    int i=0;
    for(int i=1;i<n;i++){
        excl_new=max(incl,excl);
        incl=excl+arr[i];
        excl=excl_new;
    }
    return max(excl,incl);
}
