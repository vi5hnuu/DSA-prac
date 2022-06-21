#include<iostream>
#include<vector>
#include<stack>
using namespace std;

//naive solution is to use two for loop
vector<int> nextGreater(int arr[],int n){
  stack<int> indexes;
  vector<int> res(n,-1);
  for(int i=n-1;i>=0;i--){
    if(indexes.empty()){}
    else{
      while(!indexes.empty() && arr[indexes.top()]<=arr[i]){
        indexes.pop();
      }
      if(indexes.empty()){}
      else
        res[i]=arr[indexes.top()];
    }
    indexes.push(i);
  }
  return res;
}

int main(){
  int arr[]={15,10,18,12,4,6,2,8};
  for(int x:nextGreater(arr,8)){
    cout<<x<<" ";
  }

  return 0;
}