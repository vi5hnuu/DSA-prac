#include<iostream>
#include<exception>
using namespace std;



class Stack{
    private:
       struct Node{
        int data;
        Node *next;
       }*front;
    public:
        Stack(){
            front=NULL;
        }
        ~Stack(){

            Node *temp=NULL;
            while(front){
                temp=front;
                front=front->next;
                //cout<<"deleted "<<temp->data<<endl;
                delete temp;
            }

        }
        bool isEmpty(){
            return this->front==NULL;
        }
        int pop(){
            if(front){
            Node *temp=front;
            int data=temp->data;
            front=front->next;
            delete temp;
            return data;
            }else{
                throw string("Stack is empty");
            }
        }
        int peek(){
            if(front)
            return front->data;
            else{
                throw string("Stack is empty");
            }
        }
        void push(int data){
            Node *newNode=new Node;
            newNode->data=data;
            newNode->next=NULL;

            if(front==NULL)
            front=newNode;
            else{
            newNode->next=front;
            front=newNode;
            }
        }
};

/*
int main(){
try{
Stack stck;
stck.push(10);
stck.push(11);
stck.push(12);
stck.push(13);
stck.push(14);
*/
/*cout<<stck.pop()<<endl;
cout<<stck.pop()<<endl;
cout<<stck.pop()<<endl;
cout<<stck.pop()<<endl;
cout<<stck.pop()<<endl;
cout<<stck.pop()<<endl;*/
/*}
catch(string &str){
    cout<<str;
}
}*/

