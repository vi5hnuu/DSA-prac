// { Driver Code Starts
// C++ program to evaluate value of a postfix expression

#include <bits/stdc++.h>
using namespace std;


 // } Driver Code Ends
class Solution
{
    private:
    class Eval{
        public:
        int operator()(int a,char c,int b){
            switch(c){
                case '*':return a*b;
                case '/':return a/b;
                case '+':return a+b;
                case '-':return a-b;
            }
        }
    };
    public:
    //Function to evaluate a postfix expression.
    int evaluatePostfix(string S)
    {
        stack<int> res;
        Eval eval;
        for(int i=0,len=S.length();i<len;i++){
            if(S[i]>='0' && S[i]<='9')
                res.push(S[i]-'0');
            else{
                int a=res.top();
                res.pop();
                int b=res.top();
                res.pop();
                int result=eval(b,S[i],a);
                res.push(result);
            }
        }
        int data=res.top();
        res.pop();
        return data;
    }
};

// { Driver Code Starts.

// Driver program to test above functions
int main()
{
    int t;
    cin>>t;
    cin.ignore(INT_MAX, '\n');
    while(t--)
    {
        string S;
        cin>>S;
        Solution obj;
    
    cout<<obj.evaluatePostfix(S)<<endl;
    }
    return 0;
}
  // } Driver Code Ends