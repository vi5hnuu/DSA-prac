// { Driver Code Starts
// C++ program to rearrange an array in minimum
// maximum form
#include <bits/stdc++.h>
using namespace std;

/*
Given a sorted array of positive integers. Your task is to rearrange  the array elements alternatively i.e first element should be max value, second should be min value, third should be second max, fourth should be second min and so on.
Note: Modify the original array itself.
*/

//works when only array is sorted in increasing order...and it take o(n^2)
class Solution{
    private:
    void reverse(long long arr[],int n,int low,int high){
        while(low<high){
            swap(arr[low],arr[high]);
            low++;
            high--;
        }
    }
    public:
    // This function wants you to modify the given input
    // array and no need to return anything
    // arr: input array
    // n: size of array
    //Function to rearrange  the array elements alternately.
    void rearrange(long long *arr, int n)
    {
        //give array is sorted in increasing order
        int k=0;
        while(k<n){
            reverse(arr,n,n-1,n-1);//no use..just for clarrification
            reverse(arr,n,k,n-2);
            reverse(arr,n,k,n-1);
            k+=2;
        }
    }

};

// { Driver Code Starts.

// Driver program to test above function
int main()
{
    int t;

    //testcases
    cin >> t;

    while(t--){

        //size of array
        int n;
        cin >> n;

        long long arr[n];

        //adding elements to the array
        for(int i = 0;i<n;i++){
            cin >> arr[i];
        }

        Solution ob;

        //calling rearrange() function
        ob.rearrange(arr, n);

        //printing the elements
        for (int i = 0; i < n; i++)
		    cout << arr[i] << " ";

		cout << endl;
    }
	return 0;
}
  // } Driver Code Ends
