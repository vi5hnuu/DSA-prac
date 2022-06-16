#include<iostream>
using namespace std;

void print(Node *head){
  if(!head)
    return;
    print(head->next);
    cout<<head->data<<" ";
}