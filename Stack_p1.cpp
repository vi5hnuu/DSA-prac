#include<iostream>
#include "StackLinkedList.cpp"
using namespace std;


bool isBalanced(string &str){

    Stack s;//int stack
    for(int i=0;i<str.length();i++){

            if(str[i]=='(' || str[i]=='{' || str[i]=='['){

                s.push(str[i]);
               }
            else if(str[i]==')' || str[i]=='}' || str[i]==']'){
                    int diff=str[i]-s.pop();
                if(!(diff==2 || diff==1)){
                    return false;
                }
            }
    }
    if(s.isEmpty())
        return true;
    else
        return false;
}

int main(){
//string s="((({{{}}}))){}[][[]{}]";
//string s="(A+B)+(C-D)";
//string s="((A+B)+(C-D)";
//string s="((A+B)+[C-D])";
string s="((A+B)+[C-D]}";
cout<<(isBalanced(s)==1 ? "Balanced" : "Not Balanced");

}
