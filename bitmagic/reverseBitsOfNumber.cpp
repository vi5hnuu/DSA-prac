// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

 // } Driver Code Ends
class Solution {
  public:
    long long reversedBits(long long X) {
        long long reverseNum=0;//32 bits //long long is 4 bytes
        int i=31;
        while(X!=0){//take last bit of x and set it on reverse num from end(from 31st bit)
            if(X&1)
                reverseNum=reverseNum | ((X&1)<<i);
            i--;
            X=X>>1;
        }
        return reverseNum;
    }
};

// { Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        long long X;

        cin>>X;

        Solution ob;
        cout << ob.reversedBits(X) << endl;
    }
    return 0;
}  // } Driver Code Ends
