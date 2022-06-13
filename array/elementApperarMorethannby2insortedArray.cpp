#include<iostream>
using namespace std;


/*
Time Complexity: O(n)

Auxiliary Space: O(1)
*/
//to see if target is there >n/2 times in sorted array
/*
int findmajority_sorted(int a[],int n,int target){//voting //for sorted array only
    int last_index= n& 1 ? (n/2+1) : n/2;
    for(int i=0;i<last_index;i++){
        if(a[i]==target && a[i+n/2]==target)
            return 1;
    }
    return 0;
}
*/

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
/*
Time Complexity: O(Logn)

Auxiliary Space: O(1)
*/

int _binarySearch(int a[],int low,int high,int x);

bool findmajority_sorted(int a[],int n,int x){
    int i=_binarySearch(a,0,n-1,x);

    if(i==-1)
        return false;

    if(((i+n/2)<=(n-1)) && a[i+n/2]==x)
        return true;
    else
        return false;
}

int _binarySearch(int a[],int low,int high,int x){
    if(high>=low){
        int mid=(low+high)/2;
        if((a[mid]==x) && (mid==0 || x>a[mid-1])){
            return mid;
        }
        else if(x>a[mid])
            return _binarySearch(a,(mid+1),high,x);
        else
            return _binarySearch(a,low,mid-1,x);
    }
    return -1;
}

int main(){
     int arr[] ={1, 2, 3, 4, 4, 4, 4};
    int n = sizeof(arr)/sizeof(arr[0]);
    int x = 4;
    if (findmajority_sorted(arr, n, x))
        cout <<x <<" appears more than "<<n/2 << " times in arr[]"<< endl;
    else
        cout <<x <<" does not appear more than" << n/2 <<"  times in arr[]" << endl;

return 0;
}
