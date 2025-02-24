Given the head of a singly linked list and two integers left and right where left <= right, reverse the nodes of the list from position left to position right, and return the reversed list.

 

Example 1:


Input: head = [1,2,3,4,5], left = 2, right = 4
Output: [1,4,3,2,5]
Example 2:

Input: head = [5], left = 1, right = 1
Output: [5]
 

Constraints:

The number of nodes in the list is n.
1 <= n <= 500
-500 <= Node.val <= 500
1 <= left <= right <= n
 

Follow up: Could you do it in one pass?


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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* revStart= (left==1 ? nullptr : head) ;//node before rev LL start
        
        int total=right-left+1;
        while(revStart && left-2>0) {
            revStart=revStart->next;
            left--;
        };

        ListNode* rest= revStart ? revStart->next : head;

        ListNode* fn=rest; //first node of to be rev ll

        ListNode* rv=nullptr;
        while(rest && total--){
            ListNode* temp=rest;
            rest=rest->next;
            temp->next=rv;
            rv=temp;
        }

        fn->next=rest;
        if(revStart) revStart->next=rv;
        
        return revStart ? head : rv;
    }
};