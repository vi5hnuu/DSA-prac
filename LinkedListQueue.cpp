#include<iostream>
using namespace std;

/*
struct ListNode{
int data;
ListNode *next;
};

struct Queue{
ListNode *front;
ListNode *rear;
};

Queue* createQueue(){
    Queue *Q;
    Q=new Queue;
    if(!Q)
    return NULL;

    Q->front=Q->rear=NULL;
    return Q;
}

int IsEmpty(const Queue *const Q){
    return Q->front==NULL;
}

void EnQueue(const Queue *Q,int data){
ListNode *newNode=new ListNode;
if(!newNode)
    return;

newNode->data=data;
newNode->next=NULL;
if(Q->rear)
    Q->rear->next=newNode;

    Q->rear=newNode;
    if(Q->front==NULL)
    Q->front=Q->rear;

}

int DeQueue(const Queue *Q){
    int data=INT_MAX;
    ListNode *temp;
    if(IsEmpty(Q))
    return data;

    temp=Q->front;
    data=temp->data;
    Q->front=Q->front->next;
    delete temp;
    return data;
}

void deleteQueue(const Queue *Q){
ListNode *temp=Q->front;

while(temp){
    if(temp)
    cout<<"Deleted node with data "<<temp->data<<endl;
    ListNode *t=temp->next;

    delete temp;
    temp=t;
}
cout<<"Deleted Queue";
delete Q;
Q=NULL;
}
*/

class LinkedQueue{
private:
    struct ListNode{
        int data;
        ListNode *next;
    }*front,*rear;
     //we need rear to add node at end...if we dont have rear we have to traverse list on each addition.....
public:
    int length;
    LinkedQueue(){
        this->length=0;
        front=rear=NULL;
    }
    ~LinkedQueue(){
    ListNode *temp=front;

    while(temp){
        if(temp){
        //cout<<"Deleted node with data "<<temp->data<<endl;
        }
        ListNode *t=temp->next;
        delete temp;
        temp=t;
        }
        //cout<<"Deleted Queue\n";
        front=rear=NULL;
    }


int IsEmpty() const{
    return this->front==NULL;
}

void EnQueue(int data){
        ListNode *newNode = new ListNode;
        if (!newNode)
            return;

        this->length++;
        newNode->data = data;
        newNode->next = NULL;
        if (this->IsEmpty()){
            this->front = newNode;
        }
        else{
            this->rear->next = newNode;
        }
        this->rear = newNode;
}

int DeQueue(){
    int data=INT_MAX;
    ListNode *temp;
    if(IsEmpty())
    return data;

    temp=this->front;
    data=temp->data;
    this->front=temp->next;
    delete temp;
    this->length--;
    return data;
}
};


//int main(){
    /*Queue *myQueue=createQueue();
    EnQueue(myQueue,10);
    EnQueue(myQueue,11);
    EnQueue(myQueue,12);
    EnQueue(myQueue,13);
    EnQueue(myQueue,14);
    EnQueue(myQueue,15);

    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;

    deleteQueue(myQueue);*/


    /*LinkedQueue Queue;
    Queue.EnQueue(10);
    Queue.EnQueue(11);
    Queue.EnQueue(12);
    Queue.EnQueue(13);
    Queue.EnQueue(14);

    cout<<Queue.DeQueue()<<endl;
    cout<<Queue.DeQueue()<<endl;


    return 0;*/
//}
