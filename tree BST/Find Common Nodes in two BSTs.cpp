// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

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


class Solution
{
    void inorder(Node *root,vector<int> &res){
        if(!root)
            return;
        inorder(root->left,res);
        res.push_back(root->data);
        inorder(root->right,res);
    }
    public:
    //Function to find the nodes that are common in both BST.
    vector <int> findCommon(Node *root1, Node *root2)
    {
        /*
        Expected Time Complexity: O(N1 + N2) where N1 and N2 are the sizes of the 2 BSTs.
        Expected Auxiliary Space: O(H1 + H2) where H1 and H2 are the heights of the 2 BSTs.
        */
        vector<int> left,right;
        vector<int> res;
        inorder(root1,left);
        inorder(root2,right);
        if(left.size()==0 || right.size()==0)
            return {};

        //Tree are BST so inorder is sorted
        int i=0,j=0;
        while(i<left.size() && j<right.size()){
            if(left[i]==right[j]){
                res.push_back(left[i]);
                i++;j++;
            }
            else if(left[i]<right[j]){
                i++;
            }
            else{
                j++;
            }
        }
        return res;
    }
};




// { Driver Code Starts.

int main()
{
    int t;
    cin>>t;
    getchar();
    while(t--)
    {
        string s;
        getline(cin,s);
        Node* root1 = buildTree(s);

        getline(cin,s);
        Node* root2 = buildTree(s);
        Solution ob;
        vector <int> res = ob.findCommon(root1, root2);
        for (int i : res)
            cout << i << " ";
        cout<< endl;
    }

	return 1;
}  // } Driver Code Ends
