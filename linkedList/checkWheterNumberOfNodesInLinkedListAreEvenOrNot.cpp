#include<iostream>
using namespace std;

/*
int isLengthEvenOrOdd(struct Node* head)
{
     int count=0;
     while(head){
         count++;
         head=head->next;
     }
     return (count&1) ? 1 : 0;
}//0 true,1 false
*/

// bool evenOdd(Node *head){
//   if(!head)
//     return true;
  
//   Node *fast=head->next;//2nd node
//   while(fast){
//     if(fast->next && !fast->next->next)
//       return false;
//     if(fast->next)
//     fast=fast->next->next;
//     else 
//       fast=NULL;
//   }
//   return true;
// }

bool evenOdd(Node *head){
  if(!head)
    return true;
  
  Node *fast=head;
  while(fast && fast->next){
      fast=fast->next->next;
  }
  if(!fast)
    return true;
  else 
    return false;
}