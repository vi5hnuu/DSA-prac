#include<iostream>
#include<algorithm>
using namespace std;

/*
avg size n>=2
only one element repeat (any number of time)
all the element from 0 to max are present
therefor 0<=max(arr)<<n-2;
*/

int repeating_element0(int arr[],int n){//O(n^2),no change in original array
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(arr[i]==arr[j])
                return arr[i];
        }
    }
    return -1;
}
int repeating_element1(int arr[],int n){//O(nlogn),change in original array
    sort(arr,arr+n);
    for(int i=1;i<n;i++){
        if(arr[i]==arr[i-1])
            return arr[i];
    }
    return -1;
}

int repeating_element2(int arr[],int n){//do not change origninal array
    //O(n),S(n)
    bool ispresent[n-1]={false};
    for(int i=0;i<n-1;i++){
        if(!ispresent[arr[i]]){
                ispresent[arr[i]]=true;
        }
        else
            return arr[i];
    }
    return -1;
}

int repeating_element3(int arr[],int n){//do not change origninal array
    for(int i=0;i<n-1;i++){
        if(arr[arr[i]]<0){
            ///////////////////////////////
            //make neg pos before returning
            for(int i=0;i<n-1;i++)
                if(arr[i]<0)
                    arr[i]=-arr[i];
            ///////////////////////////////
            return arr[i];
        }
        else
            arr[arr[i]]=-arr[arr[i]];
    }
    return -1;
}

int repeating_element4(int arr[],int n){//do not change origninal array
    //only for [1,n] no zero in arry..it work in cycle

    int slow=arr[0],fast=arr[0];
    do{
        slow=arr[slow];
        fast=arr[arr[fast]];
    }while(slow!=fast);
    slow=arr[0];
    while(slow!=fast){
        slow=arr[slow];
        fast=arr[fast];
    }
    return slow;
}

int repeating_element5(int arr[],int n){//do not change origninal array
    //modified for array containing zero[as per ques the array always contain zero]..it work in cycle

    int slow=arr[0]+1,fast=arr[0]+1;
    do{
        slow=arr[slow]+1;
        fast=arr[arr[fast]+1]+1;
    }while(slow!=fast);
    slow=arr[0]+1;
    while(slow!=fast){
        slow=arr[slow]+1;
        fast=arr[fast]+1;
    }
    return slow-1;
}
int main(){
    int arr[]={0,2,1,3,2,2};
    //int arr[]={4,2,1,3,2,2};//no zero
    cout<<repeating_element5(arr,6)<<endl;

    return 0;
}
