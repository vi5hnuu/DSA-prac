Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
 

Example 1:

Input: s = "()"
Output: true
Example 2:

Input: s = "()[]{}"
Output: true
Example 3:

Input: s = "(]"
Output: false
 

Constraints:

1 <= s.length <= 104
s consists of parentheses only '()[]{}'.


class Solution {
public:
    bool isValid(string s) {
        stack<char> stck;

        for(int i=0,sz=s.length();i<sz;i++){
            if(stck.empty() || ((s[i]-stck.top())!=1 && (s[i]-stck.top())!=2)) stck.push(s[i]);
            else stck.pop();
        }
        return stck.empty();
    }
};