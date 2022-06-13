// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

/*
Given a list A having N positive elements. The task to create another list such as ith element is XOR of all elements of  A except A[i].

Example 1:

Input:
A = [2, 1, 5, 9]
Output:
13 14 10 6
Explanation:
At first position 1^5^9 = 13
At second position 2^5^9 = 14
At third position 2^1^9 = 10
At last position 2^1^5 = 6
*/

 // } Driver Code Ends
class Solution
{
public:
    vector<int> getXor(vector<int> A, int N)
    {
        int xorrOfAll=0;
        for(int i=0;i<N;i++){
            xorrOfAll^=A[i];
        }
        vector<int> res(A);
        for(int i=0;i<N;i++){
            res[i]=xorrOfAll^res[i];
        }
        return res;
    }
};

// { Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int N;
        cin >> N ;
        vector<int> A(N);

        for (int i = 0; i < N; i++)
        {
            cin >> A[i];
        }

        Solution ob;
        vector<int> B = ob.getXor(A, N);
        for(int i = 0 ; i < N ; i++)
        {
            cout << B[i] <<" ";
        }
        cout << endl;
    }
    return 0;
}  // } Driver Code Ends
