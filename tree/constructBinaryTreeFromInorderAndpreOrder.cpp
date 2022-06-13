// { Driver Code Starts
//

#include<bits/stdc++.h>
using namespace std;

struct Node
{
	int data;
	struct Node *left;
	struct Node *right;

	Node(int x){
	    data = x;
	    left = NULL;
	    right = NULL;
	}
};


void printPostOrder(Node *root)
{
	if(root==NULL)
		return;
	printPostOrder(root->left);
	printPostOrder(root->right);
	cout<<root->data<<" ";
}

 // } Driver Code Ends


/*Complete the code here.
Node is as follows:
struct Node
{
  int data;
  Node* left;
  Node* right;
};
*/
class Solution{
    Node* buildTree(int in[],int pre[],int is,int ie,int &preIndex){
        if(is>ie)return NULL;
        Node *root=new Node(pre[preIndex++]);
        int indexInInorder=-1;
        for(int i=is;i<=ie;i++){
            if(in[i]==root->data){
                indexInInorder=i;
                break;
            }
        }
        root->left=buildTree(in,pre,is,indexInInorder-1,preIndex);
        root->right=buildTree(in,pre,indexInInorder+1,ie,preIndex);
        return root;
    }
    public:
    Node* buildTree(int in[],int pre[], int n)
    {
        int preIndex=0;
        return buildTree(in,pre,0,n-1,preIndex);
    }
};

// { Driver Code Starts.
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;

		int inorder[n], preorder[n];
		for(int i=0; i<n; i++)
			cin>> inorder[i];
		for(int i=0; i<n; i++)
			cin>> preorder[i];
		Solution obj;
		Node *root = obj.buildTree(inorder, preorder, n);
		printPostOrder(root);
		cout<< endl;
	}
}
  // } Driver Code Ends
