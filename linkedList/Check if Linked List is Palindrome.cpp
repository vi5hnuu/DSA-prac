// { Driver Code Starts
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>
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




 // } Driver Code Ends
/*
struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
};
*/
#include<vector>
class Solution{
  public:
    //Function to check whether the list is palindrome.
    /*
    bool isPalindrome(Node *head)
    {
        string s;
        while(head){
            s+=to_string(head->data);//what if data in not convertible to int but can only be compared
            //and what if it is convertible to string but very large
            head=head->next;
        };
        for(int i=0,len=s.length();i<len/2;i++){
            if(s[i]!=s[len-1-i])
                return false;
        }
        return true;
    }
    */
    /*
    bool isPalindrome(Node *head)
    {
        vector<Node *> res;
        while(head){
            res.push_back(head);
            head=head->next;
        };
        for(int i=0,len=res.size();i<len/2;i++){
            if(res[i]->data!=res[len-1-i]->data)
                return false;
        }
        return true;
    }
    */
    
    /////////////////
    /*
    int lenOfLinkedList(Node *head){
        int len=0;
        while(head){
            len++;
            head=head->next;
        }
        return len;
    }
    Node *reverse(Node *head){
        Node *curr=head;
        Node *prev=NULL;
        while(curr){
            Node *next=curr->next;
            curr->next=prev;
            prev=curr;
            curr=next;
        }
        return prev;
    }
    void print(Node *head){
        while(head){
            cout<<head->data<<" ";
            head=head->next;
        }
    }
    bool isPalindrome(Node *head)
    {
        int len=lenOfLinkedList(head);
        int jump=len/2;
        Node *head1=head;
        while(jump>0){
            jump--;
            head=head->next;
        }
        Node *head2=reverse(head);
        //Note head1 last node is not set to null but still this works becase of cond. in while claus.
        //proof
        //print(head1);examine this print result
        while(head1 && head2){
            if(head1->data!=head2->data)
                return false;
            
            head1=head1->next;
            head2=head2->next;
        }
        return true;
    }
    */
    
    //optimized
    Node* mid(Node *head){
        Node *fast=head,*slow=head;
        while(fast && fast->next){
            slow=slow->next;
            fast=fast->next->next;
        }
        return slow;
    }
    Node *reverse(Node *head){
        Node *curr=head;
        Node *prev=NULL;
        while(curr){
            Node *next=curr->next;
            curr->next=prev;
            prev=curr;
            curr=next;
        }
        return prev;
    }
    void print(Node *head){
        while(head){
            cout<<head->data<<" ";
            head=head->next;
        }
    }
    bool isPalindrome(Node *head)
    {
        
        Node *head1=head;
        Node *midNode=mid(head);
        Node *head2=reverse(midNode);
        //Note head1 last node is not set to null but still this works becase of cond. in while claus.
        //can you guess what are two linked list in case of odd or even nodes
        //for off both have same length
        //for even nodes one linked list is bigger...........
        //print(head1);examine this print result
        while(head1 && head2){
            if(head1->data!=head2->data)
                return false;
            
            head1=head1->next;
            head2=head2->next;
        }
        return true;
    }
};



// { Driver Code Starts.
/* Driver program to test above function*/
int main()
{
  int T,i,n,l,firstdata;
    cin>>T;
    while(T--)
    {
        
        struct Node *head = NULL,  *tail = NULL;
        cin>>n;
        // taking first data of LL
        cin>>firstdata;
        head = new Node(firstdata);
        tail = head;
        // taking remaining data of LL
        for(i=1;i<n;i++)
        {
            cin>>l;
            tail->next = new Node(l);
            tail = tail->next;
        }
    Solution obj;
   	cout<<obj.isPalindrome(head)<<endl;
    }
    return 0;
}

  // } Driver Code Ends