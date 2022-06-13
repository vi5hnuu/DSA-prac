#include<iostream>
using namespace std;


Node* selfBalance(int sortedArr[],int is,int ie){
    if(is>ie)
        return NULL;
    int mid=(is+ie)/2;
    Node *root=new Node(sortedArr[mid]);
    root->left=selfBalance(sortedArr,is,mid-1);
    root->right=selfBalance(sortedArr,mid+1,ie);
    return root;
}

Node* selfBalance(int sortedArr[],int n){
    return selfBalance(sortedArr,0,n-1);
}
int heightt(Node *root){
    if(!root)
        return 0;
    return 1+max(heightt(root->left),heightt(root->right));
}
int main(){
	int arr[]={1,2,3,4,5,6,7,8,9,10,11};
	Node *rt= selfBalance(arr,0,10);
	cout<<heightt(rt)<<" "<<log2(11)<<endl;

	return 0;
}
