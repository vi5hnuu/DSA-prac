#include<iostream>
using namespace std;

int circularListLength(Node *head){
  if(!head)
    return 0;
  
  int count=0;
  Node *temp=head;
  do{
    count++;
    temp=temp->next;
  }while(temp!=head);
  return count;
}