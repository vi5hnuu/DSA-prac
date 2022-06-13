#include<iostream>
#include<queue>
using namespace std;

class Stack{
private:
    queue<int> Queue1;
    queue<int> Queue2;
public:
    int pop(){

            if(Queue1.empty() && Queue2.empty())
                throw string("Stack is Empty");
            int data;
            if(!Queue1.empty())
            while(!Queue1.empty()){
            data=Queue1.front();
            Queue1.pop();

            if(!Queue1.empty())
            Queue2.push(data);
            //cout<<data<<" ";
            }
            else
            while(!Queue2.empty()){
            data=Queue2.front();
            Queue2.pop();

            if(!Queue2.empty())
            Queue1.push(data);
            //cout<<data<<" ";
            }
            return data;
    }

    void push(int data){
        //one Queue is always empty
        if(Queue1.empty())
            Queue2.push(data);
        else
            Queue1.push(data);
    }

};

int main(){
    try{
    Stack stck;
    stck.push(9);
    stck.push(10);
    stck.push(11);
    stck.push(12);
    stck.push(13);
    stck.push(14);
    stck.push(15);
    stck.push(16);

    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;//comment three pop's*/
    }
    catch(string &x){
        cout<<x<<endl;
    }
return 0;
}

