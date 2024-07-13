Given a string s, find the length of the longest 
substring
 without repeating characters.

 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.


//O(N*N)
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len=s.length();
        if(!len) return 0;
        int last_startrepeatingIndex=0; //just next index of repeating char(from start index)

        int maxNonRepLen=1;
        for(int i=0;i<len;i++){
            for(int j=i-1;j>=last_startrepeatingIndex;j--){
                if(s[i]==s[j]){
                    last_startrepeatingIndex=j+1;
                    maxNonRepLen=max(maxNonRepLen,i-j);
                    break;
                }else{
                    maxNonRepLen=max(maxNonRepLen,i-j+1);
                }
            }
        }
        return maxNonRepLen;
    }
};

//// O(N)
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len=s.length();
        if(!len) return 0;

        unordered_map<int,int> elIndex;//num -> index

        // eg if repeat at index [1,7] then repIndex=2
        int repIndex=0; 

        int maxNonRepLen=1;
        for(int i=0;i<len;i++){
            if(!elIndex.count(s[i]) || (elIndex.count(s[i]) && elIndex[s[i]]<repIndex)) {
                maxNonRepLen=max(maxNonRepLen,i-repIndex+1);
            }else{
                repIndex=elIndex[s[i]]+1;
                maxNonRepLen=max(maxNonRepLen,i-repIndex);
            }
            elIndex[s[i]]=i;
        }
        return maxNonRepLen;
    }
};