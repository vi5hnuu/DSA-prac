#include<iostream>
using namespace std;

void circularListLength(Node *head){
  if(!head)
    return;

  Node *temp=head;
  do{
    cout<<temp->data<<" ";
    temp=temp->next;
  }while(temp!=head);
}