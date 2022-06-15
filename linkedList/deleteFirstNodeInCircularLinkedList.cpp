#include<iostream>
using namespace std;

void deleteFirstNode(Node *&head){
  if(!head){
    return;
  }

  if(head->next==head){
    delete head;
    return;
  }

  Node *temp=head;
  while(temp->next!=head){
    temp=temp->next;
  }
  Node *newhead=head->next;
  delete temp->next;
  temp->next=newhead;
  head=newhead;
}

void deleteFirstNode(Node *&head){//O(1)
  if(!head){
    return;
  }

  if(head->next==head){
    delete head;
    head=NULL;
    return;
  }

  head->data=head->next->data;
  Node *temp=head->next;
  head->next=temp->next;
  delete temp;
}