// { Driver Code Starts
#include <bits/stdc++.h>

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

struct Node *start = NULL;


 // } Driver Code Ends
/*
 
  Node is defined as
  struct Node {
    int data;
    struct Node *next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

*/
class Solution
{
    public:
    //Function to sort a linked list of 0s, 1s and 2s.
    Node* segregate(Node *head) {
        if(!head)
            return NULL;
        
        Node *zero=NULL,*zTail=NULL;
        Node *one=NULL,*oTail=NULL;
        Node *two=NULL,*tTail=NULL;
        while(head){
            if(head->data==0){
                if(!zero){
                    zero=zTail=head;
                }else{
                    zTail->next=head;
                    zTail=zTail->next;
                }
            }
            else if(head->data==1){
                if(!one){
                    one=oTail=head;
                }else{
                    oTail->next=head;
                    oTail=oTail->next;
                }
            }
            else{
                if(!two){
                    two=tTail=head;
                }else{
                    tTail->next=head;
                    tTail=tTail->next;
                }
            }
                head=head->next;
        }
        
        if(zero)
            zTail->next=NULL;
        if(one)
            oTail->next=NULL;
        if(two)
            tTail->next=NULL;
        
        if(zero){
            if(one){
                zTail->next=one;
                oTail->next=two;
            }
            else{
                zTail->next=two;
            }
                return zero;
        }
        else{
            if(one){
                oTail->next=two;
                return oTail;
            }
            else{
                return two;
            }
        }
    }
};


// { Driver Code Starts.

// Function to sort a linked list of 0s, 1s and 2s
void printList(struct Node *Node) {
    while (Node != NULL) {
        printf("%d ", Node->data);
        Node = Node->next;
    }
    printf("\n");
}

/* Drier program to test above function*/
void insert(int n1) {
    int n, value, i;
    // scanf("%d",&n);
    n = n1;
    struct Node *temp;
    for (i = 0; i < n; i++) {
        scanf("%d", &value);

        if (i == 0) {
            start = new Node(value);
            temp = start;
            continue;
        } else {
            temp->next = new Node(value);
            temp = temp->next;
            temp->next = NULL;
        }
    }
}

int main() {

    int n;

    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        insert(n);
        Solution ob;
        struct Node *newHead = ob.segregate(start);
        printList(newHead);
    }

    return 0;
}  // } Driver Code Ends