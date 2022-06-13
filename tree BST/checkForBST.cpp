// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
#define MAX_HEIGHT 100000

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




 // } Driver Code Ends
class Solution{
    /* O(N^2)
    private:
    int maxInTree(Node *root){//max in tree
        if(!root)
            return INT_MIN;
        return max(root->data,max(maxInTree(root->left),maxInTree(root->right)));
    }
    int minInTree(Node *root){//max in tree
        if(!root)
            return INT_MAX;
        return min(root->data,min(minInTree(root->left),minInTree(root->right)));
    }
    public:
    bool isBST(Node* root){
       if(!root || (root && !root->right && !root->left))
        return true;

        int maxInLeft=maxInTree(root->left);
        int minInRight=minInTree(root->right);
        //cout<<maxInLeft<<" "<<minInRight<<endl;
        if(root->data>maxInLeft && root->data<minInRight)
            return isBST(root->left) && isBST(root->right);
        else
            return false;
    }
    */
    ////best solution
    /*
       5
    /    \
    1      8
          /
          7
    for every node we pass range
    for example node 5 has range of -inf to +inf
    node 8 has range from (5,+inf)
    node 1 has range from (-inf,5)
    node 7 has range from (5,8)
    */

    /*
    private:
        //let INT_MIN denotes -inf and INT_MAX denote +inf
        bool isBSThelper(Node *root,int start=INT_MIN,int end=INT_MAX){
            if(!root){
                return true;
            }
            if(root->data>start && root->data<end)
                return isBSThelper(root->left,start,root->data) && isBSThelper(root->right,root->data,end);
            else
                return false;
        }
    public:
        bool isBST(Node* root){
            return isBSThelper(root);
        }
    */


    //if it is bst means its inorder is in increasing order
    private:
    bool isBST(Node* root,int &prevv){
        if (!root)
            return true;

        if(!isBST(root->left,prevv))
            return false;

        if(root->data<=prevv)
            return false;
        prevv=root->data;

        return isBST(root->right,prevv);
    }
    public:
    bool isBST(Node *root){
        int prev=INT_MIN;
        return isBST(root,prev);
    }
};




// { Driver Code Starts.

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

void inorder(Node *root, vector<int> &v)
{
    if(root==NULL)
        return;

    inorder(root->left, v);
    v.push_back(root->data);
    inorder(root->right, v);
}

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
    Solution ob;
    if(ob.isBST(root))
        cout<<"1\n";

    else
        cout<<"0\n";
   }
   return 0;
}


//Position this line where user code will be pasted
  // } Driver Code Ends
