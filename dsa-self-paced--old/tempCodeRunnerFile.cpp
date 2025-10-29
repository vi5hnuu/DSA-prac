 #include<bits/stdc++.h>
 using namespace std;

class Solution {
  public:
    int cuttingRod(int rope, int c1,int c2,int c3) {
      map<int,int> ropeMaxCuts;
      return cuttingRod(ropeMaxCuts,rope,c1,c2,c3);
    }
  private:
    int cuttingRod(map<int,int> &ropeMaxCuts,int rope, int c1,int c2,int c3) {
      if (rope == 0) return 0;  // No cuts needed for rope of length 0

       if(rope<0){
            return INT_MIN;
        }
        auto cache=ropeMaxCuts.find(rope);
        if(cache!=ropeMaxCuts.end()) return ropeMaxCuts[rope];

        int c1Cuts=cuttingRod(rope-c1,c1,c2,c3);
        int c2Cuts=cuttingRod(rope-c2,c1,c2,c3);
        int c3Cuts=cuttingRod(rope-c3,c1,c2,c3);
        int maxCuts=max(c1Cuts,max(c2Cuts,c3Cuts));
        if(maxCuts<0){
            return INT_MIN;
        }
        return ropeMaxCuts[rope]=maxCuts+1;
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