#include<iostream>
using namespace std;


/*
zeroth index is always front
size tell the rear
*/
class Deque{
  private:
    int size,cap,*arr;
  public:
    Deque(int cap){
      this->cap=cap;
      size=0;
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

void Deque::insertFront(int data){
  if(size==0){
    arr[size++]=data;
  }else if(size<cap){
    for(int i=size;i>0;i--)
      arr[i]=arr[i-1];
    arr[0]=data;
    size++;
  }else{
    throw string("Deque full.");
  }
}
void Deque::insertBack(int data){
  if(size<cap){
    arr[size++]=data;
  }
  else{
    throw string("Deque full.");
  }
}

int Deque::deleteBack(){
  if(size>0){
    int x=arr[--size];
    return x;
  }else{
    throw string("Deque empty.");
  }
}

int Deque::deleteFront(){
  if(size==0){
    throw string("Deque empty.");
  }

  int x=arr[0];
  for(int i=1;i<size;i++){
    arr[i-1]=arr[i];
  }
  size--;
  return x;
}

bool Deque::empty(){
  if(size==0)
    return true;
  return false;
}

void Deque::showDeque(){
  for(int i=0;i<size;i++){
      cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int Deque::getBack(){
  if(this->empty())
    throw string("Deque empty.");
  return arr[size-1];
}

int Deque::getFront(){
  if(this->empty())
    throw string("Deque empty.");
  return arr[0];
}

int main(){
  Deque d(10);
  d.showDeque();
  d.insertBack(10);
  d.insertBack(11);
  d.insertBack(12);
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
  d.showDeque();
  return 0;
}