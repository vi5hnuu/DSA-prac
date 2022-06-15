class Solution
{
    public:
    //Function to remove a loop in the linked list.
    Node* firstNode(Node* head)
    {
       Node *slow=head,*fast=head;
       while(fast && fast->next){
           slow=slow->next;
           fast=fast->next->next;
           if(slow==fast)
                break;
       }
       if(!fast || !fast->next)
        return;
        
        slow=head;
        while(slow!=fast){
            slow=slow->next;
            fast=fast->next;
        }
       return slow; 
    }
};

