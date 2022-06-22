// { Driver Code Starts
#include <bits/stdc++.h>

using namespace std;

/*
Input:
N = 2
Output:
move disk 1 from rod 1 to rod 2
move disk 2 from rod 1 to rod 3
move disk 1 from rod 2 to rod 3
3
Explanation: For N=2 , steps will be
as follows in the example and total
3 steps will be taken.
*/

class Solution{
    public:
    // You need to complete this function

    // avoid space at the starting of the string in "move disk....."
    long long toh(int N, int from, int to, int aux) {
        if(N==1){
        cout<<"move disk "<<N<<" from rod "<<from<<" to rod "<<to<<endl;
        return 1;
        }
            
        int x=1+toh(N-1,from,aux,to);
        cout<<"move disk "<<N<<" from rod "<<from<<" to rod "<<to<<endl;
        int y=1+toh(N-1,aux,to,from);
        return x+y-1;
    }

};

// { Driver Code Starts.

int main() {

    int T;
    cin >> T;//testcases
    while (T--) {
        
        int N;
        cin >> N;//taking input N
        
        //calling toh() function
        Solution ob;
        
        cout << ob.toh(N, 1, 3, 2) << endl;
    }
    return 0;
}


//Position this line where user code will be pasted.  // } Driver Code Ends