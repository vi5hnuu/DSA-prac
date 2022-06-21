#include<bits/stdc++.h>
using namespace std;

//same prec can be on stack
int precVal(char a){
      switch(a){
          case ')':return 0;
          case '^':return 10;
          case '*':return 8;
          case '/':return 8;
          case '+':return 6;
          case '-':return 6;
      }
  }

string infixToPrefix(string input){
  int len=input.length();
  stack<char> stck;
  string res="";
  for(int i=len-1;i>=0;i--){
    if((input[i]>='A' && input[i]<='Z') || (input[i]>='a' && input[i]<='z') || (input[i]>='0' && input[i]<='9'))
      res=input[i]+res;
    else{
      if(stck.empty() || input[i]==')')
        stck.push(input[i]);
      else if(input[i]=='('){
        while(stck.top()!=')'){
          res=stck.top()+res;
          stck.pop();
        }
        stck.pop();
      }
      else{
        if(precVal(stck.top())<=precVal(input[i]))
          stck.push(input[i]);
        else{
          while(!stck.empty() && precVal(stck.top())>precVal(input[i])){
            res=stck.top()+res;
            stck.pop();
          }
          stck.push(input[i]);
        }
      }
    }
  }
  while(!stck.empty()){
    res=stck.top()+res;
    stck.pop();
  }
 
  return res;
}

int main(){
  //string s="2+3*5+8";
  //string s="2+3*(5+8)";
  //string s="2+(3*5)+8";
  //string s="X+Y*Z+X";
  //string s="X+Y*Z";
  string s="x+y/z-w*u";
  cout<<infixToPrefix(s);
}