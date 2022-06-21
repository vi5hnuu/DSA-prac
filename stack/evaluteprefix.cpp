#include<bits/stdc++.h>
using namespace std;

int precVal(char a){
      switch(a){
          case '^':return 10;
          case '*':return 8;
          case '/':return 8;
          case '+':return 6;
          case '-':return 6;
      }
  }

class Eval{
  public:
  double operator()(double a,char op,double b){
    switch(op){
      case '+':return a+b;
      case '-':return a-b;
      case '*':return a*b;
      case '/':return a*1.0/b;
    }
  }
};

double infixEval(string input){
  Eval eval;
  int len=input.length();
  stack<double> stck;
  double res=0;
  for(int i=len-1;i>=0;i--){
    if(input[i]>='0' && input[i]<='9')
      stck.push(input[i]-'0');
    else{
        double first=stck.top();
        stck.pop();
        double second=stck.top();
        stck.pop(); 
        res=eval(first,input[i],second);
        stck.push(res);
      }
    }
  return stck.top();
}

int main(){
  //string s="+*253";
  string s="+/253";
  cout<<infixEval(s);

  return 0;
}