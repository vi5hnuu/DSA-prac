// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
class Solution{
    private:
    int kadMaxSum(int arr[],int n){
    int res = arr[0];
	int maxEnding = arr[0];

	for(int i = 1; i < n; i++){
		maxEnding = max(maxEnding + arr[i], arr[i]);
		res = max(maxEnding, res);
	}
	return res;
    }

    public:
    // arr: input array
    // num: size of array
    //Function to find maximum circular subarray sum.
    int circularSubarraySum(int arr[], int n){
        int normalMaxSum=kadMaxSum(arr,n);
        if(normalMaxSum<0){
            return normalMaxSum;
        }

        //array can be all positive(no possible of max circular sum) or (pos+neg have possible of max circular sum)
        int totalSum=0;
        for(int i=0;i<n;i++){
            totalSum+=arr[i];
            arr[i]=-arr[i];
        }
        int minSum=kadMaxSum(arr,n);
        if(totalSum+minSum==0){//means array was all positive
            return normalMaxSum;
        }
        else{//contained both pos and neg
            return max(normalMaxSum,totalSum+minSum);//minSum is negative
        }
    }
};

// { Driver Code Starts.

int main()
 {
	int T;

	//testcases
	cin>> T;

	while (T--)
	{
	    int num;

	    //size of array
	    cin>>num;
	    int arr[num];

	    //inserting elements
	    for(int i = 0; i<num; i++)
	        cin>>arr[i];

	    Solution ob;
	    //calling function
	    cout << ob.circularSubarraySum(arr, num) << endl;

	}

	return 0;
}  // } Driver Code Ends


//understanding
/*
if normal sum is neg than this is maxSum
else if array is positive then if we again find min sum then totalSum+minsum==0 means array was all positive and normal sum was maxSum
else
there is possibility that the min sum is between start and end index if this is case we can subtract(add) minsum from total Sum of array
and can get max circular sum..

but if min sum(sum of negatives) lies circularly then our normalMaxSum was the only maxSum..
*/
