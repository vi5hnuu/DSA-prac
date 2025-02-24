Given the head of a singly linked list, return true if it is a 
palindrome
 or false otherwise.

 

Example 1:


Input: head = [1,2,2,1]
Output: true
Example 2:


Input: head = [1,2]
Output: false
 

Constraints:

The number of nodes in the list is in the range [1, 105].
0 <= Node.val <= 9
 

Follow up: Could you do it in O(n) time and O(1) space?


//////////////////////////////////////////////////


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
    bool isPalindrome(ListNode* head) {
        ListNode* turtle=head,*rabbit=head;
        
        while(rabbit->next && rabbit->next->next){
            turtle=turtle->next;
            rabbit=rabbit->next->next;
        }

        rabbit=turtle->next;
        turtle=head;

        stack<int> stck;
        while(rabbit){
            stck.push(rabbit->val);
            rabbit=rabbit->next;
        }

        //compare turtle and rev rabbit path
        while(turtle && !stck.empty()){
            if(turtle->val!=stck.top()) return false;
            turtle=turtle->next;
            stck.pop();
        }
        return true;
    }
};



//////////////////////////////////////////////////



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
    bool isPalindrome(ListNode* head) {//O(3N/2)
        ListNode* turtle=head,*rabbit=head;

        while(rabbit->next && rabbit->next->next){ //O(N/2)
            turtle=turtle->next;
            rabbit=rabbit->next->next;
        }

        rabbit=turtle->next;
        turtle=head;

        //reverse rabbit
        ListNode* rv=nullptr;
        while(rabbit){//O(N/2)
            ListNode* temp=rabbit;
            rabbit=rabbit->next;
            temp->next=rv;
            rv=temp;
        }

        //compare turtle and rev rabbit path
        while(turtle && rv){//O(N/2)
            if(turtle->val!=rv->val) return false;
            turtle=turtle->next;
            rv=rv->next;
        }
        return true;
    }
};