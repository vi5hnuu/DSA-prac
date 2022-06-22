#include<iostream>
using namespace std;


/*
circular Deque
*/
class Deque{
  private:
    int front,rear,cap,*arr;
  public:
    Deque(int cap){
      this->cap=cap;
      front=rear=-1;
      arr=new int[cap];
    }
  void insertFront(int data);
  void insertBack(int data);
  int deleteFront();
  int deleteBack();
  bool empty();
  int getFront();
  int getBack();
  void showDeque();
};
void Deque::showDeque(){
  if(front==-1)
    return;
  if(front<=rear){
    for(int i=front;i<=rear;i++){
      cout<<arr[i]<<" ";
    }
  }else{
    for(int i=front;i<cap;i++){
      cout<<arr[i]<<" ";
    }
    for(int i=0;i<=rear;i++){
      cout<<arr[i]<<" ";
    }
  }
  cout<<endl;
}

void Deque::insertFront(int data){
  if(front==-1){
    arr[++front]=data;
    rear=front;
  }
  else if((front-1+cap)%cap==rear){
      throw string("Deque full.");
  }
  else{
    front=(front-1+cap)%cap;
    arr[front]=data;
  }
}
void Deque::insertBack(int data){
  if(front==-1){
    arr[++front]=data;
    rear=front;
  }
  else if((rear+1)%cap==front)
    throw string("Deque full.");
  else
  arr[(++rear)%cap]=data;
}

int Deque::deleteBack(){
    if(front==-1)
        throw string("Deque empty.");
    if(front==rear){
      int x=arr[front];
      front=rear=-1;
      return x;
    }else{
      int x=arr[rear];
      rear=(rear-1+cap)%cap;
      return x;
    }
}

int Deque::deleteFront(){
    if(front==-1)
      throw string("Deque empty.");
    if(front==rear){
      int x=arr[front];
      front=rear=-1;
      return x;
    }else{
      int x=arr[front];
      front=(front+1)%cap;
    }
}

bool Deque::empty(){
  if(front==-1)
      return true;
  return false;
}

int Deque::getBack(){
    if(front!=-1)
      return arr[rear];
    else
      throw string("Deque empty.");
}

int Deque::getFront(){
    if(front!=-1)
      return arr[front];
    else
      throw string("Deque empty.");
}

int main(){
  Deque d(10);
  d.showDeque();
  d.insertBack(10);
  d.insertBack(11);
  d.insertBack(12);
  d.showDeque();
  d.insertFront(4);
  d.insertFront(3);
  d.insertFront(2);
  d.insertFront(1);
  d.showDeque();
  d.deleteBack();
  d.deleteBack();
  d.showDeque();
  d.deleteFront();
  d.deleteFront();
  d.deleteFront();
  d.showDeque();
  d.insertBack(5);
  d.insertBack(6);
  d.insertBack(7);
  d.insertBack(8);
  d.insertBack(9);
  d.insertBack(15);
  d.insertBack(16);
  d.insertBack(17);
  d.showDeque();
  return 0;
}