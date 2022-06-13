#include <bits/stdc++.h>
using namespace std;

int CharInt(char c){
    switch(c){
    case 'c':return 0;
    case 'o':return 1;
    case 'v':return 2;
    case 'i':return 3;
    case 'd':return 4;
    }
}

int howManyTime(string s){
    vector<int> v(5,0);

    for(int i=0;i<s.length();i++){
        if(s[i]=='c' || s[i]=='o' || s[i]=='v' || s[i]=='i' || s[i]=='d'){
            v[CharInt(s[i])]++;
        }
    }
    int min=INT_MAX;
    for(int i=0;i<v.size();i++)
        if(v[i]<min)
            min=v[i];

    return min;
}

int main() {
    /*string s;
    string raw;
    while(cin>>s){raw+=s;}*/
    cout<<howManyTime("covid\ncov6454id");
    return 0;
}
