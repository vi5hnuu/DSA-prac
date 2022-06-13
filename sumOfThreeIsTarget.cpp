#include<bits/stdc++.h>
using namespace std;

vector<int> sumOfThree(vector<int> &nums,int target){
sort(nums.begin(),nums.end());
for(int i=0;i<nums.size();i++){ //iterating all elements
    int start=0;
    int endd=nums[nums.size()-1];

    //two pointer approach
    int temp=target-nums[i]; //nw we need to find rest two number
    while(start<endd){
        if(start!=endd && start!=i && nums[start]+nums[endd]==temp){
            return {nums[i],nums[start],nums[endd]};
        }
        else if(nums[start]+nums[endd]<target){
            start++;
        }
        else{
        endd--;
        }
    }
    return {-1}; //no such triplet exist
}

}

int main(){
vector<int> numbers={1,2,3,4,5,6,7,8,9,10};
for(int x:sumOfThree(numbers,11))
cout<<x<<" ";
return 0;
}
