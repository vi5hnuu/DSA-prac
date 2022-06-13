#include<iostream>
#include<stack>
using namespace std;


struct advancedStack{
    stack<int> elementStack;
    stack<int> minStack;
};

void push(advancedStack &s,int data){
    s.elementStack.push(data);
    if(s.minStack.empty() || s.minStack.top()>=data)
    s.minStack.push(data);
    else{
        s.minStack.push(s.minStack.top());
    }
}

int pop(advancedStack &s){
    if(s.elementStack.empty())
        throw string("Stack is empty.");
    s.minStack.pop();
    int data=s.elementStack.top();
    s.elementStack.pop();
    return data;
}

int getMin(advancedStack &s){
    if(s.elementStack.empty())
        throw string("Stack is empty.");

    return s.minStack.top();
}

int main(){
    advancedStack stck;
    push(stck,10);
    push(stck,11);
    push(stck,5);
    push(stck,13);
    push(stck,2);
    push(stck,15);

    cout<<pop(stck)<<endl;
    cout<<pop(stck)<<endl;
    cout<<"Min :"<<getMin(stck)<<endl;
    cout<<pop(stck)<<endl;
    cout<<pop(stck)<<endl;
    cout<<"Min :"<<getMin(stck)<<endl;

    return 0;
}
