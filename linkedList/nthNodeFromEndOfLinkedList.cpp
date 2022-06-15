// { Driver Code Starts
// C program to find n'th Node in linked list
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

/* Link list Node */
struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
};


/* Function to get the nth node from the last of a linked list*/
int getNthFromLast(struct Node* head, int n);



/* Driver program to test above function*/
int main()
{
  int T,i,n,l,k;

    cin>>T;

    while(T--){
    struct Node *head = NULL,  *tail = NULL;

        cin>>n>>k;
        int firstdata;
        cin>>firstdata;
        head = new Node(firstdata);
        tail = head;
        for(i=1;i<n;i++)
        {
            cin>>l;
            tail->next = new Node(l);
            tail = tail->next;
        }

    cout<<getNthFromLast(head, k)<<endl;
    }
    return 0;
}// } Driver Code Ends


/* struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
};
*/

/*
//Function to find the data of nth node from the end of a linked list.
int lenOfLinkedList(Node *head){
    int len=0;
    while(head){
        len++;
        head=head->next;
    }
    return len;
}


//1 2 3 4 5 6 7 8 9 10
//3rd node from last
//jump = > 10-3 => 7


int getNthFromLast(Node *head, int n)
{
       if(!head)
        return -1;
       int len=lenOfLinkedList(head);
       if(len<n)
            return -1;
        int jump=len-n;
        while(jump>0){
            jump--;
            head=head->next;
        }
    return head->data;
}
*/

int getNthFromLast(Node *head, int n)
{
       if(!head)
        return -1;
       
       Node *first=head,*second=head;
       while(second && n>0){
        second=second->next;
        n--;   
       }
       if(n!=0)
        return -1;
       while(second){
           first=first->next;
           second=second->next;
       } 
       return first->data;
}








