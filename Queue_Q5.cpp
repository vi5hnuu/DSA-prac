#include<iostream>
#include "LinkedListQueue.cpp"
#include "LinkedStack.cpp"
using namespace std;


int main(){
    LinkedQueue Queue;
    Stack stck;

    for(int i=21;i<=30;i++)
    Queue.EnQueue(i);

    for(int i=0;i<Queue.length;i++) //Enqueue take O(1) ,DeQueue take O(1)
    stck.push(Queue.DeQueue());

    int data=INT_MAX;
    while(!stck.isEmpty()){
        data=stck.pop();


        if(!stck.isEmpty())
        Queue.EnQueue(data);
    }
    stck.push(data);




    cout<<"On Top :"<<stck.pop()<<endl;
}
