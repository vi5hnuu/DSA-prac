#include<iostream>
using namespace std;

/*
struct ListNode{
    int data;
    ListNode *next;
    ListNode *prev;
};



void pushBackDEQ(ListNode **head,int data){
    ListNode *newNode=new ListNode;
    newNode->data=data;

    if(*head==NULL){
        *head=newNode;
        (*head)->next=*head;
        (*head)->prev=*head;
    }
    else{
        newNode->prev=(*head)->prev;
        newNode->next=*head;
        (*head)->prev->next=newNode;
        (*head)->prev=newNode;
    }
}

void pushFrontDEQ(ListNode **head,int data){
    pushBackDEQ(head,data);
    *head=(*head)->prev;
}

int popBackDEQ(ListNode **head){
    int data;
    if(*head==NULL)
        throw string("Queue is empty");

    if((*head)->prev==*head){
        data=(*head)->data;
        delete *head;
        *head=NULL;
    }
    else{
        ListNode *newTail=(*head)->prev->prev;
        data=(*head)->prev->data;
        newTail->next=*head;
        delete (*head)->prev;
        (*head)->prev=newTail;
    }

    return data;
}

int popFront(ListNode **head){
    if(*head==NULL)
        throw string("Queue is empty");

    *head=(*head)->next;
    return popBackDEQ(head);

}

void deleteFullQueue(ListNode **Q){
    //make singleLinked lIst and delete
    if((*Q)==NULL)
        return;

    (*Q)->prev->next=NULL;
    (*Q)->prev=NULL;
    ListNode *temp=NULL;
    while(*Q){
        temp=*Q;
        (*Q)=(*Q)->next;
        cout<<"delete "<<temp->data<<endl;
        delete temp;
    }
    (*Q)=NULL;
}

int main(){
    ListNode *CQueue=NULL;
    pushBackDEQ(&CQueue,16);
    pushBackDEQ(&CQueue,17);
    pushBackDEQ(&CQueue,18);
    pushBackDEQ(&CQueue,19);
    pushBackDEQ(&CQueue,20);

    pushFrontDEQ(&CQueue,15);
    pushFrontDEQ(&CQueue,14);
    pushFrontDEQ(&CQueue,13);
    pushFrontDEQ(&CQueue,12);
    pushFrontDEQ(&CQueue,11);

    cout<<popBackDEQ(&CQueue)<<endl;
    cout<<popBackDEQ(&CQueue)<<endl;
    cout<<popBackDEQ(&CQueue)<<endl;
    cout<<popBackDEQ(&CQueue)<<endl;
    cout<<popBackDEQ(&CQueue)<<endl;

    cout<<popFront(&CQueue)<<endl;
    cout<<popFront(&CQueue)<<endl;
    cout<<popFront(&CQueue)<<endl;
    cout<<popFront(&CQueue)<<endl;
    cout<<popFront(&CQueue)<<endl;

    deleteFullQueue(&CQueue);

    cout<<(CQueue==NULL);
    return 0;
}
*/

///////////////////////////////////////////////////

class CQueue{
private:
    struct ListNode{
        int data;
        ListNode *next;
        ListNode *prev;
    }*head;

    void deleteFullQueue(){
    //make singleLinked lIst and delete
    if(this->head==NULL)
        return;

    this->head->prev->next=NULL;
    this->head->prev=NULL;
    ListNode *temp=NULL;
    while(this->head){
        temp=this->head;
        this->head=this->head->next;
        cout<<"delete "<<temp->data<<endl;
        delete temp;
    }
    //cout<<(head==NULL);
    }
public:
    CQueue(){
        head=NULL;
    }
    ~CQueue(){
        deleteFullQueue();
    }

    void pushBackDEQ(int data){
    ListNode *newNode=new ListNode;
    newNode->data=data;

    if(this->head==NULL){
        this->head=newNode;
        this->head->next=this->head;
        this->head->prev=this->head;
    }
    else{
        newNode->prev=this->head->prev;
        newNode->next=this->head;
        this->head->prev->next=newNode;
        this->head->prev=newNode;
        }
    }

    void pushFrontDEQ(int data){
        this->pushBackDEQ(data);
        head=head->prev;
    }

    int popBackDEQ(){
    int data;
    if(this->head==NULL)
        throw string("Queue is empty");

    if(this->head->prev==this->head){
        data=this->head->data;
        delete this->head;
        this->head=NULL;
    }
    else{
        ListNode *newTail=this->head->prev->prev;
        data=this->head->prev->data;
        newTail->next=this->head;
        delete this->head->prev;
        this->head->prev=newTail;
    }

    return data;
    }

    int popFront(){
    if(this->head==NULL)
        throw string("Queue is empty");

    this->head=this->head->next;
    return this->popBackDEQ();
    }

};



int main(){
    CQueue Queue;
    Queue.pushBackDEQ(16);
    Queue.pushBackDEQ(17);
    Queue.pushBackDEQ(18);
    Queue.pushBackDEQ(19);
    Queue.pushBackDEQ(20);

    Queue.pushFrontDEQ(15);
    Queue.pushFrontDEQ(14);
    Queue.pushFrontDEQ(13);
    Queue.pushFrontDEQ(12);
    Queue.pushFrontDEQ(11);

    cout<<Queue.popBackDEQ()<<endl;
    cout<<Queue.popBackDEQ()<<endl;
    cout<<Queue.popBackDEQ()<<endl;
    cout<<Queue.popBackDEQ()<<endl;
    cout<<Queue.popBackDEQ()<<endl;

    cout<<Queue.popFront()<<endl;
    /*cout<<Queue.popFront()<<endl;
    cout<<Queue.popFront()<<endl;
    cout<<Queue.popFront()<<endl;
    cout<<Queue.popFront()<<endl;*/

    return 0;
}




