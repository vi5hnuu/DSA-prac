// { Driver Code Starts
//Initial Template for C++
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
//User function Template for C++

class Solution
{
    private:
    int checkCount(int pattern,int arr[],int n){
            int count=0;
        for(int i=0;i<n;i++){
            if((pattern & arr[i])==pattern)
            count++;
        }
        return count;
    }
    public:
    // Function for finding maximum AND value.
    int maxAND (int arr[], int N)
    {
        int res=0;
        for(int i=31;i>=0;i--){
            int count=checkCount(res|(1<<i),arr,N);

            if(count>=2)
                res|=(1<<i);
        }
        return res;
    }
};

// { Driver Code Starts.

// Driver function
int main()
{
    int t;
    cin>>t;//testcases
    while(t--)
    {
        int n;
        cin>>n;//input n
        int arr[n+5],i;

        //inserting elements
        for(i=0;i<n;i++)
        cin>>arr[i];
        Solution obj;
        //calling maxAND() function
        cout <<  obj.maxAND(arr,n)<<endl;
    }
    return 0;
}  // } Driver Code Ends
