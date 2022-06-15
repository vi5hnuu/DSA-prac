#include<iostream>
using namespace std;

void insertAtEnd(Node *&head,int data){//O(N)
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
}

void insertAtEnd(Node *&head,int data){//O(1)
  Node *newNode=new Node(data);
  newNode->next=newNode;

  if(!head){
    head=newNode;
    return;
  }

  newNode->next=head->next;
  head->next=newNode;
  swap(head->data,temp->data);
  head=head->next;
}