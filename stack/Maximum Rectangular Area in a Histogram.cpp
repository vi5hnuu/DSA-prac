// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
class Solution
{
    public:
    //Function to find largest rectangular area possible in a given histogram.
    //TLE O(N^2)
    /*
    long long getMaxArea(long long arr[], int n)
    {
        long long maxA=0;
        for(int i=0;i<n;i++){
            int area=arr[i];
            for(int j=i+1;j<n;j++){
                if(arr[j]>=arr[i])
                    area+=arr[i];
                else
                    break;
            }
            for(int j=i-1;j>=0;j--){
                if(arr[j]>=arr[i])
                    area+=arr[i];
                else
                    break;
            }
            maxA=maxA>area ? maxA : area;
        }
        return maxA;
    }
    */
    
    //////////////////////////////////////////
    /*
    vector<int> prevSmallerEq(long long arr[],int n){
        stack<int> indexes;
        vector<int> res(n,-1);
        for(int i=0;i<n;i++){
            if(indexes.empty()){}
            else{
                while(!indexes.empty() && arr[indexes.top()]>=arr[i])
                    indexes.pop();
                if(indexes.empty()){}
                else
                res[i]=indexes.top();
            }
            indexes.push(i);
        }
        return res;
    }
    vector<int> nextSmallerEq(long long arr[],int n){
        stack<int> indexes;
        vector<int> res(n,n);
        for(int i=n-1;i>=0;i--){
            if(indexes.empty()){}
            else{
                while(!indexes.empty() && arr[indexes.top()]>=arr[i])
                    indexes.pop();
                if(indexes.empty()){}
                else
                res[i]=indexes.top();
            }
            indexes.push(i);
        }
        return res;
    }
    void print(const vector<int> &res){
        int len=res.size();
        for(int i=0;i<len;i++)
        cout<<res[i]<<" ";
        cout<<endl;
    }
    long long getMaxArea(long long arr[], int n)
    {
        long long maxA=0;
        vector<int> preS=prevSmallerEq(arr,n);
        vector<int> nextS=nextSmallerEq(arr,n);
        //print(preS);
        //print(nextS);
        for(int i=0;i<n;i++){
             long long cur=arr[i];
             cur+=(i-preS[i]-1)*arr[i];
             cur+=(nextS[i]-i-1)*arr[i];
             maxA=maxA>cur?maxA:cur;
        }
        return maxA;
    }
    */
};


// { Driver Code Starts.

int main()
 {
    long long t;

    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        
        long long arr[n];
        for(int i=0;i<n;i++)
            cin>>arr[i];
        Solution ob;
        cout<<ob.getMaxArea(arr, n)<<endl;
    
    }
	return 0;
}
  // } Driver Code Ends