// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
#define MAX_HEIGHT 100000

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


vector <int> bottomView(Node *root);

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


 // } Driver Code Ends
//Function to return a list containing the bottom view of the given tree.

class Solution {
     /*
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
    vector <int> bottomView(Node *root) {
        map<int,vector<int>> mp;
        vector<int> res;
        verticalOrder(root,mp);
        for(auto itr=mp.begin();itr!=mp.end();itr++){
                int sz=(itr->second).size();
                res.push_back((itr->second)[sz-1]);
        }
        return res;
    }
    */
    //Modified
   /*
    private:
  void verticalOrder(Node *root,map<int,vector<int>> &mp){
      if(!root)
        return;

      //we use level order here =>input 1 2 3 4 5 N 6 output=>4 2 1 5 3 6
      queue<pair<Node *,int>> nodes;
      nodes.push({root,0});
      int index=0;
      while(!nodes.empty()){
             pair<Node *,int> &temp=nodes.front();
              nodes.pop();
              mp[temp.second].push_back(temp.first->data);
              if(temp.first->left)
                nodes.push({temp.first->left,temp.second-1});
              if(temp.first->right)
                nodes.push({temp.first->right,temp.second+1});
      }
      //space O(n recursion + n map + n for queue);
      //time O(n)
  }

  public:
    vector <int> bottomView(Node *root) {
        map<int,vector<int>> mp;
        vector<int> res;
        verticalOrder(root,mp);
        for(auto itr=mp.begin();itr!=mp.end();itr++){
                int sz=(itr->second).size();
                res.push_back((itr->second)[sz-1]);
        }
        return res;
    }
    */

    /*
why push all in map we can replace the already present key when new key is found
*/
//space efficient
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
                if(mp.find(temp.second)==mp.end())//logn ..space time trade off
                mp[temp.second].push_back(temp.first->data);
                else
                mp[temp.second][0]=temp.first->data;
              if(temp.first->left)
                nodes.push({temp.first->left,temp.second-1});
              if(temp.first->right)
                nodes.push({temp.first->right,temp.second+1});
          }
      }
      //space O(n recursion + n map + n for queue);
      //time O(nlogn)
  }
    public:
    vector<int> bottomView(Node *root)
    {
        map<int,vector<int>> mp;
        vector<int> res;
        verticalOrder(root,mp);
        for(auto itr=mp.begin();itr!=mp.end();itr++){
                res.push_back((itr->second)[0]);
        }
        return res;
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
        string s ,ch;
        getline(cin, s);
        Node* root = buildTree(s);
        Solution ob;
        vector <int> res = ob.bottomView(root);
        for (int i : res) cout << i << " ";
        cout << endl;
    }
    return 0;
}


  // } Driver Code Ends
