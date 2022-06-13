
    int leftHeight(struct Node* node){
        if(!node)
            return 0;
        return 1+leftHeight(node->left);
    }
    int rightHeight(struct Node* node){
        if(!node)
            return 0;
        return 1+rightHeight(node->right);
    }

    int nodesInCBT(Node* root){
        int nodes=0;
        if(!root)
            return 0;
        int lh=leftHeight(root);
        int rh=rightHeight(root);
        if(lh==rh)
            return nodes+=pow(2,lh)-1;
        else
            nodes+=1;
        nodes+=nodesInCBT(root->left);
        nodes+=nodesInCBT(root->right);
        return nodes;
    }
    //OR
     int nodesInCBT(Node* root){
        if(!root)
            return 0;
        int lh=leftHeight(root);
        int rh=rightHeight(root);
        if(lh==rh)
            return pow(2,lh)-1;
        else
            return 1+nodesInCBT(root->left)+nodesInCBT(root->right);
    }
