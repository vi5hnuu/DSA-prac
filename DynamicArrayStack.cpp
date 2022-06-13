#include<iostream>
using namespace std;

/*
struct DynArrayStack{
    int top;
    int capacity;
    int *array;
};

DynArrayStack *createStack(){
    DynArrayStack *s=new DynArrayStack;
    if(!s)
        return NULL;

    s->capacity=1;
    s->top=-1;
    s->array=new int[s->capacity];
    if(!s){
        delete s;
        return NULL;
    }
    return s;
}

bool isFull(DynArrayStack *s){
    return s->top==s->capacity-1;
}

bool isEmpty(DynArrayStack *s){
    return s->top==-1;
}

void DoubleStackSize(DynArrayStack *s){
    int oldSize=s->capacity;
    int *temp=new int[oldSize];
    for(int i=0;i<oldSize;i++)
        temp[i]=s->array[i];

    s->capacity*=2;
    delete[] s->array;

    s->array=new int[s->capacity];

    if(!s->array)
        throw string("Memory error.");

    for(int i=0;i<oldSize;i++)
        s->array[i]=temp[i];
}

void push(DynArrayStack *s,int data){
    if(isFull(s))
        DoubleStackSize(s);

    s->array[++s->top]=data;
}

int top(DynArrayStack *s){
    if(isEmpty(s))
        throw string("Stack underflow.");

    return s->array[s->top];
}

int pop(DynArrayStack *s){
    if(isEmpty(s))
        throw string("Stack underflow.");

    return s->array[s->top--];
}

void deleteArrayStack(DynArrayStack *s){
    if(s){
        if(s->array)
            delete[] s->array;
        delete s;
    }
}

int main(){
DynArrayStack *stck=createStack();
try{
push(stck,10);
cout<<stck->capacity<<endl;
push(stck,11);
cout<<stck->capacity<<endl;
push(stck,12);
cout<<stck->capacity<<endl;
push(stck,13);
cout<<stck->capacity<<endl;
push(stck,14);
cout<<stck->capacity<<endl;
push(stck,15);
cout<<stck->capacity<<endl;
cout<<"========"<<endl;
cout<<pop(stck)<<endl;
cout<<pop(stck)<<endl;
cout<<pop(stck)<<endl;
cout<<pop(stck)<<endl;
cout<<pop(stck)<<endl;
cout<<pop(stck)<<endl;
cout<<pop(stck)<<endl;
}
catch(string &x){
cout<<x;
}
}
*/

////////////////////////////////////////
class DynArrayStack{
    private:
        int top;
        int capacity;
        int *array;

        void DoubleStackSize(){
            int oldSize=this->capacity;
            int *temp=new int[oldSize];
            for(int i=0;i<oldSize;i++)
                temp[i]=this->array[i];

            this->capacity*=2;
            delete[] this->array;

            this->array=new int[this->capacity];

            if(!this->array)
                throw string("Memory error.");

            for(int i=0;i<oldSize;i++)
                this->array[i]=temp[i];
        }
    public:
        DynArrayStack(){
         this->capacity=1;
        this->top=-1;
        this->array=new int[this->capacity];
        if(!this){
            delete this;
            throw string("Memory error.");
            }
        }

       ~DynArrayStack(){
            if(this->array)
                delete[] this->array;
            this->array=NULL;
       }

       bool isFull()const {
            return this->top==this->capacity-1;
        }

        bool isEmpty()const {
            return this->top==-1;
        }

        void push(int data){
            if(this->isFull())
                this->DoubleStackSize();

            this->array[++this->top]=data;
        }

        int topp() const {
            if(this->isEmpty())
                throw string("Stack underflow.");

            return this->array[this->top];
        }

        int pop(){
            if(isEmpty())
                throw string("Stack underflow.");

        return this->array[this->top--];
        }
        int capacityy()const {
            return this->capacity;
        }
};





int main(){
DynArrayStack stck;
try{
stck.push(10);
cout<<stck.capacityy()<<endl;
stck.push(11);
cout<<stck.capacityy()<<endl;
stck.push(12);
cout<<stck.capacityy()<<endl;
stck.push(13);
cout<<stck.capacityy()<<endl;
stck.push(14);
cout<<stck.capacityy()<<endl;
stck.push(15);

cout<<stck.topp()<<endl;
cout<<stck.pop()<<endl;
cout<<stck.pop()<<endl;
cout<<stck.topp()<<endl;
cout<<stck.pop()<<endl;
cout<<stck.pop()<<endl;
cout<<stck.pop()<<endl;
cout<<stck.pop()<<endl;
cout<<stck.pop()<<endl;
}
catch(string &x){
cout<<x;
}
}


