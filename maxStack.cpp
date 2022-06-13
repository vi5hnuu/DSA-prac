#include<iostream>
#include<stack>
#include<vector>
using namespace std;


int main(){
//vector<int> v={2,5,8,9,6,3,4,7,5,3,9,2};
vector<int> v={10,9,8,2,5,6,3,4,7};
stack<int> s;

for(int i=0;i<v.size();i++){
    if(s.empty() || s.top()>=v[i])
    s.push(v[i]);
    else{
        while(!s.empty() && s.top()<v[i]){
            s.pop();
        }
        s.push(v[i]);
    }
}
int i=s.size();
while(!s.empty()){
    cout<<i<<" max :"<<s.top()<<endl;
    i--;
    s.pop();
}
}
