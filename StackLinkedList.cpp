#include<iostream>
using namespace std;

/*
struct ListNode{
    int data;
    ListNode *next;
};


void push(ListNode **top,int data){
    ListNode *temp;
    temp=new ListNode;
    if(!temp)
        throw string("Memory error.");

    temp->data=data;
    temp->next=*top;

    *top=temp;
}

bool isEmpty(ListNode *s){
    return s==NULL;
}

int pop(ListNode **top){
    int data;

    if(*top==NULL)
        throw string("stack underflow");

    ListNode *temp=*top;
    *top=(*top)->next;
    data=temp->data;
    delete temp;

    return data;
}

int topp(ListNode *s){
    if(s==NULL)
        throw string("stack underflow");

    return s->data;
}

void deleteStack(ListNode **top){
    ListNode *temp=NULL;
    while(*top){
        temp=*top;
        *top=(*top)->next;
        cout<<"deleted "<<temp->data<<endl;
        delete temp;
    }
    *top=NULL;
}

int main(){
    try{
ListNode *top=NULL;
//cout<<topp(top)<<endl;
push(&top,10);
cout<<topp(top)<<endl;
push(&top,11);
push(&top,12);
push(&top,13);
cout<<topp(top)<<endl;
push(&top,14);
push(&top,15);

cout<<pop(&top)<<endl;
cout<<pop(&top)<<endl;
cout<<pop(&top)<<endl;
cout<<pop(&top)<<endl;
cout<<pop(&top)<<endl;
deleteStack(&top);
cout<<pop(&top)<<endl;
cout<<pop(&top)<<endl;
    }
    catch(string &x){
        cout<<x;
    }
}
*/

////////////////////////////////
class Stack{
    private:
        struct ListNode{
            int data;
            ListNode *next;
        }*top;

        void deleteStack(){
            ListNode *temp=NULL;
            while(this->top){
                temp=this->top;
                this->top=(this->top)->next;
                cout<<"deleted "<<temp->data<<endl;
                delete temp;
            }
            this->top=NULL;
        }

    public:
        Stack(){
            top=NULL;
        }
        ~Stack(){
            this->deleteStack();
        }
    void push(int data){
    ListNode *temp;
    temp=new ListNode;
    if(!temp)
        throw string("Memory error.");

    temp->data=data;
    temp->next=this->top;
    this->top=temp;
    }

    bool isEmpty(){
        return this->top==NULL;
    }

    int pop(){
        int data;

        if(this->top==NULL)
            throw string("stack underflow");

        ListNode *temp=this->top;
        this->top=(this->top)->next;
        data=temp->data;
        delete temp;

        return data;
    }

    int peek(){
        if(this->top==NULL)
            throw string("stack underflow");

        return this->top->data;
    }
};

/*
int main(){
    try{
    Stack stck;
    stck.push(10);
    cout<<stck.peek()<<endl;
    stck.push(11);
    stck.push(12);
    stck.push(13);
    stck.push(14);
    cout<<stck.peek()<<endl;
    stck.push(15);

    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    cout<<stck.pop()<<endl;
    }catch(string &x){
        cout<<x;
    }
}
*/
