// { Driver Code Starts
#include<iostream>

#include<bits/stdc++.h>
using namespace std;

/* Link list Node */
struct Node
{
    int data;
    struct Node *next;
    Node(int x)
    {
        data = x;
        next = NULL;
    }
};

int intersectPoint(struct Node* head1, struct Node* head2);

Node* inputList(int size)
{
    if(size==0) return NULL;
    
    int val;
    cin>> val;
    
    Node *head = new Node(val);
    Node *tail = head;
    
    for(int i=0; i<size-1; i++)
    {
        cin>>val;
        tail->next = new Node(val);
        tail = tail->next;
    }
    
    return head;
}

/* Driver program to test above function*/
int main()
{
    int T,n1,n2,n3;

    cin>>T;
    while(T--)
    {
        cin>>n1>>n2>>n3;
        
        Node* head1 = inputList(n1);
        Node* head2 = inputList(n2);
        Node* common = inputList(n3);
        
        Node* temp = head1;
        while(temp!=NULL && temp->next != NULL)
            temp = temp->next;
        if(temp!=NULL) temp->next = common;
        
        temp = head2;
        while(temp!=NULL && temp->next != NULL)
            temp = temp->next;
        if(temp!=NULL) temp->next = common;
        
        cout << intersectPoint(head1, head2) << endl;
    }
    return 0;
}

// } Driver Code Ends


/* Linked List Node
struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
}; */

//Function to find intersection point in Y shaped Linked Lists.

/*
//TLE
int intersectPoint(Node* head1, Node* head2)
{
     unordered_set<Node *> nodes;
        unordered_set<Node *>::iterator itr;
        while(head1){
            nodes.insert(head1);
            head1=head1->next;
        }
        while(head2){
            if(nodes.find(head2)!=nodes.end()){
                return head2->data;
            }
            head2=head2->next;
        }
        return -1;
}
*/

int intersectPoint(Node* head1, Node* head2)
{
    Node *temp1=head1,*temp2=head2;
    int count1=0,count2=0;
    while(temp1 || temp2){
        if(temp1){
            count1++;
            temp1=temp1->next;
        }
        if(temp2){
            count2++;
            temp2=temp2->next;
        }
    }
    if(count1>=count2){
        int c=count1-count2;
        while(c>0){
            head1=head1->next;
            c--;
        }
    }
    else{
        int c=count2-count1;
        while(c>0){
            head2=head2->next;
            c--;
        }
    }
    while(head1!=head2){
        head1=head1->next;
        head2=head2->next;
    }
    return head1->data;
    
}
