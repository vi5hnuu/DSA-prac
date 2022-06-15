#include<iostream>
using namespace std;

void printNodeData(Node *head){
  if(!head)
    return;
  cout<<(head->data)<<" ";
  printNodeData(head->next);
}