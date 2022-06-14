// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
#define MAX_HEIGHT 100000
#define MAX_SIZE 100000

// Tree Node
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Function to Build Tree
Node* buildTree(string str)
{
   // Corner Case
   if(str.length() == 0 || str[0] == 'N')
       return NULL;

   // Creating vector of strings from input
   // string after spliting by space
   vector<string> ip;

   istringstream iss(str);
   for(string str; iss >> str; )
       ip.push_back(str);

   // Create the root of the tree
   Node* root = new Node(stoi(ip[0]));

   // Push the root to the queue
   queue<Node*> queue;
   queue.push(root);

   // Starting from the second element
   int i = 1;
   while(!queue.empty() && i < ip.size()) {

       // Get and remove the front of the queue
       Node* currNode = queue.front();
       queue.pop();

       // Get the current node's value from the string
       string currVal = ip[i];

       // If the left child is not null
       if(currVal != "N") {

           // Create the left child for the current node
           currNode->left = new Node(stoi(currVal));

           // Push it to the queue
           queue.push(currNode->left);
       }

       // For the right child
       i++;
       if(i >= ip.size())
           break;
       currVal = ip[i];

       // If the right child is not null
       if(currVal != "N") {

           // Create the right child for the current node
           currNode->right = new Node(stoi(currVal));

           // Push it to the queue
           queue.push(currNode->right);
       }
       i++;
   }

   return root;
}

 // } Driver Code Ends
/*Complete the function below
Node is as follows
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/

class Solution{
  private:
  /*
  Should we store vector of int or vector of references
  ans is references as references take les space because say the data in node is so heavy then vector will consume
  unnecessary space
  */
   /*
   void inorder(Node *root,vector<Node *> &res){
        if(!root)
            return;
        inorder(root->left,res);
        res.push_back(root);
        inorder(root->right,res);
    }
  public:
    // root : the root Node of the given BST
    // target : the target sum
    int isPairPresent(struct Node *root, int target)//O(N) ,O(N) space
    {
        //Nodes with their data in increasing order
        vector<Node *> res;
        inorder(root,res);
        int p=0,q=res.size()-1;//two pointer approach
        while(p<q){
            if(res[p]->data+res[q]->data==target){
                return 1;
            }
            else if(res[p]->data+res[q]->data<target){
                p++;
            }
            else{
                q--;
            }
        }
        return 0;
    }
    */
    public:
    /*
    int isPairPresent(struct Node *root, int target)//O(N) ,O(N) space
    {
        //Nodes with their data in increasing order
        vector<Node *> res;
        inorder(root,res);
        int p=0,q=res.size()-1;//two pointer approach
        while(p<q){
            if(res[p]->data+res[q]->data==target){
                return 1;
            }
            else if(res[p]->data+res[q]->data<target){
                p++;
            }
            else{
                q--;
            }
        }
        return 0;
    }
    */
    /*
    if we can find the pair earlier why go for inorder
    in prev sol we used O(n+H) sapce H for recursion and n for nodes..(worst case is O(n+h))
    what if we use unordered_set and when we taverse inorder we see if targetSum-currentNodeData is present in set or not if yes return yes else insert the current node data...
    and checking if some data in unordered_set takes o(1) time.....in java hashSet take O(1).
    */
    private:
    int isPairPresent(struct Node *root, int target,unordered_set<int> &check)//O(N) ,O(N) space
    {
        if(!root)
            return false;
        //inorder
        bool a=isPairPresent(root->left,target,check);
        if(a)
            return true;
        if(check.count(target-root->data))//O(1)..can be linear
            return true;
        else
            check.insert(root->data);
        return isPairPresent(root->right,target,check);

    }
    public:
    int isPairPresent(struct Node *root, int target)//O(N) ,O(N) space
    {
        unordered_set<int> check;
        return isPairPresent(root,target,check);
    }
};

// { Driver Code Starts.
int main() {

   int t;
   string tc;
   getline(cin, tc);
   t=stoi(tc);
   while(t--)
   {
        string s;
       getline(cin, s);
       Node* root = buildTree(s);

       getline(cin, s);
       int k = stoi(s);
        //getline(cin, s);
       Solution obj;
       cout << obj.isPairPresent(root, k) << endl;
       //cout<<"~"<<endl;
   }
   return 0;
}
  // } Driver Code Ends
