/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
 

Constraints:

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
Only one valid answer exists.
 

Follow-up: Can you come up with an algorithm that is less than O(n2) time complexity?
*/

//O(N*N)
#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
        vector<int> twoSum(vector<int>& nums, int target) {
            for(int i=0,sz=nums.size();i<sz;i++){
                const auto &x=nums[i];
                for(int j=i+1;j<sz;j++){
                    if(x==target-nums[j]) return {i,j};
                }
            }
            return {};
        }
};



//O(NLOG(N))
#include<bits/stdc++.h>
using namespace std;

class Solution {
    public:
      vector<int> twoSum(vector<int>& nums, int target) {
          unordered_map<int,int> parsedNums;//Value->index
          for(int i=0;i<nums.size();i++){
              const auto &x=nums[i];
              const auto &itr=parsedNums.find(target-x);
              if(itr!=parsedNums.end()) return {i,itr->second};
              parsedNums[x]=i;
          }
          return {};
      }
};