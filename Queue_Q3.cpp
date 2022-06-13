#include<iostream>
#include "LinkedListQueue.cpp"
using namespace std;

class Stack{
private:
    LinkedQueue Queue1;
    LinkedQueue Queue2;
public:
    int pop(){

            if(Queue1.IsEmpty() && Queue2.IsEmpty())
                throw string("Stack is Empty");

            int data;

            if(!Queue1.IsEmpty()){
            while(!Queue1.IsEmpty()){
            data=Queue1.DeQueue();

            if(!Queue1.IsEmpty())
            Queue2.EnQueue(data);
            //cout<<data<<" ";
                }
            }
            else{
            while(!Queue2.IsEmpty()){
            data=Queue2.DeQueue();

            if(!Queue2.IsEmpty())
            Queue1.EnQueue(data);
            //cout<<data<<" ";
                }
            }
            return data;
    }

    void push(int data){
        //one Queue is always empty
        if(Queue1.IsEmpty())
            Queue2.EnQueue(data);
        else
            Queue1.EnQueue(data);
    }

};

int main(){
    try{
    Stack stck;
    stck.push(10);
    stck.push(11);
    stck.push(12);
    stck.push(13);
    stck.push(14);
    stck.push(15);

    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    /*cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;*/
    cout<<stck.pop()<<endl;//comment three pop's
    }
    catch(string &x){
        cout<<x<<endl;
    }
return 0;
}

