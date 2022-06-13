// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

/*
Given an array A[] of size N. The value of an array is denoted by the bit-wise XOR of all elements it contains. Find the bit-wise XOR of the values of all subarrays of A[].

Example 1:

Input: N = 3, A[] = {1,2,3}
Output: 2
Explanation:
xor[1] = 1,
xor[1, 2] = 3
xor[2, 3] = 1
xor[1, 2, 3] = 0
xor[2] = 2
xor[3] = 3
Result : 1 ^ 3 ^ 1 ^ 0 ^ 2 ^ 3 = 2
*/

 // } Driver Code Ends
class Solution {
  public:
    int gameOfXor(int N , int A[]) {
        if(N&1==0){
            return 0;
        }
        int ans=0;
        for(int i=0;i<N;i+=2){
            ans^=A[i];
        }
        return ans;
    }
};

// { Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int N;

        cin>>N;
        int A[N];
        for(int i=0 ; i<N ; i++)
            cin>>A[i];

        Solution ob;
        cout << ob.gameOfXor(N,A) << endl;
    }
    return 0;
}  // } Driver Code Ends
