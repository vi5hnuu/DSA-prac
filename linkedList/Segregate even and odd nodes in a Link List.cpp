// { Driver Code Starts
//Initial template for C++

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
void printList(Node* node) 
{ 
    while (node != NULL) { 
        cout << node->data <<" "; 
        node = node->next; 
    }  
    cout<<"\n";
} 


 // } Driver Code Ends
//User function template for C++

/*
struct Node
{
    int data;
    struct Node* next;
    
    Node(int x){
        data = x;
        next = NULL;
    }
};
*/
class Solution{
public:
    Node* divide(int N, Node *head){
        Node *odd=NULL,*oddTail=NULL;
        Node *even=NULL,*evenTail=NULL;
        while(head){
            if(head->data&1){//odd
                if(!odd){
                    odd=head;
                    head=head->next;
                    odd->next=NULL;
                    oddTail=odd;
                }else{
                    oddTail->next=head;
                    head=head->next;
                    oddTail=oddTail->next;
                    oddTail->next=NULL;
                }
            }else{//even
                 if(!even){
                    even=head;
                    head=head->next;
                    even->next=NULL;
                    evenTail=even;
                }else{
                    evenTail->next=head;
                    head=head->next;
                    evenTail=evenTail->next;
                    evenTail->next=NULL;
                }
            }
        }
        if(evenTail){
            evenTail->next=odd;
            return even;
        }
        else
            return odd;
        
        return even;
    }
};

// { Driver Code Starts.

int main() {
    //code
    int t;
    cin>>t;
    while(t--){
        int N;
        cin>>N;
        int data;
        cin>>data;
        struct Node *head = new Node(data);
        struct Node *tail = head;
        for (int i = 0; i < N-1; ++i)
        {
            cin>>data;
            tail->next = new Node(data);
            tail = tail->next;
        }
        
        Solution ob;
        Node *ans = ob.divide(N, head);
        printList(ans); 
    }
    return 0;
}
  // } Driver Code Ends