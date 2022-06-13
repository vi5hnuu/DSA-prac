#include<iostream>
using namespace std;


/*
struct DynArrayQueue{
    int front;
    int rear;
    int capacity;
    int *array;
};

DynArrayQueue *createDynQueue(){
    DynArrayQueue *Q=new DynArrayQueue;
    if(!Q)
        return NULL;

    Q->capacity=10;
    Q->front=Q->rear=-1;
    Q->array=new  int[Q->capacity*sizeof(int)];
    if(!Q->array){
        delete Q;
        return NULL;
    }
    return Q;
}
int ISEmpty(DynArrayQueue *Q){
return Q->front==-1;
}

int IsFull(DynArrayQueue *Q){
    return((Q->rear+1)%Q->capacity==Q->front);
}

int QueueSize(DynArrayQueue *Q){
    if(Q->front!=-1 && (Q->capacity==(Q->front+Q->rear+1)))
       return Q->capacity;
    if(Q->front==-1)
    return 0;
return ((Q->capacity-Q->front+Q->rear+1)%Q->capacity);
}

void ResizeQueue(DynArrayQueue *Q){
    int sizee=Q->capacity;
    Q->capacity*=2;
    int *temp=new int[sizee];
    if(!temp)
        throw exception();

    for(int i=0;i<sizee;i++)
        temp[i]=Q->array[i];
    delete[] Q->array;
    Q->array=new int[Q->capacity];

    if(!Q->array)
        throw exception();

    for(int i=0;i<sizee;i++)
        Q->array[i]=temp[i];
    delete[] temp;
}
void EnQueue(DynArrayQueue *Q,int data){
    if(IsFull(Q))
        ResizeQueue(Q);
    Q->rear=(Q->rear+1)%Q->capacity;
    Q->array[Q->rear]=data;

    if(Q->front==-1)
        Q->front=Q->rear;
}


int DeQueue(DynArrayQueue *Q){
    if(ISEmpty(Q))
    throw exception();

    int data=Q->array[Q->front];
    if(Q->front==Q->rear)
        Q->front=Q->rear=-1;
    else
        Q->front=(Q->front+1)%Q->capacity;

    return data;
    }

*/


class DynArrayQueue{
    private:
        int front;
        int rear;
        int capacity;
        int *array;

        void ResizeQueue(){
    int sizee=this->capacity;
    this->capacity*=2;
    int *temp=new int[sizee];
    if(!temp)
        throw exception();

    for(int i=0;i<sizee;i++)
        temp[i]=this->array[i];
    delete[] this->array;
    this->array=new int[this->capacity];

    if(!this->array)
        throw exception();

    for(int i=0;i<sizee;i++)
        this->array[i]=temp[i];
    delete[] temp;
}
    public:
       DynArrayQueue(){
         this->capacity=10;
    this->front=this->rear=-1;
    this->array=new  int[this->capacity*sizeof(int)];
    if(!this->array){
        throw exception();
    }
       }
       ~DynArrayQueue(){
         if(this->array)
         delete[] this->array;
         cout<<"Queue deleted";
         }


    int IsEmpty()const{
return this->front==-1;
}

int IsFull()const{
    return((this->rear+1)%this->capacity==this->front);
}

int QueueSize()const{
    if(this->front!=-1 && (this->capacity==(this->front+this->rear+1)))
       return this->capacity;
    if(this->front==-1)
        return 0;
    return ((this->capacity-this->front+this->rear+1)%this->capacity);
}


void EnQueue(int data){
    if(IsFull())
        ResizeQueue();
    this->rear=(this->rear+1)%this->capacity;
    this->array[this->rear]=data;

    if(this->front==-1)
        this->front=this->rear;
}


int DeQueue(){
    if(IsEmpty())
    throw exception();

    int data=this->array[this->front];
    if(this->front==this->rear)
        this->front=this->rear=-1;
    else
        this->front=(this->front+1)%this->capacity;

    return data;
    }

int getcapacity(){
    return this->capacity;
}
};


int main(){
    /*try{
    DynArrayQueue *myQueue=createDynQueue();
    cout<<QueueSize(myQueue)<<endl;
    cout<<myQueue->capacity<<endl;
    EnQueue(myQueue,10);
    EnQueue(myQueue,11);
    EnQueue(myQueue,12);
    EnQueue(myQueue,13);
    EnQueue(myQueue,14);
    EnQueue(myQueue,15);
    EnQueue(myQueue,16);
    EnQueue(myQueue,17);
    EnQueue(myQueue,18);
    EnQueue(myQueue,19);
    cout<<QueueSize(myQueue)<<endl;
    cout<<myQueue->capacity<<endl;
    EnQueue(myQueue,20);
    cout<<QueueSize(myQueue)<<endl;
    cout<<myQueue->capacity<<endl;
    cout<<"=========="<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    cout<<DeQueue(myQueue)<<endl;
    }catch(exception &x){
        cout<<x.what();
    }*/


    try{
        DynArrayQueue Queue;
        cout<<Queue.getcapacity()<<endl;
        cout<<Queue.QueueSize()<<endl;
        Queue.EnQueue(10);
        Queue.EnQueue(11);
        Queue.EnQueue(12);
        Queue.EnQueue(13);
        Queue.EnQueue(14);
        Queue.EnQueue(15);
        Queue.EnQueue(16);
        Queue.EnQueue(17);
        Queue.EnQueue(18);
        Queue.EnQueue(19);
        cout<<Queue.getcapacity()<<endl;
        cout<<Queue.QueueSize()<<endl;
        Queue.EnQueue(20);
        cout<<Queue.getcapacity()<<endl;
        cout<<Queue.QueueSize()<<endl;

        cout<<Queue.DeQueue()<<endl;
        cout<<Queue.DeQueue()<<endl;
        cout<<Queue.DeQueue()<<endl;
        cout<<Queue.DeQueue()<<endl;
        cout<<Queue.DeQueue()<<endl;
        cout<<Queue.DeQueue()<<endl;
        cout<<Queue.DeQueue()<<endl;
        cout<<Queue.DeQueue()<<endl;
        cout<<Queue.DeQueue()<<endl;
        cout<<Queue.DeQueue()<<endl;
        cout<<Queue.DeQueue()<<endl;
    }catch(exception &x){
    cout<<x.what();
    }
}
