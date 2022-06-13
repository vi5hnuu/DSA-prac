#include<iostream>
#include<stack>
using namespace std;

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

int evaluate_postfix(string &str){
    stack<int> s;
    for(int i=0;i<str.length();i++){
        if(str[i]==' ')
        continue;
        if(isOperator(str[i])==1){
            if(s.empty())
                throw string("Invalid postfix expression");
            int a=s.top();
            s.pop();
            if(s.empty())
                throw string("Invalid postfix expression");
            int b=s.top();
            s.pop();
            switch (str[i])
            {
            case '+': s.push(b+a); break;
            case '-': s.push(b-a); break;
            case '*': s.push(a*b); break;
            case '/': s.push(b/a); break;
            case '%': s.push(b%a); break;
            }
        }else{
            int num=0;
            while(str[i]!=' ')
                num=num*10+str[i++]-'0';
            s.push(num);
            //cout<<"num :"<<num<<endl;
        }
    }
    return s.top();
}

int main(){
    //string str="2 3 +";
    //string str=" 22 3 1 * + 9 - ";

    string str="1 * + 9 - ";
    try{
    cout<<evaluate_postfix(str);
    }catch(string &x){
        cout<<x<<endl;
    }
    return 0;
}
