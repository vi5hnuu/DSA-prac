// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

/*
Input:
aaabbaaccd

Output: 
ad

Explanation: 
Remove (aa)abbaaccd =>abbaaccd
Remove a(bb)aaccd => aaaccd
Remove (aa)accd => accd
Remove a(cc)d => ad
*/

class Solution
{
    public:
    //Function to remove pair of duplicates from given string using Stack.
    string removePair(string str)
    {
        stack<char> stck;
        for(int i=0,len=str.length();i<len;i++){
            if(stck.empty())
                stck.push(str[i]);
            else if(stck.top()==str[i])
                stck.pop();
            else
                stck.push(str[i]);
        }
        string res;
        while(!stck.empty()){
            res=stck.top()+res;
            stck.pop();
        }
        return res;
    }
};

// { Driver Code Starts.

int main() {
    int t;
    cin>>t;
    
    while(t--)
    {
        string s;
        cin>>s;
        Solution obj;
        string ans = obj.removePair (s);
        if(ans=="")
            cout<<"Empty String"<<endl;
        else
            cout<<ans<<endl;
    }
    
	return 0;
}  // } Driver Code Ends