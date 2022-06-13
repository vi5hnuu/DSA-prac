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
// Utility function to create a new Tree Node
Node* newNode(int val)
{
    Node* temp = new Node;
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

vector<int> findSpiral(Node *root);

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


int main() {
    int t;
    string  tc;
    getline(cin,tc);
    t=stoi(tc);
    while(t--)
    {
        string s;
        getline(cin,s);
        Node* root = buildTree(s);

        vector<int> vec = findSpiral(root);
        for(int x : vec)
        cout<<x<<" ";
        cout << endl;
    }
    return 0;
}


// } Driver Code Ends


/* A binary tree node has data, pointer to left child
   and a pointer to right child
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int x){
        data = x;
        left = right = NULL;
    }
}; */


//Function to return a list containing the level order traversal in spiral form.
/*
vector<int> findSpiral(Node *root){
    if(!root)
        return {};
    vector<int> res;
    queue<Node *> nodes;
    nodes.push(root);
    bool TraverseMode=false;
    while(!nodes.empty()){
        int NoOfNodes=nodes.size();
        stack<Node *> rev;
        if(TraverseMode){
            for(int i=0;i<NoOfNodes;i++){
                Node *temp=nodes.front();
                nodes.pop();
                res.push_back(temp->data);
                if(temp->left)nodes.push(temp->left);
                if(temp->right)nodes.push(temp->right);
            }
        }
        else{
            stack<Node *> rev;
            for(int i=0;i<NoOfNodes;i++){
                Node *temp=nodes.front();
                nodes.pop();
                rev.push(temp);
                if(temp->left)nodes.push(temp->left);
                if(temp->right)nodes.push(temp->right);
            }
            while(!rev.empty()){
                res.push_back(rev.top()->data);
                rev.pop();
            }
        }
        TraverseMode=!TraverseMode;
    }
    return res;
}
*/
//modified
/*
vector<int> findSpiral(Node *root){
    if(!root)
        return {};
    vector<int> res;
    queue<Node *> nodes;
    nodes.push(root);
    bool TraverseMode=false;
    stack<Node *> rev;
    while(!nodes.empty()){
        int NoOfNodes=nodes.size();
        stack<Node *> rev;

            for(int i=0;i<NoOfNodes;i++){
                Node *temp=nodes.front();
                nodes.pop();
                if(TraverseMode)
                res.push_back(temp->data);
                else
                rev.push(temp);
                if(temp->left)nodes.push(temp->left);
                if(temp->right)nodes.push(temp->right);
            }

        if(!TraverseMode){
        while(!rev.empty()){
                res.push_back(rev.top()->data);
                rev.pop();
            }
        }
        TraverseMode=!TraverseMode;
    }
    return res;
}
*/
//best solution
vector<int> findSpiral(Node *root){
    if(!root)
        return {};
    vector<int> res;
    stack<Node *> s1;//push from right to left
    stack<Node *> s2;//push from left to right
    s2.push(root);
    while(!s1.empty() || !s2.empty()){
        Node *temp=NULL;
        while(!s1.empty()){
            temp=s1.top();
            s1.pop();
            res.push_back(temp->data);
            if(temp->left)
                s2.push(temp->left);
            if(temp->right)
                s2.push(temp->right);
        }
        while(!s2.empty()){
            temp=s2.top();
            s2.pop();
            res.push_back(temp->data);
            if(temp->right)
                s1.push(temp->right);
            if(temp->left)
                s1.push(temp->left);
        }
    }
    return res;
}


/*
Input:
           10
         /     \
        20     30
      /    \
    40     60
Output: 10 20 30 60 40
*/
