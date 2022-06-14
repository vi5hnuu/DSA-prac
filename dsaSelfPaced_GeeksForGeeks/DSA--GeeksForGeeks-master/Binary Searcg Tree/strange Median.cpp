/*
find meadina from kth smallest node
*/
//User function Template for C++

/*
Structure of node is like this

struct Node{
    int data;
    Node *left;
    Node *right;
};
*/

Node* KthSmallest(Node *root, int &K) {
    if(root){
        Node *a=KthSmallest(root->left,K);
        if(a)
            return a;
        K--;
        if(K==0)
            return root;
        Node *b=KthSmallest(root->right,K);
        if(b)
           return b;
        return NULL;
    }
    else{
        return NULL;
    }

}

void inorderData(Node *root,vector<int> &res){
    if(!root)
        return;
    inorderData(root->left,res);
    res.push_back(root->data);
    inorderData(root->right,res);
}
int median(Node *node,int k){
    vector<int> res;
    Node *start=KthSmallest(node,k);
    if(!start)
        return -1;

    inorderData(start,res);
    int len=res.size();
    if(len%2==0){
        return (res[len/2]+res[len/2-1])/2;
    }
    else
        return res[len/2];
}
