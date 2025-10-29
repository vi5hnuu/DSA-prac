 #include<bits/stdc++.h>
 using namespace std;

class Solution {
  public:
    int cuttingRod(int rope, int c1,int c2,int c3) {
      vector<int> ropeMaxCuts(rope + 1, INT_MIN);
      ropeMaxCuts[0] = 0; // No cuts needed for rope of length 0
      for(int ropeLength=1;ropeLength<=rope;ropeLength++){
        if(ropeLength-c1>=0 && ropeMaxCuts[ropeLength-c1]!=INT_MIN){
            ropeMaxCuts[ropeLength]=max(ropeMaxCuts[ropeLength],ropeMaxCuts[ropeLength-c1]+1);
        }
        if(ropeLength-c2>=0 && ropeMaxCuts[ropeLength-c2]!=INT_MIN){
            ropeMaxCuts[ropeLength]=max(ropeMaxCuts[ropeLength],ropeMaxCuts[ropeLength-c2]+1);
        }
        if(ropeLength-c3>=0 && ropeMaxCuts[ropeLength-c3]!=INT_MIN){
            ropeMaxCuts[ropeLength]=max(ropeMaxCuts[ropeLength],ropeMaxCuts[ropeLength-c3]+1);
        }
      }
      if(ropeMaxCuts[rope]<0) return 0;
      return ropeMaxCuts[rope];
    }
};

 int main(){
    Solution s1;
    cout<<s1.cuttingRod(5,2,5,1)<<endl;
    cout<<s1.cuttingRod(5,2,5,3)<<endl;
    cout<<s1.cuttingRod(10,2,5,3)<<endl;
    cout<<s1.cuttingRod(10,2,5,4)<<endl;
    cout<<s1.cuttingRod(10,2,5,6)<<endl;
    cout<<s1.cuttingRod(10,2,5,8)<<endl;
    cout<<s1.cuttingRod(10,2,5,9)<<endl;
  }