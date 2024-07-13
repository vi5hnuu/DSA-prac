Given two binary strings a and b, return their sum as a binary string.

 

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
 

Constraints:

1 <= a.length, b.length <= 104
a and b consist only of '0' or '1' characters.
Each string does not contain leading zeros except for the zero itself.


class Solution {
public:
    string addBinary(string a, string b) {
        int l1=a.length();
        int l2=b.length();
        int len=max(l1,l2);

        string sum="";
        int carry=0;
        for(int i=0;i<len;i++){
            int fromEndIdxL1=l1-i-1,fromEndIdxL2=l2-i-1;

            int sm= ((fromEndIdxL1)>=0 ? a[fromEndIdxL1]-'0' : 0)+
            ((fromEndIdxL2)>=0 ? b[fromEndIdxL2]-'0' : 0)+carry;
            carry=sm/2;
            sm=sm%2;
            sum=to_string(sm)+sum;
        }
        if(carry){
            sum=to_string(carry)+sum;
        }

        return sum;
    }
};