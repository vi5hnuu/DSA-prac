#include<iostream>
#include<stack>
using namespace std;


void insertAtBottom(stack<int> &s,int data){
    if(s.empty()){
        s.push(data);
        return;
    }
    int temp=s.top();
    s.pop();
    insertAtBottom(s,data);
    s.push(temp);
}

void reverseStack(stack<int> &s){
    if(s.empty())
    return;

    int data=s.top();
    s.pop();
    reverseStack(s);
    insertAtBottom(s,data);
}



int main(){
stack<int> s;
for(int i=1;i<=10;i++)
s.push(i);

reverseStack(s);

while(!s.empty()){
    cout<<s.top()<<endl;
    s.pop();
}
}
