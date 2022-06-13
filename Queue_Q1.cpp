#include<iostream>
using namespace std;


class LinkedQueue{
private:
    struct ListNode{
        int data;
        ListNode *next;
    }*front,*rear;
public:
    LinkedQueue(){
        front=rear=NULL;
    }
    ~LinkedQueue(){
    ListNode *temp=front;

    while(temp){
        if(temp)
        //cout<<"Deleted node with data "<<temp->data<<endl;
        ListNode *t=temp->next;
        delete temp;
        temp=t;
        }
        cout<<"Deleted Queue";
        front=rear=NULL;
    }


int IsEmpty() const{
    return this->front==NULL;
}

void EnQueue(int data){
ListNode *newNode=new ListNode;
if(!newNode)
    return;

newNode->data=data;
newNode->next=NULL;
if(this->rear)
    this->rear->next=newNode;

    this->rear=newNode;
    if(this->front==NULL)
    this->front=this->rear;

}

int DeQueue(){
    int data=INT_MAX;
    ListNode *temp;
    if(IsEmpty())
    return data;

    temp=this->front;
    data=temp->data;
    this->front=this->front->next;
    delete temp;
    return data;
}

void reverse(){
    if(front==NULL || front->next==NULL)
        return;

    ListNode *first=(front->next),*second=(first->next);
    this->rear=front;
    rear->next=NULL;

    ListNode *last=this->rear;

    while(first){
        first->next=last;
        last=first;
        first=second;
        if(second)
            second=second->next;
    }
    front=last;
}
};

int main(){

LinkedQueue Queue;
    Queue.EnQueue(10);
    Queue.EnQueue(11);
    Queue.EnQueue(12);
    Queue.EnQueue(13);
    Queue.EnQueue(14);

    Queue.reverse();
    cout<<Queue.DeQueue()<<endl;
    cout<<Queue.DeQueue()<<endl;


    return 0;
}
