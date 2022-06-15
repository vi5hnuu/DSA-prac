#include<iostream>
using namespace std;

void deleteLastNode(Node *&head,int data){
  if(!head){
    return;
  }
  if(head->next==head){
    delete head;
    head=NULL;
  }

  Node *temp=head;
  while(temp->next->next!=head){
    temp=temp->next;
  }
  delete temp->next;
  temp->next=head;
}