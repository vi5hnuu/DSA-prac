#include<iostream>
using namespace std;

/*
#define MAXSIZE 10

struct ArrayStack{
    int top;
    int capacity;
    int *array;
};

ArrayStack* createStack(){
    ArrayStack *s=new ArrayStack;
    if(!s)
    return NULL;

    s->capacity=MAXSIZE;
    s->top=-1;
    s->array=new int[s->capacity];
    if(!s->array){
        delete s;
        return NULL;
    }
    return s;
}

int isEmpty(ArrayStack *s){
    return s->top==-1;
}

int isFull(ArrayStack *s){
    return s->top==s->capacity-1;
}

void push(ArrayStack *s,int data){
    if(isFull(s))
    throw string("stack is full.");

    s->array[++s->top]=data;
}

int pop(ArrayStack *s){
    if(isEmpty(s))
        throw string("stack is empty.");

    return s->array[s->top--];
}

void deleteStack(ArrayStack *s){
    if(s){
        if(s->array)
        delete[] s->array;

        delete s; //to which s pointing is not set to null but yes all memory is released
    }
}

int main(){
ArrayStack *stck=createStack();
try{
push(stck,10);
push(stck,11);
push(stck,12);
push(stck,13);
push(stck,14);
push(stck,15);

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



class Stack{
private:
    const static int MAXSIZE=10;
    int top;
    int capacity;
    int *array;
public:
    Stack(){
        this->top=-1;
        this->capacity=10;
        this->array=new int[this->capacity];
    }

    ~Stack(){
        if(this->array)
            delete[] this->array;
        this->array=NULL;
    }

    int isEmpty()const{
    return this->top==-1;
    }

    int isFull() const{
    return this->top==this->capacity-1;
    }

    void push(int data){
    if(this->isFull())
        throw string("stack is full.");

    this->array[++this->top]=data;
    }

    int pop(){
    if(this->isEmpty())
        throw string("stack is empty.");

    return this->array[this->top--];
    }
};





int main(){
Stack stck;
try{
stck.push(10);
stck.push(11);
stck.push(12);
stck.push(13);
stck.push(14);
stck.push(15);

cout<<stck.pop()<<endl;
cout<<stck.pop()<<endl;
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
