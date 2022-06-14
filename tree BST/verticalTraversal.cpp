// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

/*
Given a Binary Tree, find the vertical traversal of it starting from the leftmost level to the rightmost level.
If there are multiple nodes passing through a vertical line, then they should be printed as they appear in level order traversal of the tree.
*/

// Tree Node
struct Node
{
    int data;
    Node* left;
    Node* right;
};
// Utility function to create a new Tree Node
Node* newNode(int val)
{
    Node* temp = new Node;
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

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
    Node* root = newNode(stoi(ip[0]));

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
            currNode->left = newNode(stoi(currVal));

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
            currNode->right = newNode(stoi(currVal));

            // Push it to the queue
            queue.push(currNode->right);
        }
        i++;
    }

    return root;
}

// Function for Inorder Traversal
void printInorder(Node* root)
{
    if(!root)
        return;

    printInorder(root->left);
    cout<<root->data<<" ";
    printInorder(root->right);
}


 // } Driver Code Ends
class Solution
{
    private:
    private:
  void verticalOrder(Node *root,map<int,vector<int>> &mp){
      if(!root)
        return;

      //we use level order here =>input 1 2 3 4 5 N 6 output=>4 2 1 5 3 6
      queue<pair<Node *,int>> nodes;
      nodes.push({root,0});
      int index=0;
      while(!nodes.empty()){
          int sz=nodes.size();
          for(int i=0;i<sz;i++){
              pair<Node *,int> &temp=nodes.front();
              nodes.pop();
              mp[temp.second].push_back(temp.first->data);
              if(temp.first->left)
                nodes.push({temp.first->left,temp.second-1});
              if(temp.first->right)
                nodes.push({temp.first->right,temp.second+1});
          }
      }
      //space O(n recursion + n map + n for queue);
      //time O(n)
  }
    public:
    //Function to find the vertical order traversal of Binary Tree.
    vector<int> verticalOrder(Node *root)
    {
        map<int,vector<int>> mp;
        vector<int> res;
        verticalOrder(root,mp);
        for(auto itr=mp.begin();itr!=mp.end();itr++){
            res.insert(res.end(),(itr->second).begin(),(itr->second).end());
        }
        return res;
    }
};



// { Driver Code Starts.
int main() {
    int t;
    string  tc;
    getline(cin,tc);
    t=stoi(tc);
    while(t--)
    {
        string s;
        getline(cin,s);
        // string c;
        // getline(cin,c);
        Solution obj;
    	Node* root = buildTree(s);

    	vector <int> res = obj.verticalOrder(root);
    	for (int i : res) cout << i << " ";
        cout << endl;
    }
	return 0;
}


  // } Driver Code Ends
