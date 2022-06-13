#include<iostream>
#include "LinkedListQueue.cpp"
#include "LinkedStack.cpp"
using namespace std;

void interLeavingQueue(LinkedQueue &Q){
if(Q.length & 1 == 1)
    return;

    Stack stck;
    int halfSize=Q.length/2;
    for(int i=0;i<halfSize;i++)
        stck.push(Q.DeQueue());
    while(!stck.isEmpty()){
        Q.EnQueue(stck.pop());
    }
    for(int i=0;i<halfSize;i++){
    Q.EnQueue(Q.DeQueue());
    }

    for(int i=0;i<halfSize;i++){
        stck.push(Q.DeQueue());
    }
    while(!stck.isEmpty()){
        Q.EnQueue(stck.pop());
        Q.EnQueue(Q.DeQueue());
    }
}

int main(){
    LinkedQueue Queue;
    Queue.EnQueue(11);
    Queue.EnQueue(12);
    Queue.EnQueue(13);
    Queue.EnQueue(14);
    Queue.EnQueue(15);
    Queue.EnQueue(16);
    Queue.EnQueue(17);
    Queue.EnQueue(18);
    Queue.EnQueue(19);
    Queue.EnQueue(20);
    interLeavingQueue(Queue);

    while(!Queue.IsEmpty()){
        cout<<Queue.DeQueue()<<endl;
    }

}
