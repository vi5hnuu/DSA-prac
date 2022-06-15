#include<iostream>
using namespace std;

void insertAtBeg(Node *&head,int data){
  Node *newNode=new Node(data);
  newNode->next=newNode;

  if(!head){
    head=newNode;
    return;
  }

  Node *temp=head;
  while(temp->next!=head){
    temp=temp->next;
  }
  temp->next=newNode;
  newNode->next=head;
  head=newNode;
}

void insertAtBeg(Node *&head,int data){//O(1)
  Node *newNode=new Node(data);
  newNode->next=newNode;

  if(!head){
    head=newNode;
    return;
  }

  newNode->next=head->next;
  head->next=newNode;
  swap(head->data,temp->data);
}