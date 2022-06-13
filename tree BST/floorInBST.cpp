//for naive solution use inorder preorder postorder O(n) time and O(H) space

Node* floor(Node *root,int K){//O(H) time and O(1) space
    if(!root){
        return K;
    }
    Node *parent=NULL;
    while(root){
        if(root->data==K){
            return root;

        }
        else if(root->data>K){
            parent=root;
            root=root->left;
        }
        else{
            parent=root;
            root=root->right;
        }
    }
    if(parent->data<K)
        return parent;
    return NULL;
}

//OR

Node* floor(Node *root,int K){//O(H) time and O(1) space
    if(!root){
        return K;
    }
    Node *floor=NULL;
    while(root){
        if(root->data==K){
            return root;
        }
        else if(root->data>K){
            root=root->left;
        }
        else{
            floor=root;//greatest value less than k found so far
            root=root->right;
        }
    }
    return floor;
}
