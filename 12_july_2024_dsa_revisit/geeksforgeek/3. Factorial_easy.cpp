/*
Given a positive integer, n. Find the factorial of n.

Examples :

Input: n = 5
Output: 120
Explanation: 1 x 2 x 3 x 4 x 5 = 120
Input: n = 4
Output: 24
Explanation: 1 x 2 x 3 x 4 = 24
Constraints:
0 <= n <= 12
*/

// using recursion
class Solution {
  public:
    int factorial(int n) {
        if(n<0) throw "invalid n, n should be >=0";
        if(n<=1) return 1;
        return n*factorial(n-1);
    }
};


// using loop
class Solution {
  public:
    int factorial(int n) {
        if(n<0) throw "invalid n, n should be >=0";
        if(n<=1) return 1;
        
        int fact=1;
        for(int i=n;i>=1;i--){
            fact*=i;
        }
        
        return fact;
    }
};