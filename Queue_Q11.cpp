#include<iostream>
#include "LinkedListQueue.cpp"
#include "LinkedStack.cpp"
using namespace std;


void reverseQueueFirstKElement(int k,LinkedQueue &Q){
    if(Q.length==0 || k>Q.length || k==0 || k==1)
        return;

    Stack stck;
    for(int i=0;i<k;i++)
    stck.push(Q.DeQueue());

    while(!stck.isEmpty()){
            Q.EnQueue(stck.pop());
    }
    for(int i=0;i<Q.length-k;i++){
        Q.EnQueue(Q.DeQueue());
    }
}

int main(){
    LinkedQueue Queue;
    Queue.EnQueue(10);
    Queue.EnQueue(20);
    Queue.EnQueue(30);
    Queue.EnQueue(40);
    Queue.EnQueue(50);
    Queue.EnQueue(60);
    Queue.EnQueue(70);
    Queue.EnQueue(80);
    reverseQueueFirstKElement(4,Queue);

    while(!Queue.IsEmpty()){
        cout<<Queue.DeQueue()<<endl;
    }
}
