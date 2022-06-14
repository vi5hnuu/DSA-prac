// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
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


 // } Driver Code Ends
/*Complete the function below
Node is as follows:
struct Node{
int data;
Node *left,*right;
};
*/
class Solution{
  private:
  void verticalSum(Node *root,map<int,int> &mp,int index=0){
      if(!root)
        return;

      verticalSum(root->left,mp,index-1);
      mp[index]+=root->data;//logn time as map uses self balancing tree
      verticalSum(root->right,mp,index+1);
  }
  public:
  /*
  root at zero column
  we go left and reduce column to -1
  we go right we increase column to +1
  we ue map and keys are  -3 -2 -1 0 1 2 3


  */
    vector <int> verticalSum(Node *root) {
        vector<int> res;
        map<int,int> mp;
        verticalSum(root,mp);
        for(auto itr=mp.begin();itr!=mp.end();itr++)
            res.push_back(itr->second);

        return res;
    }
};

// { Driver Code Starts.
int main()
{

    int t;
	scanf("%d ",&t);
    while(t--)
    {
        string s;
		getline(cin,s);
        Node* root = buildTree(s);
        Solution obj;
        vector <int> res = obj.verticalSum(root);
        for (int i : res) cout << i << " ";
        cout<<endl;
    }
}  // } Driver Code Ends
