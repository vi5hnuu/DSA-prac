//Not working

#include<iostream>
using namespace std;

class DLL{
  private:
    struct Node{
      int data;
      Node *ptrDiff;//xor of prev and next pointer
      Node(int data){
          this->data=data;
          ptrDiff=NULL;
      }
    };
    Node *head;
  public:
  DLL(){
    this->head=NULL;
  }
  void insertAtEnd(int data){
    Node *newNode=new Node(data);
    if(head){
      head=newNode;
      return;
    }
    Node *temp=head->ptrDiff;
    while(temp){
      temp=((temp->ptrDiff)->ptrDiff)^temp;
    }
    temp->ptrDiff=(temp->ptrDiff)^newNode;
    newNode->ptrDiff=temp^NULL;
  }
  void display(){
    if(!head){
      cout<<"List Empty.\n";
    }
    Node *temp=head->ptrDiff;
    while(temp){
      cout<<temp->data<<" ";
      temp=((temp->ptrDiff)->ptrDiff)^temp;
    }
  }
};

int main(){
  DLL obj;
  obj.insertAtEnd(10);
  obj.insertAtEnd(11);
  obj.insertAtEnd(12);
  obj.insertAtEnd(13);
  obj.insertAtEnd(14);
  obj.insertAtEnd(15);
  obj.display();

  return 0;
}