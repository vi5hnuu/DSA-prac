You have a browser of one tab where you start on the homepage and you can visit another url, get back in the history number of steps or move forward in the history number of steps.

Implement the BrowserHistory class:

BrowserHistory(string homepage) Initializes the object with the homepage of the browser.
void visit(string url) Visits url from the current page. It clears up all the forward history.
string back(int steps) Move steps back in history. If you can only return x steps in the history and steps > x, you will return only x steps. Return the current url after moving back in history at most steps.
string forward(int steps) Move steps forward in history. If you can only forward x steps in the history and steps > x, you will forward only x steps. Return the current url after forwarding in history at most steps.
 

Example:

Input:
["BrowserHistory","visit","visit","visit","back","back","forward","visit","forward","back","back"]
[["leetcode.com"],["google.com"],["facebook.com"],["youtube.com"],[1],[1],[1],["linkedin.com"],[2],[2],[7]]
Output:
[null,null,null,null,"facebook.com","google.com","facebook.com",null,"linkedin.com","google.com","leetcode.com"]

Explanation:
BrowserHistory browserHistory = new BrowserHistory("leetcode.com");
browserHistory.visit("google.com");       // You are in "leetcode.com". Visit "google.com"
browserHistory.visit("facebook.com");     // You are in "google.com". Visit "facebook.com"
browserHistory.visit("youtube.com");      // You are in "facebook.com". Visit "youtube.com"
browserHistory.back(1);                   // You are in "youtube.com", move back to "facebook.com" return "facebook.com"
browserHistory.back(1);                   // You are in "facebook.com", move back to "google.com" return "google.com"
browserHistory.forward(1);                // You are in "google.com", move forward to "facebook.com" return "facebook.com"
browserHistory.visit("linkedin.com");     // You are in "facebook.com". Visit "linkedin.com"
browserHistory.forward(2);                // You are in "linkedin.com", you cannot move forward any steps.
browserHistory.back(2);                   // You are in "linkedin.com", move back two steps to "facebook.com" then to "google.com". return "google.com"
browserHistory.back(7);                   // You are in "google.com", you can move back only one step to "leetcode.com". return "leetcode.com"
 

Constraints:

1 <= homepage.length <= 20
1 <= url.length <= 20
1 <= steps <= 100
homepage and url consist of  '.' or lower case English letters.
At most 5000 calls will be made to visit, back, and forward.



class BrowserHistory {
private:
    class BrowserHistoryNode{
        public:
            string url;
            BrowserHistoryNode *next=nullptr,*prev=nullptr;
            BrowserHistoryNode(string url):url(url){
                this->next=this->prev=nullptr;
            };
            BrowserHistoryNode(string url,BrowserHistoryNode *next,BrowserHistoryNode *prev){
                this->url=url;
                this->next=next;
                this->prev=prev;
            };
    };
    BrowserHistory::BrowserHistoryNode *head=nullptr;
public:
    BrowserHistory(string homepage) {
        this->head=new BrowserHistoryNode(homepage);
    }
    ~BrowserHistory() {
        freeMemory(head);
    }
    
    void visit(string url) {
        freeMemory(head->next);
        head=head->next=new BrowserHistoryNode(url,nullptr,head);
    }
    
    string back(int steps) {
        while(head && head->prev && steps--){
            head=head->prev;
        }
        return head->url;
    }
    
    string forward(int steps) {
        while(head && head->next && steps--){
            head=head->next;
        }
        return head->url;
    }

    void freeMemory(BrowserHistoryNode *from){
        while(from){
            BrowserHistoryNode* temp=from;
            from=from->next;
            delete temp;
        }
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */














//////////////////////////////////////////////////////
/*
When comparing the two approaches in C++—clearing a stack until it's empty versus destroying an object and initializing it with another fresh object of the stack—the performance can vary based on several factors. Here's a detailed analysis:

Clearing a Stack Until Empty
Pros:

Control Over Each Element's Destruction: You have precise control over how each element is destructed, which might be necessary if the elements themselves have complex destructors.
Potentially Reusable Memory: If the stack's underlying container supports it, clearing the stack may allow for the reuse of allocated memory, avoiding the overhead of frequent allocations and deallocations.
Cons:

Loop Overhead: You need to repeatedly pop elements off the stack, which involves multiple calls to pop() and top().
Destructor Calls: Each element's destructor is called individually, which could be slower if the destructors are non-trivial.
Destroying the Object and Initializing a Fresh One
Pros:

Single Operation: Destroying the stack object and creating a new one can be a single, straightforward operation, especially if the stack has no complex destructor.
Clear and Simple: This approach can be simpler and more readable in code, as it doesn't involve manually clearing the stack.
Allocator Efficiency: Creating a new stack might be more efficient if the allocator is optimized for this pattern, avoiding the overhead of repeatedly deallocating elements.
Cons:

Allocation Overhead: If the stack's underlying container (e.g., std::vector) frequently reallocates memory, this approach might incur more allocation and deallocation overhead.
Non-trivial Destructor: If the stack has a non-trivial destructor, destroying and reinitializing the stack might be more costly.
Performance Comparison
Small, Simple Objects:

For stacks holding small, simple objects (e.g., int, char), the difference might be negligible.
Destroying and reinitializing might be slightly faster due to the absence of a loop.
Large, Complex Objects:

For stacks holding large or complex objects with significant destructors, clearing the stack might allow for more controlled and potentially optimized destruction.
However, if the stack itself has a heavy destructor, reinitializing might still be beneficial.
Example Code Comparison
Clearing Until Empty
cpp
Copy code
std::stack<int> s;
// Assume s is populated with elements
while (!s.empty()) {
    s.pop();
}
Destroying and Initializing Fresh
cpp
Copy code
std::stack<int> s;
// Assume s is populated with elements
s = std::stack<int>(); // Creates a new, empty stack
Conclusion
For Simple Use Cases: Destroying and initializing a fresh stack object is often simpler and might be slightly faster due to reduced function call overhead.
For Complex Destruction Needs: Clearing the stack manually can provide more control over the destruction process and might be necessary if the objects held by the stack require specific cleanup actions.
In practice, the performance difference might not be significant unless you're dealing with very large stacks or objects with complex destructors. Profiling in your specific context is the best way to determine the most efficient approach.
*/

class BrowserHistory {
private:
    stack<string> curr,rest;
public:
    BrowserHistory(string homepage) {
        curr.push(homepage);
    }

    void visit(string url) {
        clear(rest);
        curr.push(url);
    }
    
    string back(int steps) {
        while(curr.size()>1 && steps--){
            rest.push(curr.top());
            curr.pop();
        }
        return curr.top();
    }
    
    string forward(int steps) {
        while(!rest.empty() && steps--){
            curr.push(rest.top());
            rest.pop();
        }
        return curr.top();
    }

   void clear(stack<string> &x){
        while(!x.empty()){
            x.pop();
        }
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */