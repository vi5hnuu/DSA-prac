#include<iostream>
#include<stack>
using namespace std;

//we can use xor as well as for large string stack get more space usage

bool isPalindrome(string &str){
    stack<char> s;

    int i=0;
    while(str[i]!='X')
        s.push(str[i++]);
    i++;
    while(!s.empty()){
        if(s.top()!=str[i++])
            return false;
        s.pop();
    }
    if(i==str.length())
        return true;
    else
        return false;

}

bool isPalindromeXor(string &str){
    int x=0;
    for(int i=0;i<str.length();i++){
        if(str[i]=='X')
            continue;
        x^=str[i];
    }
    if(x==0)
        return true;
    else
        return false;
}

int main(){
string str="ababaaabaabXbaabaaababa";
cout<<isPalindrome(str)<<endl;
cout<<isPalindromeXor(str)<<endl;

return 0;
}
