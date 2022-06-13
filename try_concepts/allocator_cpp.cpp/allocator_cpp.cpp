#include<iostream>
#include<memory>
using namespace std;


int main(){
    allocator<int> myAllocator;

    int *arr=myAllocator.allocate(5);
    for(int i=0;i<5;i++){
        arr[i]=i*i;
    }
    for(int i=0;i<5;i++){
        cout<<arr[i]<<" ";
    }
    myAllocator.deallocate(arr,5);

    return 0;
}
