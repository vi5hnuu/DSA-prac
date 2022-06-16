// { Driver Code Starts
// A recursive program to add two linked lists 

#include <iostream> 
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

void append(Node** head_ref, Node **tail_ref, int new_data)
{
    struct Node* new_node = new Node(new_data);
    
    if (*head_ref == NULL)
        *head_ref = new_node;
    else
        (*tail_ref)->next = new_node;
    *tail_ref = new_node;
}

void push(Node** head_ref, int new_data) 
{ 
    /* allocate node */
    Node* new_node = new Node(new_data); 
  
    /* link the old list off the new node */
    new_node->next = (*head_ref); 
  
    /* move the head to point to the new node */
    (*head_ref)    = new_node; 
} 

/* A utility function to print linked list */
void printList(Node *node) 
{ 
	while (node != NULL) 
	{ 
		cout<<node->data<<" ";
		node = node->next; 
	} 
	cout<<endl;
} 

// A utility function to swap two pointers 
void swapPointer( Node** a, Node** b ) 
{ 
	Node* t = *a; 
	*a = *b; 
	*b = t; 
} 

Node* addSameSize(Node* head1, Node* head2, int* carry) ;

void addCarryToRemaining(Node* head1, Node* curr, int* carry, Node** result) ;


// The main function that adds two linked lists represented by head1 and head2. 
// The sum of two lists is stored in a list referred by result 
void addList(Node* head1, Node* head2, int size1, int size2, Node** result) 
{ 
	Node *cur; 
    if (head1 == NULL) { 
		*result = head2; 
		return; 
	}

	if (head2 == NULL) 
	{ 
		*result = head1; 
		return; 
	}
	
	int carry = 0; 

	if (size1 == size2) 
		*result = addSameSize(head1, head2, &carry); 
    else
	{ 
		int diff = abs(size1 - size2); 

		if (size1 < size2) 
			swapPointer(&head1, &head2); 

		for (cur = head1; diff--; cur = cur->next);
		
        *result = addSameSize(cur, head2, &carry); 
        
		addCarryToRemaining(head1, cur, &carry, result); 
	} 

	if (carry) 
		push(result, carry); 
} 

// Driver program to test above functions 
int main() 
{ 
	int T;
	cin>>T;
	while(T--){
	    Node *head1 = NULL, *tail1 = NULL;
	    Node *head2 = NULL, *tail2 = NULL;
	    Node *result = NULL; 
        int size1, size2;
        cin>>size1>>size2;
        
        int temp;
        for(int i = 1; i<=size1; i++){
            cin>>temp;
            append(&head1, &tail1, temp);
        }
        for(int i = 1; i<=size2; i++){
            cin>>temp;
            append(&head2, &tail2, temp);
        }
        
        addList(head1, head2, size1, size2, &result); 
        printList(result); 
	}
    return 0; 
} 
// } Driver Code Ends


//User function Template for C++

//Function which adds two linked lists of same size.
//Function which adds two linked lists of same size represented by head1  
//and head2 and returns head of the resultant linked list. Carry
//is propagated while returning from the recursion
Node *reverse(Node *head){
    Node *cur=head;
    Node *prev=NULL;
    while(cur){
        Node *next=cur->next;
        cur->next=prev;
        prev=cur;
        cur=next;
    }
    return prev;
}

Node* addSameSize(Node* head1, Node* head2, int* carry) 
{ 
	//we are give head1 and head2 linked list of same size
	Node *revHead1=reverse(head1);
	Node *revHead2=reverse(head2);
	Node *sumList=NULL;
	*carry=0;
	while(revHead1 && revHead2){
	    int sum=revHead1->data+revHead2->data+*carry;
	        int temp=sum;
	        sum=sum%10;
	        *carry=temp/10;
	    Node *newNode=new Node(sum);
        //cout<<"Sum :"<<sum<<" carry : "<<*carry<<endl;
        newNode->next=sumList;
        sumList=newNode;
        
        revHead1=revHead1->next;
        revHead2=revHead2->next;
	}https://practice.geeksforgeeks.org/problems/add-two-numbers-represented-by-linked-list/0/?track=DSASP-LinkedList&batchId=154#
    return sumList;
} 


//This function is called after the smaller list is added to the sublist of 
//bigger list of same size. Once the right sublist is added, the carry
//must be added to left side of larger list to get the final result.
void addCarryToRemaining(Node* head1, Node* curr, int* carry, Node** sumList) 
{ 
    Node *ptr = reverse(head1);
	ptr = curr->next;
	
	Node *res = *(sumList);
	int sum;
	while(ptr) {
	    sum = ptr->data + *carry;
	    *carry = sum/10;
	    sum = sum%10;
	    
	    Node *temp = new Node(sum);
	    temp->next = res;
	    res = temp;
	    
	    ptr = ptr->next;
	}
	
	if(*carry) {
	    Node *temp = new Node(*carry);
	    temp->next = res;
	    res = temp;
	    *carry = 0;
	}
	
	*sumList = res;
    
}
