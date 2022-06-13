#include<iostream>
#include "LinkedListQueue.cpp"
#include "LinkedStack.cpp"

using namespace std;


int checkStackPairWiseOrder(Stack stck){ //new stack create ...we dont want to disturb original stack
    LinkedQueue Queue;
    bool pairWiseOdd=true;
    while(!stck.isEmpty()){
        Queue.EnQueue(stck.pop());
    }
    while(!Queue.IsEmpty()){
        stck.push(Queue.DeQueue());
    }
    while(!stck.isEmpty()){
        int a=stck.pop();
        if(!stck.isEmpty() && abs(stck.pop()-a)!=1){
            pairWiseOdd=false;
            break;
        }
    }
    return pairWiseOdd;
}

int main(){
    Stack stck; //[4,5,-2,-3,11,10,5,6,20]
    /*stck.push(20);
    stck.push(6);
    stck.push(5);
    stck.push(10);
    stck.push(11);
    stck.push(-3);
    stck.push(-2);
    stck.push(5);
    stck.push(4);*/

    stck.push(20);
    stck.push(19);
    stck.push(16);
    stck.push(15);
    stck.push(12);
    stck.push(11);
    stck.push(8);
    stck.push(7);
    stck.push(2);
    cout<<"\nIs pair wise ordered :"<<(checkStackPairWiseOrder(stck)==1 ? "true" : "false")<<endl;

}
