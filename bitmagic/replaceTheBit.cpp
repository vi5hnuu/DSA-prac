// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


/*
Given two numbers N and K, change the Kth bit from left of the number N to '0' if it is  '1', else return the number N itself.

Example 1:

Input:
N = 13, K = 2
Output: 9
Explanation: Binary representation of 13 is
1101. The 2nd bit from left is 1, we make
it 0 and result is 1001 = 9 (decimal).
*/

 // } Driver Code Ends

class Solution
{
  public:
    int replaceBit (int n, int k)
    {
        int howManyBitsAreThere=log2(n)+1;
        int shiftFromRight=howManyBitsAreThere-k;
        return (n & (1<<shiftFromRight))>0 ? n^(1<<shiftFromRight):n ;
    }
};

// { Driver Code Starts.
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k; cin >> n >> k;
        Solution ob;
        cout <<ob.replaceBit (n, k) << endl;
    }
    return 0;
}

  // } Driver Code Ends
