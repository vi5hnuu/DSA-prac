// { Driver Code Starts
#include<bits/stdc++.h>
using namespace std;


struct node
{
    int data;
    struct node* next;
    
    node(int x){
        data = x;
        next = NULL;
    }
    
};

/* Function to print linked list */
void printList(struct node *node)
{
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}


 // } Driver Code Ends
/*
  Reverse a linked list
  The input list will have at least one element  
  Return the node which points to the head of the new LinkedList
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

/*
class Solution
{
    private:
    void printList(node *first,node *second){
        if(!first)
            return;
        while(first){
            cout<<first->data<<" ";
            first=first->next;
        }
        cout<<endl;
    }
    pair<node*,node*> reverseList(node *head,int k)
    {
        node *curr=head;
        node *prev=NULL;
        while(curr && k>0){
            k--;
            node *next=curr->next;
            curr->next=prev;
            prev=curr;
            curr=next;
        }
        return {prev,curr};//prev is newHead,curr is next of this new head
    }
    public:
    struct node *reverse (struct node *head, int k){ 
            node *first=head;
            node *newHead=NULL;
            node *prev=NULL;
            node *hd=head;
            pair<node *,node *> firstGrp=reverseList(hd,k);
            //printList(firstGrp.first,firstGrp.second);
            newHead=firstGrp.first;
            hd=firstGrp.second;
            
            while(hd){
                pair<node *,node *> secondGrp=reverseList(hd,k);
                first->next=secondGrp.first;
                first=hd;
                hd=secondGrp.second;
            }
          return newHead;  
    }
};
*/

/*
//recursive
class Solution
{
    public:
    struct node *reverse (struct node *head, int k){ 
        if(!head)
          return NULL;   
        node *curr=head;
        node *firstNode=head;
        node *prev=NULL;
        int count=0;
        while(curr && count<k){
            node *next=curr->next;
            curr->next=prev;
            prev=curr;
            curr=next;
            count++;
        }
        firstNode->next=reverse(curr,k);
        return prev;
    }
};
*/
class Solution
{
    public:
    struct node *reverse (struct node *head, int k){ 
        if(!head)
          return NULL;   
        node *curr=head;
        node *newHead=NULL;
        node *firstNode=head;
        while(curr){
            node *prev=NULL;
            int count=0;
            node *temp=curr;
            while(curr && count<k){
                node *next=curr->next;
                curr->next=prev;
                prev=curr;
                curr=next;
                count++;
            }
            if(!newHead){
                newHead=prev;
            }else{
                firstNode->next=prev;
                firstNode=temp;
            }
        }
        return newHead;
    }
};
/*
reverse two groups at at time and merge them to single after reverse
in next loop take next two group and merge them and add them to result of last list
if only one group is there reverse and add to result
*/


// { Driver Code Starts.

/* Drier program to test above function*/
int main(void)
{
    int t;
    cin>>t;
     
    while(t--)
    {
        struct node* head = NULL;
        struct node* temp = NULL;
        int n;
        cin >> n;
         
        for(int i=0 ; i<n ; i++)
        {
            int value;
            cin >> value;
            if(i == 0)
            {
                head = new node(value);
                temp = head;
            }
            else
            {
                temp->next = new node(value);
                temp = temp->next;
            }
        }
        
        int k;
        cin>>k;
        
        Solution ob;
        head = ob.reverse(head, k);
        printList(head);
    }
     
    return(0);
}

  // } Driver Code Ends