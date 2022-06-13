#include<iostream>
#include<exception>
using namespace std;

/*
struct ArrayQueue{
int front;
int rear;
int capacity;
int *array;
};

ArrayQueue *Queue(int size){
    ArrayQueue *Q=new ArrayQueue;
    if(!Q)
    return NULL;

    Q->capacity=size;
    Q->front=Q->rear=-1;
    Q->array=new int[Q->capacity*sizeof(int)];

    if(!Q->array){
        delete Q;
        return NULL;
    }
    return Q;
}

bool IsEmpty(const ArrayQueue *const Q){
    return Q->front==-1;
}

int IsFull(const ArrayQueue *const Q){
    return (Q->rear+1)%Q->capacity==Q->front;
}

int QueueSize(const ArrayQueue *const Q){
    return ((Q->capacity-Q->front+Q->rear+1)%Q->capacity);
}

void EnQueue(ArrayQueue *const Q,int data){
    if(IsFull(Q))
        cout<<"Queue-Overflow\n";
    else{
        Q->rear=(Q->rear+1)%Q->capacity;
        Q->array[Q->rear]=data;
        if(Q->front==-1)
            Q->front=Q->rear;
    }
}

int DeQueue(ArrayQueue *const Q){
    int data=INT_MAX;
    if(IsEmpty(Q))
        cout<<"Queue-Under-Flow->";
    else{
        data=Q->array[Q->front];
        if(Q->front==Q->rear)
            Q->front=Q->rear=-1;
        else
            Q->front=(Q->front+1)%Q->capacity;
    }
    return data;
}


int main(){
ArrayQueue *myQueue=Queue(4);
EnQueue(myQueue,10);
EnQueue(myQueue,11);
EnQueue(myQueue,12);
EnQueue(myQueue,13);
cout<<DeQueue(myQueue)<<endl;
cout<<DeQueue(myQueue)<<endl;
cout<<DeQueue(myQueue)<<endl;
cout<<DeQueue(myQueue)<<endl;
cout<<DeQueue(myQueue)<<endl;
}
*/


class ArrayQueue{
private:
    int front;
    int rear;
    int capacity;
    int *array;
public:
    ArrayQueue(int size){
    this->capacity=size;
    this->front=this->rear=-1;
    this->array=new int[this->capacity*sizeof(int)];

    if(!this->array){
            throw  exception();
    }
    }
    ~ArrayQueue(){
    if(this->array)
    delete[] this->array;
    cout<<"Queue deleted";
    }


bool IsEmpty()const {
    return this->front==-1;
}

int IsFull()const{
    return (this->rear+1)%this->capacity==this->front;
}

int QueueSize(){
    return ((this->capacity-this->front+this->rear+1)%this->capacity);
}

void EnQueue(int data){
    if(IsFull())
        throw exception();
    else{
        this->rear=(this->rear+1)%this->capacity;
        this->array[this->rear]=data;
        if(this->front==-1)
            this->front=this->rear;
    }
}

int DeQueue(){
    int data=INT_MAX;
    if(IsEmpty())
        throw exception();
    else{
        data=this->array[this->front];
        if(this->front==this->rear)
            this->front=this->rear=-1;
        else
            this->front=(this->front+1)%this->capacity;
    }
    return data;
}
};



int main(){
ArrayQueue myQueue(4);
try{
myQueue.EnQueue(10);
myQueue.EnQueue(11);
myQueue.EnQueue(12);
myQueue.EnQueue(13);
myQueue.EnQueue(14);
myQueue.EnQueue(14);
myQueue.EnQueue(14);
}catch(exception &x){
    cout<<"Fatal Error\n";
}

try{
cout<<myQueue.DeQueue()<<endl;
cout<<myQueue.DeQueue()<<endl;
cout<<myQueue.DeQueue()<<endl;
cout<<myQueue.DeQueue()<<endl;
cout<<myQueue.DeQueue()<<endl;
cout<<myQueue.DeQueue()<<endl;
cout<<myQueue.DeQueue()<<endl;
}catch(exception &y){
    cout<<"Fatal error\n";
}
}
