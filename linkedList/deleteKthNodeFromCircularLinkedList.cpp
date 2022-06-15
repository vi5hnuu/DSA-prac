#include<iostream>
using namespace std;

//No. of nodes>=K

void deleteHead(Node *&head){//O(1)
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

void deleteKth(Node *&head,int k){
  if(!head)
    return;
  
  if(k==1){
    deleteHead(head);
    return;
  }
  Node *curr=head;
  for(int i=0;i<k-2;i++)
    curr=curr->next;

  Node *temp=curr->next;
  curr->next=temp->next;
  delete temp;
}