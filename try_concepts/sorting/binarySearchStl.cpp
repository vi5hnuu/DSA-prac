#include<algorithm>
#include<iostream>
using namespace std;

void show(int a[],int arraySize){
    for(int i=0;i<arraySize;i++){
        cout<<a[i]<<", ";
    }
}

int main(){
    int a[]={1,5,8,9,6,7,3,4,2,0};
    int asize=sizeof(a)/sizeof(a[0]);
    cout<<"\nThe array is : ";show(a,asize);

    cout<<"\n\nLets's say we want to search for";
    cout<<"\n2 in the array so, we first sort the array";
    sort(a,a+asize);
    cout<<"\nThe array after sorting is : ";
    show(a,asize);
    cout<<"\nNow, we do the binary search\n";
    if(binary_search(a,a+asize,2))
        cout<<"Element found in the array";
    else
        cout<<"Elemet not found in the array";

    cout<<"\nNow, say we want to search 10\n";
    if(binary_search(a,a+asize,10))
        cout<<"Element foun in they array";
    else
        cout<<"Element not found in the array";

        return 0;
}
