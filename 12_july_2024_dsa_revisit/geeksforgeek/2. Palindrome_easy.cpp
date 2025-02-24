/*
You are given an integer n. Your task is to determine whether it is a palindrome.

A number is considered a palindrome if it reads the same backward as forward, like the string examples "MADAM" or "MOM".

Examples:

Input: n = 555
Output: true
Explanation: The number 555 reads the same backward as forward, so it is a palindrome.
Input: n = 123
Output: false
Explanation: The number 123 reads differently backward (321), so it is not a palindrome.
Input: n = 1221
Output: true
Constraints:
1 <= n <= 109
*/

// Solution 1 using int only
class Solution {
  public:
    bool isPalindrome(int n) {
        int n_dash=n;
        int reverse=0;
        while(n){
            int lastDigit=n%10;
            n/=10;
            reverse=reverse*10+lastDigit;
        }
        return n_dash==reverse;
    }
};


// Solution 2 by converting num to string
class Solution {
  public:
    bool isPalindrome(int n) {
        string n_dash=to_string(n);
        for(int i=0,sz=n_dash.size();i<sz/2;i++){
            if(n_dash[i]!=n_dash[sz-1-i]) return false;
        }
        return true;
    }
};