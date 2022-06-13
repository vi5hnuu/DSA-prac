#include <bits/stdc++.h>
using namespace std;


int howManyTime(string s){
    map<char,int> mp;
    for(int i=0;i<s.length();i++){
        if(s[i]=='c' || s[i]=='o' || s[i]=='v' || s[i]=='i' || s[i]=='d'){
            if(mp.find(s[i])!=mp.end())
                mp[s[i]]++;
            else
                mp[s[i]]=1;
        }
    }
    if(mp.size()!=5)
        return 0;

    int m=INT_MAX;
    string target="covid";
    for(int i=0;i<5;i++){
        m=min(m,mp.at(target[i]));
    }
    return m;

}

int main() {
    string s;
    cin>>s;
    cout<<howManyTime(s);
    return 0;
}
