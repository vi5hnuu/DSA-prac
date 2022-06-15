#include<iostream>
using namespace std;


//reverse first node and call for rest
Node *reverseList(Node *head,Node *&prev){
    if(!head) 
        return NULL;

    Node *next=head->next;
    head->next=prev;
    prev=head;
    reverseList(next,prev);
    return prev;
}
//or
Node *reverseList(Node *head,Node *prev){//prev is passed by non-ref
    if(!head) 
      return prev;

    Node *next=head->next;
    head->next=prev;
    return reverseList(next,head);
}

Node *reverseList(Node *head){
  Node *pre=NULL;
  return reverseList(head,pre);
}

////////////////////////////////////
//reverse rest and then attach rest with head
Node *reverseList(Node *head){
  if(!head || !head->next)
    return head;
  
  Node *rest_head=reverseList(head->next);
  Node *rest_tail=head->next;
  rest_tail->next=head;
  head->next=NULL;
  return rest_head;
}