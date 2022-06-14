
#include<bits/stdc++.h>
using namespace std;

/*
node are added from start of array
means tree can be skew
*/

class BST {
    public:
    int data;
    BST *left, *right;

    BST();

    BST(int);

    BST* Insert(BST*, int);

};

BST ::BST()
    : data(0)
    , left(NULL)
    , right(NULL)
{
}

BST* BST ::Insert(BST* root, int value)
{
    if (!root) {
        return new BST(value);
    }

    if (value > root->data) {

        root->right = Insert(root->right, value);
    }
    else {

        root->left = Insert(root->left, value);
    }

    return root;
}

BST ::BST(int value)
{
    data = value;
    left = right = NULL;
}

int leafSum(BST *node,bool& alternate){
  if (node != nullptr){
   if (node->left == nullptr && node->right == nullptr){
        alternate = !alternate;
        if (alternate){
            return node->data;
        }
   }
   else{
    return leafSum(node->left,alternate) + leafSum(node->right,alternate);
    }
  }
  return 0;
}

int alternateLeafSum(BST* root){
  bool alternate = false;
  return leafSum(root,alternate);
}
int main(){
   long t;
   cin>>t;
   while(t--){
     long n;
     cin>>n;
     int i;
     int A[n];
     BST x,*root=NULL;
     for(i=0;i<n;i++){
        cin>>A[i];
        if(!root)
           root=x.Insert(root,A[0]);
        else
            x.Insert(root,A[i]);
     }
   cout<<alternateLeafSum(root)<<endl;
   }
  return 0;
}
