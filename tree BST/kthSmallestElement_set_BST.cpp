#include<iostream>
#include<set>
using namespace std;


/*
naive sol is do inorder traversel
*/
void printKth(Node *root,int k){
    if(root){

    }
}

int kthSmallest(int arr[],int n,int kth){
    set<int> s;
    for(int i=0;i<n;i++)//nlogn
        s.insert(arr[i]);

    auto itr=s.begin();
    for(int i=1;i<kth;i++)
        itr++;
    return *(itr);
}
//OR
int KthSmallest(Node *root, int &K) {
        if(root){
            int a=KthSmallest(root->left,K);
            K--;
            if(K==0)
                return root->data;
            int b=KthSmallest(root->right,K);
            return max(a,b);
        }
        else{
            return -1;
        }

    }
    int KthSmallestElement(Node *root, int K) {
            return KthSmallest(root,K);
    }
//OR
//sort nlog n and than return

int main(){
    int arr[]={10,5,15,20,1};
    cout<<kthSmallest(arr,5,3);

    return 0;
}
