struct Node* reverseList(struct Node *head)
    {
        if(!head || !head->next)
            return head;

        //break at first node
        //1->2->3-4->5
        //newHead=1->null
        //nextToTake=2->3->4->5
        //succ=3->4->5
        Node *newHead=head;
        Node *nextToTake=head->next;
        newHead->next=NULL;
        Node *succ=nextToTake->next;
        while(nextToTake){
            nextToTake->next=newHead;
            newHead=nextToTake;
            nextToTake=succ;
            if(nextToTake)
            succ=nextToTake->next;
        }
        return newHead;
    }


struct  Node* reverseList(struct Node *head)
    {
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