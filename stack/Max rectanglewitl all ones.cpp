// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
#define MAX 1000


 // } Driver Code Ends
/*You are required to complete this method*/

class Solution{
    private:
    vector<int> prevSmallerEq(int arr[],int n){
        stack<int> indexes;
        vector<int> res(n,-1);
        for(int i=0;i<n;i++){
            if(indexes.empty()){}
            else{
                while(!indexes.empty() && arr[indexes.top()]>=arr[i])
                    indexes.pop();
                if(indexes.empty()){}
                else
                res[i]=indexes.top();
            }
            indexes.push(i);
        }
        return res;
    }
    vector<int> nextSmallerEq(int arr[],int n){
        stack<int> indexes;
        vector<int> res(n,n);
        for(int i=n-1;i>=0;i--){
            if(indexes.empty()){}
            else{
                while(!indexes.empty() && arr[indexes.top()]>=arr[i])
                    indexes.pop();
                if(indexes.empty()){}
                else
                res[i]=indexes.top();
            }
            indexes.push(i);
        }
        return res;
    }
    void print(const vector<int> &res){
        int len=res.size();
        for(int i=0;i<len;i++)
        cout<<res[i]<<" ";
        cout<<endl;
    }
    int largestHist(int arr[], int n)
    {
        int maxA=0;
        vector<int> preS=prevSmallerEq(arr,n);
        vector<int> nextS=nextSmallerEq(arr,n);
        //print(preS);
        //print(nextS);
        for(int i=0;i<n;i++){
             int cur=arr[i];
             cur+=(i-preS[i]-1)*arr[i];
             cur+=(nextS[i]-i-1)*arr[i];
             maxA=maxA>cur?maxA:cur;
        }
        return maxA;
    }
  public:
  //largest hist has efficient sol in which single traversal and single stack is req..check video
    int maxArea(int M[MAX][MAX], int R, int C) {
        int res=largestHist(M[0],C);
          for(int i=1;i<R;i++){
            for(int j=0;j<C;j++){
              if(M[i][j]==1)
                M[i][j]+=M[i-1][j];
            }
            res=max(res,largestHist(M[i],C));
          }
          return res;
    }
};


// { Driver Code Starts.
int main() {
    int T;
    cin >> T;

    int M[MAX][MAX];

    while (T--) {
        int n, m;
        cin >> n >> m;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> M[i][j];
            }
        }
        Solution obj;
        cout << obj.maxArea(M, n, m) << endl;
    }
}
  // } Driver Code Ends