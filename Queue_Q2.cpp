#include<iostream>
#include "LinkedStack.cpp"
using namespace std;

class Queue{
private:
    Stack stack1;
    Stack stack2;
public:
    void enQueue(int data){
    stack1.push(data);
    }
    int deQueue(){
    if(stack2.isEmpty()){
            if(stack1.isEmpty())
                throw "Queue is Empty.";

        while(!stack1.isEmpty()){
            stack2.push(stack1.pop());
        }
        return stack2.pop();
    }
    return stack2.pop();
    }

};

int main(){
    Queue myQueue;
    myQueue.enQueue(10);
    myQueue.enQueue(11);
    myQueue.enQueue(12);
    myQueue.enQueue(13);
    myQueue.enQueue(14);
    myQueue.enQueue(15);
    cout<<myQueue.deQueue()<<endl;
    myQueue.enQueue(16);
    myQueue.enQueue(17);
    myQueue.enQueue(18);
    myQueue.enQueue(19);
    myQueue.enQueue(20);
    cout<<myQueue.deQueue()<<endl;
    cout<<myQueue.deQueue()<<endl;
    cout<<myQueue.deQueue()<<endl;
    cout<<myQueue.deQueue()<<endl;


    //stack1 stack2 emptied here.....
    return 0;
}
