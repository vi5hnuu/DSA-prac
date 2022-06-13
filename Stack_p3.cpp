#include<iostream>
#include<stack>
using namespace std;

//enum op{'+'=12,'-'=12,'*'=13,'/'=13,'%'=13};

int inPrec(char input)
{
    switch (input) {
    case '+':
    case '-':
        return 2;
    case '*':
    case '%':
    case '/':
        return 4;
    }
}
int isOperator(char input)
{
    switch (input) {
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 1;
    case '%':
        return 1;
    case '/':
        return 1;
    }
    return 0;
}

string infix_to_postfix(string &str){
    stack<char> s;
    string postfix="";
    for(int i=0;i<str.length();i++){
        if((str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=122))
            postfix+=str[i];
        else if(str[i]==')'){

            while(s.top()!='('){
                postfix+=s.top();
                s.pop();
            }
            s.pop();
        }
        else if(str[i]=='(')
                    s.push(str[i]);
        else if(isOperator(str[i])==1){
            if(s.empty())
                s.push(str[i]);


            else if(isOperator(s.top())==1){

                    if(inPrec(s.top())<inPrec(str[i]))
                    s.push(str[i]);
                    else{
                            while(!s.empty() &&(isOperator(s.top())==1) &&(inPrec(s.top())>=inPrec(str[i]))){
                                postfix+=s.top();
                                s.pop();
                            }
                        s.push(str[i]);
                    }

            }
            else{
                s.push(str[i]);
            }
        }
    }

    while(!s.empty()){
        postfix+=s.top();
        s.pop();
    }
    return postfix;
}

int main(){
    //string str="A+B";
    string str="a+b*c-(d/e+f*g*h)";
cout<<infix_to_postfix(str);
}
