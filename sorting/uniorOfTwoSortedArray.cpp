#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void unionOfTwoSorted_naive(int arr1[],int n,int arr2[],int m){//O((m+n)log(m+n))
    int i=0,j=0;
    vector<int> res(n+m);
    //res.assign(arr1,arr1+n);
    for(int i=0;i<n;i++){
        res[i]=arr1[i];
    }
    for(int i=0;i<m;i++){
        res[n+i]=arr2[i];
    }
    sort(res.begin(),res.end());
    for(int i=0;i<m+n;i++){
        if(i==0 || res[i]!=res[i-1])
            cout<<res[i]<<" ";
    }
}

vector<int> unionOfTwoSorted0(int arr1[],int n,int arr2[],int m){//O(m+n)
    int i=0,j=0;
    vector<int> res;
    int lastAdded=INT_MAX;
    while(i<n && j<m){
        if(arr1[i]==arr2[j]){
            if(lastAdded!=arr1[i]){
                res.push_back(arr1[i]);
                lastAdded=arr1[i];
            }
            i++;
            j++;
        }
        else if(arr1[i]<arr2[j]){
            if(arr1[i]!=lastAdded){
                res.push_back(arr1[i]);
                lastAdded=arr1[i];
            }
            i++;
        }
        else{
            if(arr2[j]!=lastAdded){
                res.push_back(arr2[j]);
                lastAdded=arr2[j];
            }
            j++;
        }
    }
    while(i<n){
        if(lastAdded!=arr1[i]){
            res.push_back(arr1[i]);
            lastAdded=arr1[i];
        }
        i++;
    }
    while(j<m){
        if(lastAdded!=arr2[j]){
            res.push_back(arr2[j]);
            lastAdded=arr2[j];
        }
        j++;
    }
    return res;
}

vector<int> unionOfTwoSorted(int arr1[],int n,int arr2[],int m){//O(m+n)
    int i=0,j=0;
    vector<int> res;
    while(i<n && j<m){
        if(i>0 && arr1[i]==arr1[i-1]){
            i++;continue;
        }
        if(j>0 && arr2[j]==arr2[j-1]){
            j++;continue;
        }
        ////////////////////////////
        if(arr1[i]==arr2[j]){
                res.push_back(arr1[i]);
            i++;
            j++;
        }
        else if(arr1[i]<arr2[j]){
            res.push_back(arr1[i]);
            i++;
        }
        else{
            res.push_back(arr2[j]);
            j++;
        }
    }
    while(i<n){
        if(i>0 && arr1[i]==arr1[i-1]){
            i++;continue;
        }
        res.push_back(arr1[i]);
        i++;
    }
    while(j<m){
        if(j>0 && arr2[j]==arr2[j-1]){
            j++;continue;
        }
        res.push_back(arr2[j]);
        j++;
    }
    return res;
}

int main(){

    /*
    int arr1[]={3,5,10,10,10,15,20};
    int arr2[]={5,10,10,15,30};

    for(int x:unionOfTwoSorted(arr1,7,arr2,5)){
        cout<<x<<" ";
    }
    */

    /*
    int arr1[]={3,5,8};
    int arr2[]={2,8,9,10,15};

    for(int x:unionOfTwoSorted(arr1,3,arr2,5)){
        cout<<x<<" ";
    }
    */

    int arr1[]={4,4,5,5,6,6};
    int arr2[]={4,4};

    for(int x:unionOfTwoSorted(arr1,6,arr2,2)){
        cout<<x<<" ";
    }
    cout<<endl;
    unionOfTwoSorted_naive(arr1,6,arr2,2);
    return 0;
}
