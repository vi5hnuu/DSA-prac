// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// Tree Node
struct Node
{
    int data;
    Node* left;
    Node* right;
};

vector<int> leftView(struct Node *root);

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

    // for(string i:ip)
    //     cout<<i<<" ";
    // cout<<endl;
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


int main() {
    int t;
    scanf("%d ",&t);
    while(t--)
    {
        string s;
        getline(cin,s);
        Node* root = buildTree(s);
        vector<int> vec = leftView(root);
        for(int x : vec)
        cout<<x<<" ";
        cout << endl;
    }
    return 0;
}

// } Driver Code Ends


/* A binary tree node

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int x){
        data = x;
        left = right = NULL;
    }
};
 */

//Function to return a list containing elements of left view of the binary tree.

//same as level order traversal using queue
/*
vector<int> leftView(Node *root)
{
    //print first nodes at each level
    if(!root)
        return {};
   vector<int> res;
   queue<Node *> nodes;
   nodes.push(root);
   nodes.push(NULL);
   while(!nodes.empty()){
       Node *temp=nodes.front();

       if(temp==NULL){//This level completed as we reached the marker
            nodes.pop();
            if(!nodes.empty())
                nodes.push(NULL);//when we reach end of marker we have next level nodes in queue

           continue;
       }
       //else print data of first node and pop untill NULL marker
       res.push_back(temp->data);
       while(nodes.front()!=NULL){
           Node *temp=nodes.front();
           nodes.pop();
           if(temp->left){
               nodes.push(temp->left);
           }
           if(temp->right){
               nodes.push(temp->right);
           }
       }
   }
   return res;
}
*/
/////////////////////////////////////////
//same as level order traversal using loops
vector<int> leftView(Node *root){
    vector<int> res;
    if(!root){
        return {};
    }
    queue<Node *> nodes;
    nodes.push(root);
    while(!nodes.empty()){
        int nodeCount=nodes.size();
        for(int i=0;i<nodeCount;i++){
            Node *temp=nodes.front();
            nodes.pop();
            if(i==0)
                res.push_back(temp->data);

            if(temp->left)
                nodes.push(temp->left);
            if(temp->right)
                nodes.push(temp->right);
        }
    }
    return res;
}
/////////////////////////////////////////
/*
void leftView(Node *root,vector<int> &res,int &maxLevel,int level=1){
    if(root==NULL)
        return;
    if(maxLevel<level){
        res.push_back(root->data);
        maxLevel=level;
    }
    leftView(root->left,res,maxLevel,level+1);
    leftView(root->right,res,maxLevel,level+1);
}

vector<int> leftView(Node *root)
{
    vector<int> res;
    int maxLevel=0;
    leftView(root,res,maxLevel);
    return res;
}
*/





