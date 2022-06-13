#include<iostream>
using namespace std;

void peakElement(int arr[],int n){//return any peak element[but lets print all of them]
    if(arr[1]<arr[0])
        cout<<arr[0]<<" ";
    for(int i=1;i<n-1;i++){
        if(arr[i-1]<arr[i] && arr[i+1]<arr[i]){
            cout<<arr[i]<<" ";
        }
    }
    if(arr[n-2]<arr[n-1])
        cout<<arr[n-1]<<" "<<endl;
}

//we use binary search here and the trick is if the element at mid is not peak then
//greater mid greater
//less mid greater
//greater mid less
//these three possible things can happen
//we got to left if left element in greater because we will surely find peak on left
//if right one is greater then we go to right because we surely find peak to right

//Note a array of 1 ,2 etc always contain a peak element and in thin ques we want to just print any one of peak element
int peakElement_binary(int arr[],int n){//return any peak element[but lets print all of them]
    int low=0;
    int high=n-1;
    while(low<=high){
        int mid=(low+high)/2;
        //when n==1 => mid==0==n-1
        if((mid==0 || arr[mid-1]<=arr[mid]) && (mid==n-1 || arr[mid+1]<=arr[mid])){
            return mid;
        }
        if(mid>0 && arr[mid-1]>=arr[mid])
            high=mid-1;
        else
            low=mid+1;
    }
    return -1;
}


int main(){
    int arr[]={5,10,20,15,7};
    peakElement(arr,5);
    cout<<endl<<arr[peakElement_binary(arr,5)];
    cout<<"\n***********************\n";
    int arrr[]={10,20,15,5,23,90};
    peakElement(arrr,6);
    cout<<endl<<arrr[peakElement_binary(arrr,6)];
    cout<<"\n***********************\n";
    int arrrr[]={80,70,90};
    peakElement(arrrr,3);
    cout<<endl<<arrrr[peakElement_binary(arrrr,3)];
    cout<<"\n***********************\n";
    int arrrrr[]={80,70};
    peakElement(arrrrr,2);
    cout<<endl<<arrrrr[peakElement_binary(arrrrr,2)];
    cout<<"\n***********************\n";
    int arrrrrr[]={80};
    peakElement(arrrrrr,1);
    cout<<endl<<arrrrrr[peakElement_binary(arrrrrr,1)];

    return 0;
}
