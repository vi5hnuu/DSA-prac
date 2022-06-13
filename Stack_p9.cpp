#include<iostream>
#include<stack>
#include<list>
using namespace std;


bool isPalindromeXor(list<char> &str){
    int sz=str.size();
    int x=0;
    for(int i=0;i<sz;i++){
        if(str.front()=='X'){
            str.pop_front();
            continue;
            }
        x^=str.front();
        //cout<<str.front();
        str.pop_front();
    }
    if(x==0)
        return true;
    else
        return false;
}

int main(){
list<char> str;
string s="ababaaabaabXbaabaaababa";
for(int i=0;i<s.length();i++)
    str.push_back(s[i]);
cout<<isPalindromeXor(str)<<endl;

return 0;
}
