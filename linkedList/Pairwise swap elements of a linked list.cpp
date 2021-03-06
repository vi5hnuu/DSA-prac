// { Driver Code Starts
#include <bits/stdc++.h> 
using namespace std; 

struct Node
{
    int data;
    struct Node* next;
    
    Node(int x){
        data = x;
        next = NULL;
    }
};


 // } Driver Code Ends
/*
  Pairwise swap a linked list
  The input list will have at least one element
  node is defined as

struct node
{
    int data;
    struct node* next;

    node(int x){
        data = x;
        next = NULL;
    }

}*head;
*/

class Solution
{
    public:
    /*
    Node* pairWiseSwap(struct Node* head){
        
        //Constraints:
        //1 ≤ N ≤ 103
        
        Node *newHead=NULL;
        Node *rest=head;
        Node *prev=NULL;
       while(rest){
           Node *first=rest;
           Node *second=rest->next;
           first->next=NULL;
           
           if(second){
               rest=second->next;
               second->next=first;
           }
           else{
               rest=NULL;
           }
            if(prev){
                prev->next=second ? second : first;
            }
            prev=first;
            if(!newHead){
                newHead=second ? second : first;
            }
       }
       return newHead;
    }
    */
    
    Node* pairWiseSwap(struct Node* head){
        
        //Constraints:
        //1 ≤ N ≤ 103
        if(!head)
            return NULL;
        Node *first=head;
        Node *second=head->next;
        Node *next=NULL;
        
        if(second){
            next=second->next;
            second->next=first;
        }
        else{
            next=NULL;
        }
            first->next=pairWiseSwap(next);
        return second ? second : first;
            
    }   
};

// { Driver Code Starts.

void printList(Node* node) 
{ 
	while (node != NULL) { 
		cout << node->data <<" "; 
		node = node->next; 
	}  
	cout<<"\n";
}

int main() 
{ 
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;

		int data;
		cin>>data;
		struct Node *head = new Node(data);
		struct Node *tail = head;
		map<Node*, int> mp;
		mp[head] = head->data;
		for (int i = 0; i<n-1; ++i)
		{
			cin>>data;
			tail->next = new Node(data);
			tail = tail->next;
			mp[tail] = tail->data;
		}
		struct Node *failure = new Node(-1);
		Solution ob;
		head = ob.pairWiseSwap(head);
		int flag = 0;
		struct Node *temp = head;
		while(temp){
		    if(mp[temp] != temp->data){
		        flag = 1;
		        break;
		    }
		    temp = temp->next;
		}
		if(flag)
		    printList(failure);
		else
		    printList(head);
	}
	return 0; 
}
  // } Driver Code Ends