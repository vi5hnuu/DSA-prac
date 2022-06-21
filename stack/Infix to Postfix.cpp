// { Driver Code Starts
// C++ implementation to convert infix expression to postfix
#include <bits/stdc++.h>
using namespace std;

//same prec cannot be on stasck
 // } Driver Code Ends
class Solution {
/*
  private:
  int precVal(char a){
      switch(a){
          case '(':return 100;
          case '^':return 10;
          case '*':return 8;
          case '/':return 8;
          case '+':return 6;
          case '-':return 6;
      }
  }
  public:
    // Function to convert an infix expression to a postfix expression.
    string infixToPostfix(string s) {
        stringstream ss;
        stack<char> res;
        for(int i=0,len=s.length();i<len;i++){
            if((s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z')){
                ss<<s[i];
            }
            else{
                if(s[i]==')'){
                    while(res.top()!='('){
                    ss<<res.top();
                    res.pop();
                }
                res.pop();
                }
                else{
                    if(res.empty() || precVal(res.top())<precVal(s[i])){
                        res.push(s[i]);
                    }else{
                        while((!res.empty() && res.top()!='(') && precVal(res.top())>=precVal(s[i])){
                            ss<<res.top();
                            res.pop();
                        }
                        res.push(s[i]);
                    }   
                }
            }
        }
        while(!res.empty()){
            ss<<res.top();
            res.pop();
        }
        return ss.str();
    }*/
    /////////////
    private:
  int precVal(char a){
      switch(a){
          case '(':return 0;
          case '^':return 10;
          case '*':return 8;
          case '/':return 8;
          case '+':return 6;
          case '-':return 6;
      }
  }
  public:
    // Function to convert an infix expression to a postfix expression.
    string infixToPostfix(string s) {
        stringstream ss;
        stack<char> res;
        for(int i=0,len=s.length();i<len;i++){
            if((s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z')){
                ss<<s[i];
            }
            else{
                if(s[i]=='(')
                    res.push('(');
                else if(s[i]==')'){
                    while(res.top()!='('){
                    ss<<res.top();
                    res.pop();
                }
                res.pop();
                }
                else{
                    if(res.empty() || precVal(res.top())<precVal(s[i])){
                        res.push(s[i]);
                    }else{
                        while((!res.empty()) && precVal(res.top())>=precVal(s[i])){
                            ss<<res.top();
                            res.pop();
                        }
                        res.push(s[i]);
                    }   
                }
            }
        }
        while(!res.empty()){
            ss<<res.top();
            res.pop();
        }
        return ss.str();
    }
};


// { Driver Code Starts.
// Driver program to test above functions
int main() {
    int t;
    cin >> t;
    cin.ignore(INT_MAX, '\n');
    while (t--) {
        string exp;
        cin >> exp;
        Solution ob;
        cout << ob.infixToPostfix(exp) << endl;
    }
    return 0;
}
  // } Driver Code Ends