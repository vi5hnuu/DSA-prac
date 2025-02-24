Given the head of a linked list, remove the nth node from the end of the list and return its head.

 

Example 1:


Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
Example 2:

Input: head = [1], n = 1
Output: []
Example 3:

Input: head = [1,2], n = 1
Output: [1]
 

Constraints:

The number of nodes in the list is sz.
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz
 

Follow up: Could you do this in one pass?


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        int len=lengthLL(head);
        
        ListNode* clone=head;
        if(n==len){
            head=head->next;
            delete clone;
            return head;
        }
        int mv=len-1-n;

        while(mv){
            mv--;
            clone=clone->next;
        }
        ListNode* del=clone->next;
        clone->next=del->next;
        delete del;
        return head;
    }
private:
    long lengthLL(ListNode* head){
        int len=0;
        while(head){
            len++;
            head=head->next;
        }
        return len;
    }
};


// using gap-between two pointers technique

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        //using gap+1 gap between two pointer
        ListNode* x=head;
        ListNode* y=head;
        for(int i=1;i<=n;i++){
            y=y->next;
        }

        if(!y){//first node
            head=head->next;
            delete x;
            return head;
        }

        while(y->next){
            x=x->next;
            y=y->next;
        }

        ListNode* del=x->next;
        x->next=del->next;
        delete del;
        return head;
    }
};